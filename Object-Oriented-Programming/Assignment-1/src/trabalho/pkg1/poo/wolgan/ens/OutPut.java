package trabalho.pkg1.poo.wolgan.ens;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectOutputStream;
import java.util.Formatter;
import java.util.FormatterClosedException;
import java.util.NoSuchElementException;
import java.util.Vector;

public final class OutPut {        
    private ObjectOutputStream output;
    private Vector<Torcedor> torcedor;    
    
    public OutPut(Vector<Torcedor> torcedor){
        this.torcedor = torcedor;
        openFile();
        addRecords();
        closeFile();
    }
    
    public void openFile(){
        try{
            this.output = new ObjectOutputStream(new FileOutputStream("saida.bin"));             
            
        }
        catch(IOException err1){
            System.out.println("erro ao abrir o arquivo: "+err1);
            System.exit(1);               
        }
    }
    
    public void addRecords(){                
        try{
            for ( int i = 0 ; i < torcedor.size() ; i++){             
                this.output.writeObject(this.torcedor.elementAt(i));
            }
        }catch(IOException err2){
            System.out.println("erro ao escrever no arquivo.");
            return;
        }catch(NoSuchElementException err2){
            System.err.println("Entrada invalida");            
        }
    }
    
    public void closeFile(){
        try{
            if(this.output != null)
            this.output.close();
        }catch(IOException err3){
            System.out.println("Erro ao fechar arquivo");
        }
    }
}