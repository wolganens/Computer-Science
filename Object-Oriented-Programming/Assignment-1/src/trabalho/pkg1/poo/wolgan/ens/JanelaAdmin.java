package trabalho.pkg1.poo.wolgan.ens;

import java.awt.AWTException;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;

public class JanelaAdmin extends JFrame implements ActionListener{
    JFrame frame;
    JLabel userLabel;
    JLabel passLabel;
    JTextField userTextField;
    JPasswordField passTextField;
    JButton buttonLogin;   
    JButton buttonClean;
    JPanel painel;   
    JLabel topo;
    private Vector<Admin> admins = new Vector();    
    private int posUsuario;
    
    public JanelaAdmin(){
        
    }
    
    public void criaPainelAdmin(){          
        frame = new JFrame();        
        frame.pack();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(220,200);        
        frame.setVisible(true);
        frame.setLocationRelativeTo(null);
        
        userLabel = new JLabel("Usuário:");
        passLabel = new JLabel("Senha:");
        topo = new JLabel("Entre com seus dados:");
        userTextField = new JTextField(10);
        passTextField = new JPasswordField(10);
        buttonLogin = new JButton("Acessar");
        buttonLogin.setActionCommand("ACESSAR");
        buttonLogin.addActionListener(this);

        buttonClean = new JButton("Limpar dados");
        buttonClean.setActionCommand("LIMPAR");
        buttonClean.addActionListener(this);

        painel = new JPanel();                
        painel.add(userLabel);
        painel.add(userTextField);
        painel.add(passLabel);
        painel.add(passTextField);
        painel.add(buttonLogin);
        painel.add(buttonClean);
        frame.add(painel);        
    }
     public void criaAdmins(){
        Admin adm1 = new Admin("admin","123");
        Admin adm2 = new Admin("admin2","1kk23456");
        this.admins.add(adm1);
        this.admins.add(adm2);
    }
     public void actionPerformed(ActionEvent e){
        String comando = (String) e.getActionCommand();
        if(comando.equals("ACESSAR")){
            String user = userTextField.getText();
            String pass = passTextField.getText();
            if(isSet(user)){                               
                if(verificaSenha(pass)){                                                     
                    try {                    
                        JanelaCadastro Cadastro = new JanelaCadastro(user);
                    } catch (AWTException ex) {
                        Logger.getLogger(JanelaAdmin.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
                else
                    JOptionPane.showMessageDialog(null, "Senha incorreta!");
            }
            else{
                JOptionPane.showMessageDialog(null, "Usario incorreto!");
            }
        }
        else if(comando.equals("LIMPAR")){
            userTextField.setText("");
            passTextField.setText("");
        }
    }
     public boolean isSet(String usuario){
        for(int i=0; i<this.admins.size(); i++){
            if(this.admins.elementAt(i).getUsuario().equals(usuario)){                
                this.posUsuario = i;
                return true;
            }
        }
        return false;
    }
    
    public boolean verificaSenha(String senha){
        return (this.admins.elementAt(this.posUsuario).getSenha().equals(senha));
    }
}
