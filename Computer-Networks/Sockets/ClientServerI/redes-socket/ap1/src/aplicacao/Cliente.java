/**
 * 
 */
package aplicacao;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.net.Socket;

/**
 * @author serpa and schubert
 * 
 */
public class Cliente {
	private String ip;
	private int port;

	public Cliente(String ip, int port) {
		this.ip = ip;
		this.port = port;
	}

	public void executar() {
		Socket cliente = null;
		String mensagem = null;
		DataOutputStream output = null;

		while (true) {
			System.out.println("Mensagem: ");
			BufferedReader leitor = new BufferedReader(new InputStreamReader(
					System.in));
			try {
				mensagem = leitor.readLine();
			} catch (Exception e) {
				System.out.println("Não foi possível ler da entrada.\n"
						+ e.getMessage() + ".\n");
				System.exit(-7);
			}

			if (mensagem.equalsIgnoreCase("SAIR")) {
				break;
			}

			try {
				cliente = new Socket(this.ip, this.port);
				output = new DataOutputStream(cliente.getOutputStream());
				output.writeBytes(mensagem + "\n");
			} catch (Exception e) {
				System.out
						.println("Não foi possível enviar a mensagem ao servidor.\n"
								+ e.getMessage() + ".\n");
				System.exit(-8);
			}

			try {
				cliente.close();
			} catch (Exception e) {
				System.out
						.println("Não foi possível encerrar a conexão do cliente.\n"
								+ e.getMessage() + ".\n");
				System.exit(-9);
			}

		}

	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Cliente cliente = new Cliente("127.0.0.1", 12345);

		cliente.executar();

	}

}
