
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.Toolkit;
import javafx.scene.shape.Circle;
import javax.swing.ImageIcon;

public class Personagem {
    
        
    private static final int ALTURA_PERSONAGEM = 150;
    private static final int LARGURA_PERSONAGEM = 150;
    
    private static final int POSICAO_INICIAL_X_DO_PERSONAGEM = 0;
    private static final int POSICAO_Y_DO_PERSONAGEM = 350;
    
    private static final int MOVIMENTO_DO_PERSONAGEM = 5;
    
    private Image imagem = null;
    private int x = POSICAO_INICIAL_X_DO_PERSONAGEM;
    private int y = POSICAO_Y_DO_PERSONAGEM;
    private boolean andandoParaDireita = false;
    private boolean andandoParaEsquerda = false;
    private boolean andandoParaCima = false;
    private boolean andandoParaBaixo = false;
    
    public Personagem(){
        //carga do personagem
        Image cargaPersonagem = Toolkit.getDefaultToolkit().getImage("louvadeus.png");
        cargaPersonagem = cargaPersonagem.getScaledInstance(LARGURA_PERSONAGEM, ALTURA_PERSONAGEM, Image.SCALE_DEFAULT);
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
        return ALTURA_PERSONAGEM;
    }
    
    public int getLargura(){
        return LARGURA_PERSONAGEM;
    }
    
    public boolean isAndandoParaDireita(){
        return this.andandoParaDireita;
    }
    
    public boolean isAndandoParaEsquerda(){
        return this.andandoParaEsquerda;
    }
    
    public boolean isAndandoParaCima(){
        return this.andandoParaCima;
    }
    
    public boolean isAndandoParaBaixo(){
        return this.andandoParaBaixo;
    }
    
    public void moverParaDireita(){
        this.x += MOVIMENTO_DO_PERSONAGEM;
    }
    
    public void moverParaEsquerda(){
        this.x -= MOVIMENTO_DO_PERSONAGEM;
    }
    
    public void moverParaCima(){
        this.y -= MOVIMENTO_DO_PERSONAGEM;
    }
    
    public void moverParaBaixo(){
        this.y += MOVIMENTO_DO_PERSONAGEM;
    }
    
    public void comecarAAndar(int direcao){
        switch(direcao){
            //vale lembrar que ESQUERDA e código da tecla esquerda do teclado são os mesmos
            case JanelaDoJogo.ESQUERDA:
                this.andandoParaEsquerda = true;
                break;
            //o mesmo de cima vale para DIREITA
            case JanelaDoJogo.DIREITA:
                this.andandoParaDireita = true;
                break;
            case JanelaDoJogo.CIMA:
                this.andandoParaCima = true;
                break;
            case JanelaDoJogo.BAIXO:
                this.andandoParaBaixo = true;
                break;
            default:
        }
    }
    
    public void pararDeAndar(int direcao){
        switch(direcao){
            case JanelaDoJogo.ESQUERDA:
                this.andandoParaEsquerda = false;
                break;
            case JanelaDoJogo.DIREITA:
                this.andandoParaDireita = false;
                break;
            case JanelaDoJogo.CIMA:
                this.andandoParaCima = false;
                break;
            case JanelaDoJogo.BAIXO:
                this.andandoParaBaixo = false;
                break;
            default:
        }
    }
    
    /**
     * Testa colisão por interseção dos retângulos de suas imagens
     * @param inimigo
     * @return 
     */
    public boolean testarColisao(Inimigo inimigo){        
        Circle areaPersonagem = new Circle(this.getX(), this.getY(), this.getLargura());
        Circle areaInimigo = new Circle(inimigo.getX(), inimigo.getY(), inimigo.getLargura());
        System.out.println(areaInimigo.radiusProperty());
        //return areaPersonagem.intersects(areaInimigo);
        return true;
    }
    
}
