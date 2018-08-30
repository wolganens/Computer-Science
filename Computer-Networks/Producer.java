public class Producer implements Runnable {
    private CubbyHole cubbyhole;

    public Producer(CubbyHole c) {
        cubbyhole = c;
    }

    public void run() {
        for (int i = 1; i <= 5; i++) {
            cubbyhole.put(i);
            try {
                Thread.sleep((int)(Math.random() * 100));
            } catch (InterruptedException e) { }
        }
    }
}
