/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package prog.paralela;

import static java.lang.Math.random;
import java.util.concurrent.Semaphore;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *  Exercício não foi completo, tive dificuldades com a array de threads
 * @author Claudio Davi
 */
public class Thread4 implements Runnable{

    final static int TAM = 100;
    final static int NTH = 10;

    static int[] vetor = new int[TAM];
    static int somaTotal = 0;
    static Semaphore semaphore;

    public static void funcao(long i) throws InterruptedException {
        int somaLocal = 0;

        System.out.println(i);
        for (int j = (int) ((TAM / NTH) * i); j < (TAM / NTH) * i + 1; j++) {
            somaLocal += vetor[j];
            System.out.println(somaLocal);

        }
        semaphore.acquire();
        somaTotal += somaLocal;
        semaphore.release();
    }

    public static void main(String[] args) {
        Thread4 th[] = new Thread4[NTH];
        int id = 0;
        for(int i = 0; i < TAM; i++) {
            vetor[i] = 1;
        }
        for(int i = 0; i < NTH; i++){
            th[i] = new Thread4();
        }
    }

    @Override
    public void run() {
        try {
            funcao((long) random());
        } catch (InterruptedException ex) {
            Logger.getLogger(Thread4.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

}
