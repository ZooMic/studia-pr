//@author ZooMic
package lab_6;

public class Watek3 extends Thread {
    private int id;
    private int n;
    private Obraz obraz;
    
    Watek3(int i, int n, Obraz o) {
        this.id = i;
        this.n = n;
        this.obraz = o;
    }

    @Override
    public void run() {
        obraz.calculate_histogram_cycle(id,n);
    }
    
}
