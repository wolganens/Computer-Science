
import java.awt.Color;
import javax.swing.JFrame;

public class JanelaDoJogo extends JFrame {
    
    public static final int LARGURA = 800;
    public static final int ALTURA = 600;
    
    private static TelaDoJogo telaDoJogo = null;
    
    public JanelaDoJogo(){
        
        //inicializando as propriedades da janela
        this.setLayout(null);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setSize(LARGURA, ALTURA);
        this.setTitle("Imagem e eventos");
        this.setVisible(true);
        
        //criando e inicializando a tela do jogo
        telaDoJogo = new TelaDoJogo();
        telaDoJogo.setBackground(Color.WHITE);
        telaDoJogo.setSize(800,600);
        
        // usado para carregar toda a imagem em memória antes de desenhar na tela
        telaDoJogo.setDoubleBuffered(true); 
        
        this.add(telaDoJogo);
        
    }
    /*
    public void configurarMenu(){
        itemDeMenuNovoJogo.addActionListener(
            new ActionListener(){
                public void actionPerformed(ActionEvent evt){
                    tratarAcaoItemDeMenuNovoJogo();
                }
            }
        );
    }
    private void tratarAcaoItemDeMenuNovoJogo(){
       this.telaDoJogo.setBackground(new java.awt.Color(255,255,255));
    }*/
}
