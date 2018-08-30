package aplicacao;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

/**
 * @author serpa and schubert
 */

public class Servidor implements Runnable {
	Socket cliente;

	public Servidor(Socket cliente) {
		this.cliente = cliente;
	}

	public void run() {
		String[] dados;
		BufferedReader entrada;

		try {
			entrada = new BufferedReader(new InputStreamReader(cliente.getInputStream()));
			dados = entrada.readLine().split("-");
			
			DateFormat dateFormat = new SimpleDateFormat("dd/MM/yy HH:mm:ss:SS");
			Calendar cal = Calendar.getInstance();
			
			//System.out.println("\n\tDebug - Cliente: " + dados[0]);
			Date d1 = dateFormat.parse(dados[0]);
			long diff = cal.getTimeInMillis() - d1.getTime();

			System.out.println(dateFormat.format(cal.getTime()) + " - " + dados[1]	+ " - Atraso: " + diff + " ms\n");

			cliente.close();
			entrada.close();
		} catch (IOException | ParseException e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) throws IOException {
		ServerSocket servidor = new ServerSocket(12345);
		System.out.println("Servidor iniciado em 127.0.0.1:12345\n");

		while (true) {
			Socket cliente = servidor.accept();
			new Thread(new Servidor(cliente)).start();
		}
	}

}