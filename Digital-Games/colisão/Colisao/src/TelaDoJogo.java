
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.Timer;
import java.util.TimerTask;
import javax.swing.ImageIcon;
import javax.swing.JPanel;

public class TelaDoJogo extends JPanel {
    
    private static final int ATRASO_INICIAL = 0;
    private static final int INTERVALO = 50;
    private static final int QUANTIDADE_DE_INIMIGOS = 5;
    private static final int X_PONTUACAO = 300;
    private static final int Y_PONTUACAO = 30;
    
    private Image fundo = null;
    private Timer timer;
    private Personagem personagem = null;
    private Inimigo[] inimigos = new Inimigo[QUANTIDADE_DE_INIMIGOS];
    private int pontuacao = 0;
    
    public TelaDoJogo(){
        //carga da imagem de fundo em um ícone (primitivo da imagem)
        Image cargaFundo = Toolkit.getDefaultToolkit().getImage("fazenda.png");
        cargaFundo = cargaFundo.getScaledInstance(JanelaDoJogo.LARGURA, JanelaDoJogo.ALTURA, Image.SCALE_DEFAULT);
        ImageIcon iconeFundo = new ImageIcon(cargaFundo);
        
        //uso da imagem de fundo em si
        fundo = iconeFundo.getImage();
        
        personagem = new Personagem();
        
        for(int i=0; i<QUANTIDADE_DE_INIMIGOS; i++){
            inimigos[i] = new Inimigo();
        }
        
        //configuração do timer
        timer = new Timer();
        timer.scheduleAtFixedRate(new TarefaAgendada(), ATRASO_INICIAL, INTERVALO);
        
        //configura os listeners de teclado
        this.addKeyListener(
                new KeyListener(){
                    @Override
                    public void keyPressed(KeyEvent evento){
                        personagem.comecarAAndar(evento.getKeyCode());
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
        for(int i=0; i<QUANTIDADE_DE_INIMIGOS; i++){
            /* só desenha inimigos vivos */
            if(inimigos[i].isVivo()){
                g2d.drawImage(inimigos[i].getImage(), inimigos[i].getX(), inimigos[i].getY(), null);
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
            for(int i=0; i<QUANTIDADE_DE_INIMIGOS; i++){
                /* só testa colisão com inimigos vivos */
                if(inimigos[i].isVivo() && personagem.testarColisao(inimigos[i])){
                    inimigos[i].matar();
                    pontuacao++;
                }
            }
            
            repaint(); /* atualiza as coisas na tela */
        }
        
    }
    
}
