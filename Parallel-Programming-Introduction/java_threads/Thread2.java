/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package prog.paralela;

import java.util.concurrent.Semaphore;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author davi
 */
public class Thread2 implements Runnable {

    static int _N = 1000;
    static int saldo = 100;

    @Override
    public void run() {
        deposita();
        retira();
    }

    public static void main(String[] args) {
        (new Thread(new Thread2())).start();
        (new Thread(new Thread2())).start();
        System.out.println(saldo);
    }

    public static void deposita() {
        Semaphore mutex = new Semaphore(1);
        int i, a;
        for (int j = 0; j < _N; j++) {
            try {
                mutex.acquire();
                a = saldo;
                a = a + 1;
                saldo = a;
                mutex.release();
            } catch (InterruptedException ex) {
                Logger.getLogger(Thread2.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }

    public static void retira() {
        int i, b;
        Semaphore mutex = new Semaphore(1);
        for (int j = 0; j < _N; j++) {
            try {
                mutex.acquire();
                b = saldo;
                b = b - 1;
                saldo = b;
                mutex.release();
            } catch (InterruptedException ex) {
                Logger.getLogger(Thread2.class.getName()).log(Level.SEVERE, null, ex);
            }
        }

    }
}
