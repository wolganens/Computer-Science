
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.Toolkit;
import javax.swing.ImageIcon;

public class Parede {
    
    private static final int ALTURA_PAREDE = 400;
    private static final int LARGURA_PAREDE = 20;
    
    private Image imagem = null;
    
    private int x = 600;
    private int y = 100;
    
    public Parede(){
        //carga do personagem
        Image cargaParede = Toolkit.getDefaultToolkit().getImage("parede.png");
        cargaParede = cargaParede.getScaledInstance(LARGURA_PAREDE, ALTURA_PAREDE, Image.SCALE_DEFAULT);
        ImageIcon iconeParede = new ImageIcon(cargaParede);
        
        //uso da imagem do personagem
        imagem = iconeParede.getImage();
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
        return ALTURA_PAREDE;
    }
    
    public int getLargura(){
        return LARGURA_PAREDE;
    }
    
    /**
     * Uso de varredura translacional (extrusão) para prever colisões baseadas no deslocamento de objetos
     * @param tiro
     * @return 
     */
    public boolean testarColisao(Tiro tiro){
        Rectangle areaPersonagem = new Rectangle(this.getX(), this.getY(), this.getLargura(), this.getAltura());
        /* retângulo gerado pela varredura translacional (extrusão) do tiro em função de sua velocidade (deslocamento) à direita no eixo X */
        Rectangle areaTiro = new Rectangle(tiro.getX(), tiro.getY(), tiro.getLargura()+tiro.getDeslocamento(), tiro.getAltura());
        return areaPersonagem.intersects(areaTiro);
    }
    
    
}
