package trabalho.pkg1.poo.wolgan.ens;

import java.awt.AWTException;
import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.Image;
import java.awt.PopupMenu;
import java.awt.Rectangle;
import java.awt.TextField;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.lang.reflect.Array;
import static java.rmi.Naming.list;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.Calendar;
import static java.util.Collections.list;
import java.util.Date;
import java.util.Vector;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JSpinner;
import javax.swing.JTextField;
import javax.swing.SpinnerDateModel;
import javax.xml.crypto.Data;

public class JanelaCadastro extends JFrame implements ActionListener{
    String cpf1;
    float parseFloat;
    private Vector<JComboBox> jcomboList = new Vector();
    private Vector<JTextField> jfieldsList = new Vector();
    private Vector<Torcedor> torcedorList;
    private static int contador = 0;
    private String nomeTorcedor;
    private String estado;
    private String cidade;
    private String email;
    
    JButton showCadastroContainer;
    JButton showTorcedores;
    JButton editTorcedores;
    JButton cadastrar;
        
    Container menu;
    JPanel relatorio;
    JFrame background;
    
    JLabel nomeTorcedorLabel;
    JTextField nome;
    
    JLabel labelData;
    JComboBox comboDia;
    JComboBox comboMes;
    JComboBox comboAno;
    
    JLabel labelSexo;
    JComboBox comboSexo;
    
    JLabel labelCivil;
    JComboBox comboCivil;
    
    JLabel labelTelefone;
    JTextField textFieldTelefone;
       
    JLabel cpfTorcedor;
    JTextField cpf;
    
    JLabel estadoTorcedor;
    JTextField estadoField;
    
    JLabel cidadeTorcedor;
    JTextField cidadeField;
    
    JLabel cepTorcedor;
    JTextField cep;
    
    JLabel labelBairro;
    JTextField textFieldBairro;
    
    JLabel labelEndereco;
    JTextField textFieldEndereco;
    
    JLabel labelComplemento;
    JTextField textFieldComplemento;
    
    JLabel labelNumero;
    JTextField textFieldNumero;
    
    JLabel tatuTorcedor;
    JTextField tatu;
    
    JLabel labelAltura;
    JTextField textFieldAltura;
    
    JLabel labelCorCabelo;
    JTextField textFieldCorCabelo;
    
    JLabel marcaTorcedor;
    JTextField marca;
    
    JLabel labelAcessorio;
    JTextField textFieldAcessorio;
    
    JLabel labelEmail;
    JTextField textFieldEmail;
    
    JLabel labelRg;
    JTextField textFieldRg;
    
    JButton limparDados;
    JLabel fieldDataLabel;
    private JSpinner fieldData;
    
    Date now;
   
    JPanel exibeTorcedorJanela;
    JPanel editarTorcedor;
    JPanel content;
    
    String admin;
    
    public JanelaCadastro(String admin) throws AWTException{       
        this.admin = admin;                
        JOptionPane.showMessageDialog(null, "Bem vindo ao sistema "+admin);
        InPut carrega = new InPut();
        this.torcedorList = carrega.readRecords();
        this.contador = torcedorList.size();
        //INICIO - CriaÃ§Ã£o do frame(background)
        background = new JFrame();       
        background.setSize(660, 850);
        background.setLayout(null);
        background.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);        
        background.setLocationRelativeTo(null);
        background.setVisible(true);
        //FIM - CriaÃ§Ã£o do frame(background)
        
        //INICIO - CRIA BOTAO PARA ABRIR JANELA DE INSERÃ‡ÃƒO DE TORCEDOR
        showCadastroContainer = new JButton("Novo torcedor");
        showCadastroContainer.setBounds(new Rectangle(120,10,200,25));
        showCadastroContainer.setSize(125,30);
        showCadastroContainer.setActionCommand("showCadastroTorcedor");
        showCadastroContainer.addActionListener(this);
        background.add(showCadastroContainer);
        //FIM - CRIA BOTAO PARA ABRIR JANELA DE INSERÃ‡ÃƒO DE TORCEDOR
        
        //INICIO - CRIA BOTAO PARA ABRIR JANELA DE EXIBIÃ‡ÃƒO DE TORCEDOR
        showTorcedores = new JButton("Exibir Torcedores");
        showTorcedores.setBounds(new Rectangle(250,10,200,25));
        showTorcedores.setSize(145,30);
        showTorcedores.setActionCommand("showTorcedores");
        showTorcedores.addActionListener(this);        
        background.add(showTorcedores);
        //FIM - CRIA BOTAO PARA ABRIR JANELA DE EXIBIÃ‡ÃƒO DE TORCEDOR
        
        //INICIO - CRIA BOTAO PARA ABRIR JANELA DE EDIÃ‡ÃƒO DE TORCEDOR
        editTorcedores = new JButton("Editar Dados");
        editTorcedores.setBounds(new Rectangle(400,10,200,25));
        editTorcedores.setSize(125,30);
        editTorcedores.setActionCommand("editTorcedor");
        editTorcedores.addActionListener(this);
        background.add(editTorcedores);
        //FIM - CRIA BOTAO PARA ABRIR JANELA DE EDIÃ‡ÃƒO DE TORCEDOR
        
        //INICIO - CRIA CONTAINER PARA EXIBIR OS CAMPOS DE CADASTRO DO TORCEDOR
        content = new JPanel();
        //content = getContentPane();
        content.setLayout(null);       
        content.setSize(660, 550);
        content.setBounds(20, 70, 660, 540);
        content.setVisible(true);
        //FIM - CRIA CONTAINER PARA EXIBIR OS CAMPOS DE CADASTRO DO TORCEDOR
        
        //INICIO - CRIA LABEL E CAMPOS PARA CADASTRO DO TORCEDOR
        nomeTorcedorLabel = new JLabel("Nome:");
        nomeTorcedorLabel.setBounds(new Rectangle(0,20,100,25));
        content.add(nomeTorcedorLabel);        
        nome = new JTextField();
        nome.setBounds(new Rectangle(40,20,150,25));
        content.add(nome);
        jfieldsList.add(nome);
        
        now = new Date();  
        SpinnerDateModel model = new SpinnerDateModel(now, null, now, Calendar.DAY_OF_WEEK);  
        this.fieldData = new JSpinner(model);
        this.fieldData.setEditor(new JSpinner.DateEditor(this.fieldData, "dd/MM/yyyy"));
        this.fieldData.setBounds(new Rectangle(320,20,150,25));
        content.add(this.fieldData, null);
        
        labelData = new JLabel("Data de Nascimento:");
        labelData.setBounds(new Rectangle(195,20,180,25));
        content.add(labelData);       
        labelSexo = new JLabel("Sexo:");
        labelSexo.setBounds(new Rectangle(0,50,100,25));
        content.add(labelSexo);
        String[] listaSexo = {"Masculino", "Feminino"};
        comboSexo = new JComboBox(listaSexo);
        comboSexo.setBounds(new Rectangle(40,50,100,25));
        content.add(comboSexo);
        
        labelCivil = new JLabel("Estado Civil:");
        labelCivil.setBounds(new Rectangle(195,50,150,25));
        content.add(labelCivil);
        String[] listaCivil = {"Solteiro", "Casado", "Divorciado"};
        comboCivil = new JComboBox(listaCivil);
        comboCivil.setBounds(new Rectangle(320,50,100,25));
        content.add(comboCivil);
        
        labelTelefone = new JLabel("DDD+ Telefone");
        labelTelefone.setBounds(new Rectangle(0,80,100,25));
        content.add(labelTelefone);        
        textFieldTelefone = new JTextField();
        textFieldTelefone.setBounds(new Rectangle(120,80,150,25));
        content.add(textFieldTelefone);
        jfieldsList.add(textFieldTelefone);
        
        cpfTorcedor = new JLabel("CPF:");
        cpfTorcedor.setBounds(new Rectangle(275,80,200,25));
        content.add(cpfTorcedor);
        cpf = new JTextField();
        cpf.setBounds(new Rectangle(320,80,200,25));
        content.add(cpf);
        jfieldsList.add(cpf);
        
        cepTorcedor = new JLabel("CEP:");
        cepTorcedor.setBounds(new Rectangle(0,110,100,25));
        content.add(cepTorcedor);
        cep = new JTextField();
        cep.setBounds(new Rectangle(120,110,120,25));
        content.add(cep);
        jfieldsList.add(cep);

        estadoTorcedor = new JLabel("Estado:");
        estadoTorcedor.setBounds(new Rectangle(275,110,200,25));
        content.add(estadoTorcedor);
        estadoField = new JTextField();
        estadoField.setBounds(new Rectangle(320,110,200,25));
        content.add(estadoField);
        jfieldsList.add(estadoField);

        cidadeTorcedor = new JLabel("Cidade:");
        cidadeTorcedor.setBounds(new Rectangle(0,140,100,25));
        content.add(cidadeTorcedor);
        cidadeField = new JTextField();
        cidadeField.setBounds(new Rectangle(120,140,120,25));
        content.add(cidadeField);
        jfieldsList.add(cidadeField);
        
        labelBairro = new JLabel("Bairro:");
        labelBairro.setBounds(new Rectangle(275,140,200,25));
        content.add(labelBairro);
        textFieldBairro = new JTextField();
        textFieldBairro.setBounds(new Rectangle(320,140,200,25));
        content.add(textFieldBairro);
        jfieldsList.add(textFieldBairro);       
        
        labelComplemento = new JLabel("Complemento:");
        labelComplemento.setBounds(new Rectangle(0,170,100,25));
        content.add(labelComplemento);
        textFieldComplemento = new JTextField();
        textFieldComplemento.setBounds(new Rectangle(120,170,120,25));
        content.add(textFieldComplemento);
        jfieldsList.add(textFieldComplemento);
        
        labelNumero = new JLabel("Número:");
        labelNumero.setBounds(new Rectangle(275,170,200,25));
        content.add(labelNumero);
        textFieldNumero = new JTextField();
        textFieldNumero.setBounds(new Rectangle(330,170,190,25));
        content.add(textFieldNumero);
        jfieldsList.add(textFieldNumero);
        
        
        tatuTorcedor = new JLabel("Tatuagem:");
        tatuTorcedor.setBounds(new Rectangle(0,230,200,25));
        content.add(tatuTorcedor);
        tatu = new JTextField();
        tatu.setBounds(new Rectangle(120,230,200,25));
        content.add(tatu);
        jfieldsList.add(tatu);
        
        marcaTorcedor = new JLabel("Mancha:");
        marcaTorcedor.setBounds(new Rectangle(325,230,200,25));
        content.add(marcaTorcedor);
        marca = new JTextField();
        marca.setBounds(new Rectangle(370,230,200,25));
        content.add(marca);
        jfieldsList.add(marca);
        
        labelAltura = new JLabel("Altura");
        labelAltura.setBounds(new Rectangle(0,260,200,25));
        content.add(labelAltura);
        textFieldAltura = new JTextField();
        textFieldAltura.setBounds(new Rectangle(120,260,200,25));
        content.add(textFieldAltura);
        jfieldsList.add(textFieldAltura);
        
        labelCorCabelo = new JLabel("Cor do Cabelo:");
        labelCorCabelo.setBounds(new Rectangle(325,260,200,25));
        content.add(labelCorCabelo);
        textFieldCorCabelo = new JTextField();
        textFieldCorCabelo.setBounds(new Rectangle(410,260,160,25));
        content.add(textFieldCorCabelo);
        jfieldsList.add(textFieldCorCabelo);
        
        labelAcessorio = new JLabel("Acessório");
        labelAcessorio.setBounds(new Rectangle(0,290,200,25));
        content.add(labelAcessorio);
        textFieldAcessorio = new JTextField();
        textFieldAcessorio.setBounds(new Rectangle(120,290,200,25));
        content.add(textFieldAcessorio);
        jfieldsList.add(textFieldAcessorio);
        
        labelEmail = new JLabel("E-mail:");
        labelEmail.setBounds(new Rectangle(325,290,200,25));
        content.add(labelEmail);
        textFieldEmail = new JTextField();
        textFieldEmail.setBounds(new Rectangle(410,290,160,25));
        content.add(textFieldEmail);
        jfieldsList.add(textFieldEmail);
        
        labelRg = new JLabel("RG");
        labelRg.setBounds(new Rectangle(0,320,200,25));
        content.add(labelRg);
        textFieldRg = new JTextField();
        textFieldRg.setBounds(new Rectangle(120,320,200,25));
        content.add(textFieldRg);
        jfieldsList.add(textFieldRg);
        
        cadastrar = new JButton("Cadastrar");
        cadastrar.setBounds(new Rectangle(0,350,200,25));
        cadastrar.setSize(110,30);
        cadastrar.setActionCommand("CADASTRAR");
        cadastrar.addActionListener(this);
        content.add(cadastrar);        
        
        limparDados = new JButton("Limpar campos");
        limparDados.setBounds(new Rectangle(120,350,200,25));
        limparDados.setSize(200,30);
        limparDados.setActionCommand("LIMPAR");
        limparDados.addActionListener(this);
        content.add(limparDados);       
        background.add(content);
    }
           
    public void actionPerformed(ActionEvent ae){
        String comando = ae.getActionCommand();
        if ("showCadastroTorcedor".equals(comando)) {
            if(background.isAncestorOf(exibeTorcedorJanela)){                                   
                background.remove(exibeTorcedorJanela);                                                
            }
            if(background.isAncestorOf(editarTorcedor)){               
                background.remove(editarTorcedor);                                
            }            
            background.add(content);
        }
        else if("LIMPAR".equals(comando)){
            for(int i = 0 ; i<jfieldsList.size() ; i++)
                this.jfieldsList.elementAt(i).setText("");
        }
        else if("showTorcedores".equals(comando)){                        
            ExibeTorcedor listaTorcedores = new ExibeTorcedor(this.torcedorList);            
        }
        else if("editTorcedor".equals(comando)){                  
            EditaTorcedor editaTorcedorJanela = new EditaTorcedor(this.torcedorList);                       
        }
        else if("CADASTRAR".equals(comando)){
            try{
                this.recuperarDados();
            }
            catch(IllegalArgumentException iae){
                JOptionPane.showMessageDialog(null, iae.getMessage()); 
            }
            catch(ValidMailException vme){
                JOptionPane.showMessageDialog(null, vme.getMessage()); 
            }
            catch(Exception ex){
                JOptionPane.showMessageDialog(null, ex.getMessage()); 
            }
        }
    }


    private void recuperarDados() throws IllegalArgumentException, ValidMailException, NumberFormatException{

        for(int i=0 ; i<jfieldsList.size(); i++)
            if(this.jfieldsList.elementAt(i).getText().equals(""))
                throw new IllegalArgumentException("Verifique os campos vazios!");                        


        this.nomeTorcedor = this.nome.getText();                    
        this.estado = this.estadoField.getText();
        this.cidade = this.cidadeField.getText();          
        if(!(ValidMail.ValidMaila(this.textFieldEmail.getText()))){
            new ValidMailException("Digite um email válido!");
            System.out.println("entrou no if");
        }
                               
        this.email = this.textFieldEmail.getText();                                          
        this.cpf1 = this.cpf.getText();                                
        String alto = this.textFieldAltura.getText();


        int cpfInt = Integer.parseInt(cpf1);
        int Telefone = Integer.parseInt(this.textFieldTelefone.getText());
        this.parseFloat = Float.parseFloat(alto);

        String acessorio = this.textFieldAcessorio.getText();
        String corCabelo = this.textFieldCorCabelo.getText();
        String tatuagem = this.tatu.getText();
        String mancha = this.marca.getText();
        Date data = (Date) this.fieldData.getValue();
        String rg = this.textFieldRg.getText();            
        String sexo = comboSexo.getSelectedItem().toString();
        String civil = comboCivil.getSelectedItem().toString();
        String tel = this.textFieldTelefone.getText();            
        String cep = this.cep.getText();            
        String residencia = this.textFieldNumero.getText();
        int resid = Integer.parseInt(residencia);
        String complemento = this.textFieldComplemento.getText();
        String bairro = this.textFieldBairro.getText();         
        

        //Torcedor obj1 = new Torcedor(nomeTorcedor,civil,bairro,estado,cidade,cpf,alto,acessorio,corCabelo,tatuagem,mancha,sexo,complemento,resid,tel,cep,dia,mes,ano,rg);   
        this.contador += 1;
        Torcedor obj1 = new Torcedor(this.contador);
        obj1.setNome(nomeTorcedor);
        obj1.setEstado(estado);
        obj1.setCidade(cidade);
        obj1.setEmail(email);
        obj1.setCpf(cpf1);
        obj1.setAltura(parseFloat);
        obj1.setAcessorio(acessorio);
        obj1.setCorCabelo(corCabelo);
        obj1.setTatuagem(tatuagem);
        obj1.setMancha(mancha);
        obj1.setData(data);
        obj1.setRg(rg);
        obj1.setSexo(sexo);
        obj1.setEstadoCivil(civil);
        obj1.setTelefone(tel);
        obj1.setCep(cep);
        obj1.setNumeroResidencia(resid);
        obj1.setComplemento(complemento);
        obj1.setBairro(bairro);
        obj1.seCadastradoPor(this.admin);
        torcedorList.add(obj1);
        OutPut gravaTorcedor = new OutPut(this.torcedorList);
        new InPut().readRecords();
        JOptionPane.showMessageDialog(null, "Torcedor cadastrado com sucesso");

        for(int i=0; i<jfieldsList.size(); i++)
            this.jfieldsList.elementAt(i).setText("");
    }
}