
import java.awt.Image;
import java.awt.Toolkit;
import javax.swing.ImageIcon;

public class Tiro {
    
    private static final int ALTURA_TIRO = 20;
    private static final int LARGURA_TIRO = 20;
    private static final int DESLOCAMENTO = 50;
    
    private static Image imagem = null;
    
    private int x = 0;
    private int y = 0;
    
    private boolean disparada = true;
    
    public Tiro(Personagem origem){
        /* como "imagem" é estática, só precisa fazer uma vez se ela não tiver sido inicializada */
        if(imagem == null){
            //carga do tiro
            Image cargaPersonagem = Toolkit.getDefaultToolkit().getImage("bala.png");
            cargaPersonagem = cargaPersonagem.getScaledInstance(LARGURA_TIRO, ALTURA_TIRO, Image.SCALE_DEFAULT);
            ImageIcon iconePersonagem = new ImageIcon(cargaPersonagem);

            //uso da imagem do tiro
            imagem = iconePersonagem.getImage();
        }
        
        //aparece à direita da origem, na metade da sua altura
        this.x = origem.getX()+origem.getLargura()/2;
        this.y = origem.getY()+(origem.getAltura()/2);
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
        return ALTURA_TIRO;
    }
    
    public int getLargura(){
        return LARGURA_TIRO;
    }
    
    public int getDeslocamento(){
        return DESLOCAMENTO;
    }
    
    public void sumir(){
        this.disparada = false;
    }
    
    public void mover(){
        this.x += DESLOCAMENTO;
    }
    
    public boolean isDisparada(){
        return this.disparada;
    }
    
}
