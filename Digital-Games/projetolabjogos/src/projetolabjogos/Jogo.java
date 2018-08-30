
import java.awt.EventQueue;

public class Jogo {
    
    public static JanelaDoJogo janela = null;
    
    public static void main(String[] args) {
        
        //inicializa a interface na 'thread AWT-EventQueue-0' em vez da 'thread main'
        EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {                
                JanelaDoJogo janela = new JanelaDoJogo();
                janela.setVisible(true);                
            }
        });
        
    }
    
}
