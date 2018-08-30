/**
 * 
 */
package aplicacao;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * @author serpa and schubert
 * 
 */
public class Servidor {

	private ServerSocket servidor;

	public Servidor(int porta) {
		try {
			servidor = new ServerSocket(porta);
		} catch (Exception e) {
			System.out.println("Não foi possível escutar na porta " + porta
					+ ".\n" + e.getMessage() + ".\n");
			System.exit(-2);
		}

		System.out.println("Servidor iniciado em 127.0.0.1:" + porta);
	}

	public void executar() {
		String dados = null;
		Socket cliente = null;
		BufferedReader entrada = null;

		while (true) {
			try {
				cliente = servidor.accept();
				entrada = new BufferedReader(new InputStreamReader(
						cliente.getInputStream()));
			} catch (Exception e) {
				System.out
						.println("Não foi possível aceitar a conexão com o cliente.\n"
								+ e.getMessage() + ".\n");
				System.exit(-3);
			}

			try {
				dados = entrada.readLine();
				System.out.println(dados + "\n");
			} catch (Exception e) {
				System.out
						.println("Não foi possível ler a entrada no método listen().\n"
								+ e.getMessage() + ".\n");
				System.exit(-4);
			}

			try {
				cliente.close();
				entrada.close();
			} catch (Exception e) {
				System.out
						.println("Não foi possível encerrar a conexão com o cliente.\n"
								+ e.getMessage() + ".\n");
				System.exit(-5);
			}
		}
	}

	public static void main(String[] args) {
		Servidor servidor = new Servidor(12345);
		
		servidor.executar();
	}

}
