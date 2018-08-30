
import java.awt.Image;
import java.awt.Toolkit;
import java.util.Random;
import javax.swing.ImageIcon;

public class Inimigo {
    
    private static final int ALTURA_INIMIGO = 50;
    private static final int LARGURA_INIMIGO = 50;
    
    private Random geradorAleatorio = new Random();
    
    private Image imagem = null;
    
    private int x = gerarXAleatorio();
    private int y = gerarYAleatorio();
    
    private boolean vivo = true;
    
    public Inimigo(){
        //carga do personagem
        Image cargaPersonagem = Toolkit.getDefaultToolkit().getImage("joaninha.png");
        cargaPersonagem = cargaPersonagem.getScaledInstance(LARGURA_INIMIGO, ALTURA_INIMIGO, Image.SCALE_DEFAULT);
        ImageIcon iconePersonagem = new ImageIcon(cargaPersonagem);
        
        //uso da imagem do personagem
        imagem = iconePersonagem.getImage();
    }
    
    public Image getImage(){
        return this.imagem;
    }
    
    public int getX(){
        return this.x;
    }
    
    public int getY(){
        return this.y;
    }
    
    public int getAltura(){
        return ALTURA_INIMIGO;
    }
    
    public int getLargura(){
        return LARGURA_INIMIGO;
    }
    
    public void matar(){
        this.vivo = false;
    }
    
    public boolean isVivo(){
        return this.vivo;
    }
    
    public int gerarXAleatorio(){
        return geradorAleatorio.nextInt(JanelaDoJogo.LARGURA-LARGURA_INIMIGO);
    }
    
    public int gerarYAleatorio(){
        return geradorAleatorio.nextInt(JanelaDoJogo.ALTURA-ALTURA_INIMIGO);
    }
    
}
