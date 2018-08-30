package aplicacao;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.net.UnknownHostException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;

/**
 * @author serpa and schubert
 */

public class Cliente {
	private String ip;
	private int port, id;

	public Cliente(String ip, int port, int id) {
		this.ip = ip;
		this.port = port;
		this.id = id;
	}

	public void executar() throws UnknownHostException, IOException, InterruptedException {
		int msg = 1;
		Socket cliente = null;
		DataOutputStream output = null;

		while (true) {
			cliente = new Socket(this.ip, this.port);
			
			output = new DataOutputStream(cliente.getOutputStream());
			
			DateFormat dateFormat = new SimpleDateFormat("dd/MM/yy HH:mm:ss:SS");
			Calendar cal = Calendar.getInstance(); 
			
			output.writeBytes(dateFormat.format(cal.getTime()) + "-Cliente " + this.id + ": msg " + msg++);

			cliente.close();

			Thread.sleep(3000);
		}
		
	}

	public static void main(String[] args) throws NumberFormatException, IOException, InterruptedException {		
		
		BufferedReader leitor = new BufferedReader(new InputStreamReader(System.in));
		System.out.println("Digite o número do cliente: ");
		int id = Integer.parseInt(leitor.readLine());

		Cliente cliente = new Cliente("127.0.0.1", 12345, id);

		cliente.executar();

	}

}
