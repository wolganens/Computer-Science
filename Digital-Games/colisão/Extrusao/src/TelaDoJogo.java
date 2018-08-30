
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;
import javax.swing.ImageIcon;
import javax.swing.JPanel;

public class TelaDoJogo extends JPanel {
    
    private static final int ATRASO_INICIAL = 0;
    private static final int INTERVALO = 33;
    private static final int X_PONTUACAO = 300;
    private static final int Y_PONTUACAO = 30;
    
    private Image fundo = null;
    private Timer timer;
    private Personagem personagem = null;
    private Parede parede = null;
    private ArrayList<Tiro> tiros = null;
    private int pontuacao = 0;
    
    public TelaDoJogo(){
        //carga da imagem de fundo em um ícone (primitivo da imagem)
        Image cargaFundo = Toolkit.getDefaultToolkit().getImage("fazenda.png");
        cargaFundo = cargaFundo.getScaledInstance(JanelaDoJogo.LARGURA, JanelaDoJogo.ALTURA, Image.SCALE_DEFAULT);
        ImageIcon iconeFundo = new ImageIcon(cargaFundo);
        
        //uso da imagem de fundo em si
        fundo = iconeFundo.getImage();
        
        personagem = new Personagem();
        parede = new Parede();
        tiros = new ArrayList<>();
        
        //configuração do timer
        timer = new Timer();
        timer.scheduleAtFixedRate(new TarefaAgendada(), ATRASO_INICIAL, INTERVALO);
        
        //configura os listeners de teclado
        this.addKeyListener(
                new KeyListener(){
                    @Override
                    public void keyPressed(KeyEvent evento){
                        personagem.comecarAAndar(evento.getKeyCode());
                        /* se apertou espaço, atira */
                        if(evento.getKeyCode() == KeyEvent.VK_SPACE){
                            tiros.add(new Tiro(personagem));
                        }
                    }
                    
                    @Override
                    public void keyReleased(KeyEvent evento){
                        personagem.pararDeAndar(evento.getKeyCode());
                    }
                    
                    @Override
                    public void keyTyped(KeyEvent evento){
                    }
                }
        );
    }
    
    @Override
    public void paintComponent(Graphics g){
        super.paintComponent(g);
        
        desenharCoisas(g);
    }
    
    
    private void desenharCoisas(Graphics g){
        Graphics2D g2d = (Graphics2D) g;
        
        //desenha as imagens
        g2d.drawImage(fundo, 0, 0, null);
        g2d.drawImage(personagem.getImage(), personagem.getX(), personagem.getY(), null);
        g2d.drawImage(parede.getImage(), parede.getX(), parede.getY(), null);
        for(int i=0; i<tiros.size(); i++){
            Tiro tiro = tiros.get(i);
            /* só desenha inimigos vivos */
            if(tiro.isDisparada()){
                g2d.drawImage(tiro.getImage(), tiro.getX(), tiro.getY(), null);
            }
        }
        g2d.setFont(new Font("Serif", Font.PLAIN, 40));
        g2d.drawString("Pontos: "+pontuacao, X_PONTUACAO, Y_PONTUACAO);
        
        Toolkit.getDefaultToolkit().sync(); /* garante atualização da tela nos variados sistemas de janela */
        g.dispose(); /* libera os recursos gráficos */
    }
    
    private class TarefaAgendada extends TimerTask{
        
        //método com animações e lógica do jogo
        //será invocado no intervalo definido para invocação da tarefa
        @Override
        public void run(){
            /* atualiza movimento do personagem */
            if(personagem.isAndandoParaDireita()){
                personagem.moverParaDireita();
            }
            if(personagem.isAndandoParaEsquerda()){
                personagem.moverParaEsquerda();
            }
            if(personagem.isAndandoParaCima()){
                personagem.moverParaCima();
            }
            if(personagem.isAndandoParaBaixo()){
                personagem.moverParaBaixo();
            }
            /* verifica colisões */
            for(int i=0; i<tiros.size(); i++){
                if(tiros.get(i).isDisparada() && parede.testarColisao(tiros.get(i))){
                    tiros.get(i).sumir();
                    pontuacao++;
                }
            }
            /* atualiza posição dos tiros */
            for(int i=0; i<tiros.size(); i++){
                tiros.get(i).mover();
            }
            
            repaint(); /* atualiza as coisas na tela */
        }
        
    }
    
}
