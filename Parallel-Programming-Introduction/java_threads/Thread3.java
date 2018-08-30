/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package prog.paralela;

import java.util.concurrent.Semaphore;
import java.util.logging.Level;
import java.util.logging.Logger;
import sun.awt.windows.ThemeReader;

/**
 *
 * @author Claudio Davi
 */
public class Thread3 implements Runnable {

    static int buffer = 0;

    @Override
    public void run() {
        try {
            produtor();
            consumidor();
        } catch (InterruptedException ex) {
            Logger.getLogger(Thread3.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public static void main (String args[]){
      (new Thread(new Thread3())).start();
        (new Thread(new Thread3())).start();
    }

    public synchronized void produtor() throws InterruptedException {
        Semaphore mutex = new Semaphore(1);

        for (int j = 0; j < 100; j++) {
            mutex.acquire();
            buffer++;
            System.out.println(buffer);
            notify();
            mutex.release();
        }
    }

    public synchronized void consumidor() throws InterruptedException {
        Semaphore mutex = new Semaphore(1);
        for (int i = 0; i < 100; i++) {
            mutex.acquire();
            while (buffer <= 0) {
                wait();
                buffer--;
                System.out.println(buffer);
                mutex.release();
            }
        }
    }
}
