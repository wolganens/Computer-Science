
import java.awt.EventQueue;

public class Jogo {
    
    public static JanelaDoJogo janela = null;
    
    public static void main(String[] args) {
        EventQueue.invokeLater(new Runnable() {
            
            @Override
            public void run() {                
                JanelaDoJogo janela = new JanelaDoJogo();
                janela.setVisible(true);                
            }
        });
    }
    
}
