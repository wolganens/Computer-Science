package trabalho.pkg1.poo.wolgan.ens;

import static java.lang.Character.isAlphabetic;
import javax.swing.JOptionPane;

public class ValidMail{

    ValidMail(){}

    public static boolean ValidMaila(String email){

        char[] toCharArray = email.toCharArray();
        int contaArroba=0, contaPonto=0;

        for(int i=0; i<toCharArray.length; i++){
            if(toCharArray[i] == '@')
                contaArroba++;

            if(toCharArray[i] == '.')
                contaPonto++;
        }

        if(contaArroba != 1 || contaPonto < 1)                
            return false;
        
        return true;
    }
}
