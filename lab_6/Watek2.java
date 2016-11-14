// @author ZooMic
package lab_6;

public class Watek2 implements Runnable {
    private int a;
    private int b;
    private Obraz obraz;
    
    Watek2(int a, int b, Obraz o) {
        this.a = a;
        this.b = b;
        this.obraz = o;
    }
    
    @Override
    public void run() {
        for(int i = a; i < b; i++) {
           obraz.calculate_histogram(i);
           obraz.print_histogram(i);
        }
    }
    
}
