package trabalho.pkg1.poo.wolgan.ens;

import static com.sun.org.apache.xalan.internal.xsltc.compiler.sym.EOF;
import java.io.BufferedReader;
import java.io.EOFException;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.util.Vector;

public class InPut {
    private ObjectInputStream input;
    private Vector<Torcedor> record = new Vector<Torcedor>();
    private Torcedor temp;
    private int contador;
    //private BufferedReader br = null; 
        
        public InPut(){
            openFile();
            readRecords();
            closeFile();
        }
	public void openFile(){
            try{
                input = new ObjectInputStream(new FileInputStream("saida.bin"));                   
            }
            catch(IOException err1){
                System.err.println("Erro ao abrir arquivo");
            }
	}
        
        public Vector<Torcedor> readRecords(){            
            try{
                while(true){
                    this.temp = (Torcedor) input.readObject();
                    this.record.add(temp);
                }
            }
            catch(EOFException err2){
                return null; //se chegou a 'tentar' ler apos chegar ao fim do arquvio
            }
            catch(ClassCastException err0){
                System.out.println("impossível recuper dados do arquivo");
            }
            catch(NullPointerException npe){
                System.out.println("Impossivel acessar dados do objeto");
            }
            catch(ClassNotFoundException err3){
                System.out.println("Nao foi possivel criar o objeto");
            }
            catch(IOException err4){
                System.err.println("Erro durante leitura do arquivo");
            }
            return this.record;
	}
        public void closeFile(){
            try{
                if(input != null)
                input.close();
            }
            catch(IOException err5){
                System.out.println("Nao foi possivel fechar o arquivo");
                System.exit(1);
            }
	}
}
