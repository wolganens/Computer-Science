import java.io.*;
import java.net.*;
import java.util.Date;
import org.joda.time.DateTime;

class Client {
 public static void main(String argv[]) throws Exception{
  long data;
  String message;  
  for ( int i = 0; i< 3 ; i++){
  // Input stream - from user keyboard.
  BufferedReader fromUser = new BufferedReader(
    new InputStreamReader(System.in));
  
  // Creates the Client socket and binds to the server
  // at localhost, port 4444
  Socket clientSocket = new Socket("localhost", 4444);
  
  // Output stream to send the sentence through this.
  DataOutputStream toServer = new DataOutputStream(clientSocket.getOutputStream());
  
  Date date = new Date();  
  long clientTime = date.getTime();
  
  System.out.print("Client> ");
  message = fromUser.readLine();    
  
  toServer.writeBytes(Long.toString(clientTime) + '\n');
  toServer.writeBytes(message + '\n');
  
  clientSocket.close(); // TCP Client sends the close message to server.
  }
 }
}