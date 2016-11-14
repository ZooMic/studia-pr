//@author ZooMic
package lab_6;

public class Watek extends Thread {
    private int id;
    private Obraz obraz;
    
    Watek(int i, Obraz o) {
        this.id = i;
        this.obraz = o;
    }

    @Override
    public void run() {
        obraz.calculate_histogram(id);
        obraz.print_histogram(id);
    }
    
}
