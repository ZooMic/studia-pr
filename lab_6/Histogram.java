// @author ZooMic
package lab_6;

import java.util.Scanner;

public class Histogram {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
	
	System.out.println("Set image size: n (#rows), m(#kolumns)");
	int n = scanner.nextInt();
	int m = scanner.nextInt();
	Obraz obraz = new Obraz(n, m);
        //zadanie_a(obraz);
        //zadanie_b(obraz);
        zadanie_2_cyklicznie(obraz);
    }
    
    private static void zadanie_a(Obraz obraz) {
        // Każdy wątek związany jest z jednym znakiem
        Watek[] threads = new Watek[94];
        for(int i = 0; i < 94; i++) {
            threads[i] = new Watek(i, obraz);
        }
        for(int i = 0; i < 94; i++) {
            threads[i].start();
        }
        for(int i = 0; i < 94; i++) {
            try {
               threads[i].join();
            } catch (InterruptedException e) {}
        }
    }
    
    private static void zadanie_b(Obraz obraz) {
        // Dekompozycja w dziedzinie problemu metodą blokową (dziedziną jest ASCII)
        Scanner scanner = new Scanner(System.in);
        System.out.println("Write threads number: ");
        int liczba_watkow = scanner.nextInt();
        Watek2[] threads = new Watek2[liczba_watkow];
        Thread[] t = new Thread[liczba_watkow];
        int przedzial = 94 / liczba_watkow;
        for(int i = 0; i < liczba_watkow; i++) {
            if(i == liczba_watkow - 1) {
                threads[i] = new Watek2(i * przedzial, 94, obraz);
            } else {
                threads[i] = new Watek2(i * przedzial, (i+1) * przedzial, obraz);
            }
        }
        for(int i = 0; i < liczba_watkow; i++) {
           t[i] = new Thread(threads[i]);
           t[i].start();
        }
        for(int i = 0; i < liczba_watkow; i++) {
            try {
               t[i].join();
            } catch (InterruptedException e) {}
        }
    }
    
    private static void zadanie_2_cyklicznie(Obraz obraz) {
         // Dekompozycja w dziedzinie problemu metodą cykliczna (dziedziną jest Obraz)
        Scanner scanner = new Scanner(System.in);
        System.out.println("Write threads number: ");
        int liczba_watkow = scanner.nextInt();
        Watek3[] threads = new Watek3[liczba_watkow];
        for(int i = 0; i < liczba_watkow; i++) {
            threads[i] = new Watek3(i, liczba_watkow, obraz);
        }
        for(int i = 0; i < liczba_watkow; i++) {
            threads[i].start();
        }
        for(int i = 0; i < liczba_watkow; i++) {
             try {
               threads[i].join();
            } catch (InterruptedException e) {}
        }
        obraz.print_histogram();
    }
    
}
