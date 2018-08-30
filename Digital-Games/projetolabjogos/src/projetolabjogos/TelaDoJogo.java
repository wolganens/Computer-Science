import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Toolkit;
import java.util.Timer;
import java.util.TimerTask;
import javax.swing.ImageIcon;
import javax.swing.JPanel;

public class TelaDoJogo extends JPanel {
    /* constantes para o loop do jogo */
    private static final int ATRASO_INICIAL_ANTES_DE_COMECAR = 0;
    private static final int INTERVALO_ENTRE_CHAMADAS = 500;
    
    /* constantes com dimensões e posição do personagem */
    private static final int ALTURA_PERSONAGEM = 150;
    private static final int LARGURA_PERSONAGEM = 150;
    private static  int POSICAO_X_DO_PERSONAGEM = 100;
    private static final int POSICAO_Y_DO_PERSONAGEM = 350;
    
    /* variáveis para carregar as imagens */
    private Image fundo = null;
    private Image personagem = null;
    
    /* timer para controle do loop de jogo */
    private Timer timer;
    
    /* construtor da tela */
    public TelaDoJogo(){
        //carga da imagem de fundo em um ícone (primitivo da imagem)
        Image cargaFundo = Toolkit.getDefaultToolkit().getImage("fazenda.png");
        cargaFundo = cargaFundo.getScaledInstance(JanelaDoJogo.LARGURA, JanelaDoJogo.ALTURA, Image.SCALE_DEFAULT);
        ImageIcon iconeFundo = new ImageIcon(cargaFundo);
        
        //uso da imagem de fundo em si
        fundo = iconeFundo.getImage();
        
        //carga da imagem do personagem
        Image cargaPersonagem = Toolkit.getDefaultToolkit().getImage("walk-1.png");
        cargaPersonagem = cargaPersonagem.getScaledInstance(LARGURA_PERSONAGEM, ALTURA_PERSONAGEM, Image.SCALE_DEFAULT);
        ImageIcon iconePersonagem = new ImageIcon(cargaPersonagem);
        
        //uso da imagem do personagem em si
        personagem = iconePersonagem.getImage();
        
        //inicialização do timer
        timer = new Timer();
        timer.scheduleAtFixedRate(new TarefaAgendada(), ATRASO_INICIAL_ANTES_DE_COMECAR, INTERVALO_ENTRE_CHAMADAS);
    }
    
    /* método de atualização de tela invocado automaticamente pelo repaint() */
    @Override
    public void paintComponent(Graphics g){
        super.paintComponent(g);
        
        //conversão de tipo mais genérico
        Graphics2D g2d = (Graphics2D) g;
        
        //desenha as imagens
        g2d.drawImage(fundo, 0, 0, null);
        g2d.drawImage(personagem, POSICAO_X_DO_PERSONAGEM, POSICAO_Y_DO_PERSONAGEM, null);
        
        //garante atualização da tela nos variados sistemas de janela
        Toolkit.getDefaultToolkit().sync(); 
        
        //libera os recursos gráficos
        g.dispose(); 
    }
    
    /* classe interna que descreve o que deve ser feito no loop do jogo */
    private class TarefaAgendada extends TimerTask{
        //método com animações e lógica do jogo
        //será invocado no intervalo definido para invocação da tarefa
        @Override
        public void run(){
            
            do{
                POSICAO_X_DO_PERSONAGEM++;
                
            }while(POSICAO_X_DO_PERSONAGEM < 200);
            
            //atualiza as coisas na tela
            repaint(); 
        }
        
    }
    
}
