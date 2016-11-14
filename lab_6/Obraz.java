// @author ZooMic
package lab_6;

import java.util.Random;

public class Obraz {
    private int size_n;
    private int size_m;
    private char[][] tab;
    private int[] histogram;
    
    public Obraz(int n, int m) {
	
	this.size_n = n;
	this.size_m = m;
	tab = new char[n][m];
	
	final Random random = new Random();
	
	for(int i=0;i<n;i++) {
	    for(int j=0;j<m;j++) {	
		tab[i][j] = (char)(random.nextInt(94)+33);  // ascii 33-127
		System.out.print(tab[i][j]+" ");
	    }
	    System.out.print("\n");
	}
	System.out.print("\n\n");
	histogram = new int[94];
   	clear_histogram();
    }
    
    public void clear_histogram(){
	for(int i=0;i<94;i++) histogram[i]=0;
    }

    public void calculate_histogram(){
	for(int i=0;i<size_n;i++) {
	    for(int j=0;j<size_m;j++) {
	
		for(int k=0;k<94;k++) {
		    if(tab[i][j] == (char)(k+33)) histogram[k]++;	    
		}

	    }
	}
    }
    
    private synchronized void increment_histogram(int id) {
        histogram[id]++;
    }
    
    public void calculate_histogram(int id) {
        for(int i = 0; i < size_n; i++) {
            for(int j = 0; j < size_m; j++) {
                if(tab[i][j] == (char)(id+33)) {
                    increment_histogram(id);
                }
            }
        }
    }
    
    public void calculate_histogram_cycle(int id, int n) {
        // id - pozycja poczatkowa (id watku)
        // n - ilosc watków (przesunięcie o n elementów)
        for(int i = 0; i < size_n; i++) {
            for(int j = id; j < size_m; j += n) {
                increment_histogram((int)tab[i][j] - 33);
            }
        }
    }

    public void print_histogram() {
	for(int i=0;i<94;i++) {
	    System.out.print((char)(i + 33));
            for(int j = 0; j < histogram[i]; j++) {
                System.out.print("=");
            }
            System.out.println();	    
	}
    }
    
    public synchronized void print_histogram(int id) {
        System.out.print((char)(id + 33));
        for(int i = 0; i < histogram[id]; i++) {
            System.out.print("=");
        }
        System.out.println();
    }
}
