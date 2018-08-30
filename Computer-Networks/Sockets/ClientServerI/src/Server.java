import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import static java.lang.Long.parseLong;
import java.net.*;
import java.util.Date;
import org.joda.time.DateTime;
import org.joda.time.DateTimeUtils;

class Server {
 public static void main(String argv[]) throws Exception {  
  
  // Creates a server socket, which waits for clients 
  // to initiate connection.
  ServerSocket welcomeConnection = new ServerSocket(4444);
  
  while (true) {
   System.out.println("Aguardando conexões....");
   
   // Creates a new socket when a client contacts 
   // the server for the first time.
   Socket connection = welcomeConnection.accept();
   
   Date date = new Date();
   
   
   System.out.println("Client Connected.");
   
   BufferedReader fromClient = new BufferedReader(
     new InputStreamReader(connection.getInputStream()));
   
   DataOutputStream toClient = new DataOutputStream(
     connection.getOutputStream());
      
   long ping = date.getTime() - parseLong(fromClient.readLine());
      
   String clientMessage = fromClient.readLine();
   
   System.out.println(clientMessage);
      
  }
 }
}