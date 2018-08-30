package trabalho.pkg1.poo.wolgan.ens;

import java.awt.Container;
import java.awt.Dimension;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;


public class ExibeTorcedor extends JFrame{
    private JTextArea relatorio;
    private JScrollPane areaScrollPane;
    JFrame satanas;
    JFrame background;   
    
    public ExibeTorcedor(Vector<Torcedor> torcedor){        
        satanas = new JFrame();
        satanas.setLayout(null);
        satanas.setSize(550, 550);               
        satanas.setLocationRelativeTo(null);
        satanas.setVisible(true);  
        
        this.relatorio = new JTextArea();
        this.areaScrollPane = new JScrollPane(relatorio);

        areaScrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        areaScrollPane.setPreferredSize(new Dimension(250, 250));
        areaScrollPane.setBounds(new Rectangle(1, 1, 550, 550));
        satanas.add(areaScrollPane, null);        
	String texto = "";
        for(int i=0; i<torcedor.size(); i++){
            Torcedor objr = torcedor.elementAt(i);
            texto += "ID:"+objr.getId()+"\n"+"Nome:"+objr.getNome()+"\n"+ "Estado:"+objr.getEstado()+"\n"+"Cidade: "+objr.getCidade()+"\n"+"Sexo:"+objr.getSexo()+"\n"+"Telefone:"+objr.getTelefone()+"\n"+"Tatuagem:"+objr.getTatuagem()+"\n"+"Altura:"+objr.getAltura()+"\n"+"Data de nascimento:"+objr.getData()+"\n"+"Email:"+objr.getEmail()+"\n"+"Este torcedor foi cadastrado por:"+objr.getCadastradoPor()+"\n---------------------------------------------\n";
        }
        relatorio.append(texto);       
    } 
}
