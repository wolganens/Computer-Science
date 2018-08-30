
import java.awt.Color;
import java.awt.event.KeyEvent;
import javax.swing.JFrame;
import javax.swing.JPanel;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Jean
 */
public class JanelaDoJogo extends JFrame {
    
    public static final int LARGURA = 800;
    public static final int ALTURA = 600;
    
    public static final int ESQUERDA = KeyEvent.VK_LEFT;
    public static final int DIREITA = KeyEvent.VK_RIGHT;
    public static final int CIMA = KeyEvent.VK_UP;
    public static final int BAIXO = KeyEvent.VK_DOWN;
    
    TelaDoJogo telaDoJogo = null;
    
    public JanelaDoJogo(){
        
        //inicializando as propriedades da janela
        this.setLayout(null);
        this.setResizable(false);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setSize(LARGURA, ALTURA);
        this.setTitle("Imagem e eventos");
        this.setVisible(true);
        
        //criando e inicializando a área do jogo
        telaDoJogo = new TelaDoJogo();
        telaDoJogo.setBackground(Color.WHITE);
        telaDoJogo.setFocusable(true);
        telaDoJogo.setSize(800,600);
        telaDoJogo.setDoubleBuffered(true); /* usado para carregar toda a imagem em memória antes de desenhar na tela */
        this.add(telaDoJogo);
        
    }
    
}
