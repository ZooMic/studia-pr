#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<omp.h>

#include "search_max_openmp.h"

/********************** linear search ************************/
double search_max(double *A, int p, int k) {
		double a_max = A[p];
		int i;
		for(i=p+1; i<=k; i++) if(a_max < A[i]) a_max = A[i];
		return(a_max);
}

/************* parallel linear search - openmp ****************/
double search_max_openmp_simple( double *A, int p, int k) {
	  double a_max = A[p];
	  double a_max_local = a_max;
		#pragma omp parallel default(none) firstprivate(A, p, k, a_max_local) shared(a_max)
	  {
	    	int i;
				#pragma omp for
	    	for(i=p+1; i<=k; i++) if(a_max_local < A[i]) a_max_local = A[i];
				#pragma omp critical (cs_a_max)
	    	{
	      		if(a_max < a_max_local) a_max = a_max_local;
	    	}
	  }
	  return(a_max);
}

/************* parallel linear search - openmp ****************/
double search_max_openmp_task(double *A, int p, int k) {
	  double a_max = A[p];
		//omp_set_nested(1);
		#pragma omp parallel sections default(none) shared(a_max) firstprivate(A,p,k)
	  {
				#pragma omp section
	    	{
			      int num_threads = omp_get_num_threads();
			      int n = k-p+1;
			      int num_tasks = num_threads+1;
			      int n_loc=ceil(n/num_tasks);
			      int itask;
						int local_max = 0;
						#pragma omp parallel for default(none) firstprivate(local_max) shared(a_max, num_tasks, n_loc, A, p, k)
			      for(itask=0; itask<num_tasks; itask++) {
								int p_task = p+itask*n_loc;
								if(p_task>k) {
								  	printf("Error in task decomposition! Exiting.\n");
								  	exit(0);
								}
								int k_task = p+(itask+1)*n_loc-1;
								if(itask==num_tasks-1) k_task = k;
								#pragma omp task
								{
										int i;
										for(i = p_task; i < k_task; i++) {
												if(local_max < A[i]) local_max = A[i];
										}
										#pragma omp critical
										{
												if(local_max > a_max) a_max = local_max;
										}
								} // end task definition
			    	} // end loop over tasks
			  } // end single region
	  } // end parallel region
	  return(a_max);
}


/************ binary search (array not sorted) ****************/
double bin_search_max(double *a, int p, int k) {
	  if(p<k) {
		    int s=(p+k)/2;
		    double a_max_1 = bin_search_max(a, p, s);
		    double a_max_2 = bin_search_max(a, s+1, k);
		    //printf("p %d  k %d, maximal elements %lf, %lf\n", p, k, a_max_1, a_max_2);
		    if(a_max_1 < a_max_2) return(a_max_2);
		    else return(a_max_1);
	  }
	  else{
	    	return(a[p]);
	  }
}
/*** single task for parallel binary search (array not sorted) - openmp ***/
#define  max_level 4
double bin_search_max_task(double* A, int p, int r, int level) {


}

/********** parallel binary search (array not sorted) - openmp ***********/
double bin_search_max_openmp(double *A, int p, int k ) {
	  double a_max;
		#pragma omp parallel default(none) firstprivate(A,p,k) shared(a_max)
	  {
				#pragma omp single
	    	{
						#pragma omp task
	      		{
		  					a_max = bin_search_max_task(A,p,k,0);
	      		}
	    	}
	  }
	  return(a_max);
}
