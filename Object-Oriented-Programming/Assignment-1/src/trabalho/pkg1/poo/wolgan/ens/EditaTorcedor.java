package trabalho.pkg1.poo.wolgan.ens;

import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Calendar;
import java.util.Date;
import java.util.Vector;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSpinner;
import javax.swing.JTextField;
import javax.swing.SpinnerDateModel;

public class EditaTorcedor extends JFrame implements ActionListener{
    JLabel nomeTorcedor;
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
    JTextField estado;
    
    JLabel cidadeTorcedor;
    JTextField cidade;
    
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
    
    JLabel fieldDataLabel;
    private JSpinner fieldData;
    
    Date now;
    
    JButton limparDados;
    JButton cadastrar;
    
    JFrame editaPainelJPanel;
    
    JLabel encontraTorcedor;
    JTextField buscaTorcedor;
    JButton procuraTorcedor; 
    
    private Vector<Torcedor> torcedorList;
    
    int posicaoUsuario;
    String procuraUuario;   
    
    public  EditaTorcedor(Vector<Torcedor> torcedorList){  
        this.torcedorList = torcedorList;
        editaPainelJPanel = new JFrame();
        editaPainelJPanel.setLayout(null);       
        editaPainelJPanel.setSize(660, 550);
        editaPainelJPanel.setBounds(20, 70, 660, 540);
        editaPainelJPanel.setLocationRelativeTo(null);
        editaPainelJPanel.setVisible(true);                
        
        encontraTorcedor = new JLabel("Digite o nome do Torcedor:");
        encontraTorcedor.setBounds(new Rectangle(10,0,160,25));
        editaPainelJPanel.add(encontraTorcedor);
        
        buscaTorcedor = new JTextField();
        buscaTorcedor.setBounds(new Rectangle(180,0,100,25));
        editaPainelJPanel.add(buscaTorcedor);
        
        procuraTorcedor = new JButton("Procurar");
        procuraTorcedor.setBounds(new Rectangle(285,0,100,25));
        procuraTorcedor.setActionCommand("Buscar");
        procuraTorcedor.addActionListener(this);
        editaPainelJPanel.add(procuraTorcedor);
        
        nomeTorcedor = new JLabel("Nome:");
        nomeTorcedor.setBounds(new Rectangle(10,40,100,25));
        editaPainelJPanel.add(nomeTorcedor);
        nome = new JTextField();
        nome.setBounds(new Rectangle(60,40,130,25));
        editaPainelJPanel.add(nome);       

        now = new Date();  
        SpinnerDateModel model = new SpinnerDateModel(now, null, now, Calendar.DAY_OF_WEEK);  
        this.fieldData = new JSpinner(model);
        this.fieldData.setEditor(new JSpinner.DateEditor(this.fieldData, "dd/MM/yyyy"));
        this.fieldData.setBounds(new Rectangle(320,40,150,25));
        editaPainelJPanel.add(this.fieldData, null);
        
        labelData = new JLabel("Data de Nascimento:");
        labelData.setBounds(new Rectangle(195,40,180,25));

        editaPainelJPanel.add(labelData);       
        labelSexo = new JLabel("Sexo:");
        labelSexo.setBounds(new Rectangle(10,70,100,25));
        editaPainelJPanel.add(labelSexo);
        String[] listaSexo = {"Masculino", "Feminino"};
        comboSexo = new JComboBox(listaSexo);
        comboSexo.setBounds(new Rectangle(40,70,100,25));
        editaPainelJPanel.add(comboSexo);
        
        labelCivil = new JLabel("Estado Civil:");
        labelCivil.setBounds(new Rectangle(195,70,150,25));
        editaPainelJPanel.add(labelCivil);
        String[] listaCivil = {"Solteiro", "Casado", "Divorciado"};
        comboCivil = new JComboBox(listaCivil);
        comboCivil.setBounds(new Rectangle(320,70,100,25));
        editaPainelJPanel.add(comboCivil);
        
        labelTelefone = new JLabel("DDD+ Telefone");
        labelTelefone.setBounds(new Rectangle(10,100,100,25));
        editaPainelJPanel.add(labelTelefone);        
        textFieldTelefone = new JTextField();
        textFieldTelefone.setBounds(new Rectangle(120,100,150,25));
        editaPainelJPanel.add(textFieldTelefone);        
        
        cpfTorcedor = new JLabel("CPF:");
        cpfTorcedor.setBounds(new Rectangle(275,100,200,25));
        editaPainelJPanel.add(cpfTorcedor);
        cpf = new JTextField();
        cpf.setBounds(new Rectangle(320,100,200,25));
        editaPainelJPanel.add(cpf);        
        
        cepTorcedor = new JLabel("CEP:");
        cepTorcedor.setBounds(new Rectangle(10,130,100,25));
        editaPainelJPanel.add(cepTorcedor);
        cep = new JTextField();
        cep.setBounds(new Rectangle(120,130,120,25));
        editaPainelJPanel.add(cep);        

        estadoTorcedor = new JLabel("Estado:");
        estadoTorcedor.setBounds(new Rectangle(275,130,200,25));
        editaPainelJPanel.add(estadoTorcedor);
        estado = new JTextField();
        estado.setBounds(new Rectangle(320,130,200,25));
        editaPainelJPanel.add(estado);        

        cidadeTorcedor = new JLabel("Cidade:");
        cidadeTorcedor.setBounds(new Rectangle(10,160,100,25));
        editaPainelJPanel.add(cidadeTorcedor);
        cidade = new JTextField();
        cidade.setBounds(new Rectangle(120,160,120,25));
        editaPainelJPanel.add(cidade);        
        
        labelBairro = new JLabel("Bairro:");
        labelBairro.setBounds(new Rectangle(275,160,200,25));
        editaPainelJPanel.add(labelBairro);
        textFieldBairro = new JTextField();
        textFieldBairro.setBounds(new Rectangle(320,160,200,25));
        editaPainelJPanel.add(textFieldBairro);        
              
        
        labelComplemento = new JLabel("Complemento:");
        labelComplemento.setBounds(new Rectangle(275,190,200,25));
        editaPainelJPanel.add(labelComplemento);
        textFieldComplemento = new JTextField();
        textFieldComplemento.setBounds(new Rectangle(370,190,150,25));
        editaPainelJPanel.add(textFieldComplemento);        
        
        labelNumero = new JLabel("Número:");
        labelNumero.setBounds(new Rectangle(10,190,100,25));
        editaPainelJPanel.add(labelNumero);
        textFieldNumero = new JTextField();
        textFieldNumero.setBounds(new Rectangle(120,190,120,25));
        editaPainelJPanel.add(textFieldNumero);        
        
        
        tatuTorcedor = new JLabel("Tatuagem:");
        tatuTorcedor.setBounds(new Rectangle(10,250,200,25));
        editaPainelJPanel.add(tatuTorcedor);
        tatu = new JTextField();
        tatu.setBounds(new Rectangle(120,250,200,25));
        editaPainelJPanel.add(tatu);        
        
        marcaTorcedor = new JLabel("Mancha:");
        marcaTorcedor.setBounds(new Rectangle(325,250,200,25));
        editaPainelJPanel.add(marcaTorcedor);
        marca = new JTextField();
        marca.setBounds(new Rectangle(370,250,200,25));
        editaPainelJPanel.add(marca);        
        
        labelAltura = new JLabel("Altura");
        labelAltura.setBounds(new Rectangle(10,280,200,25));
        editaPainelJPanel.add(labelAltura);
        textFieldAltura = new JTextField();
        textFieldAltura.setBounds(new Rectangle(120,280,200,25));
        editaPainelJPanel.add(textFieldAltura);        
        
        labelCorCabelo = new JLabel("Cor do Cabelo:");
        labelCorCabelo.setBounds(new Rectangle(325,280,200,25));
        editaPainelJPanel.add(labelCorCabelo);
        textFieldCorCabelo = new JTextField();
        textFieldCorCabelo.setBounds(new Rectangle(410,280,160,25));
        editaPainelJPanel.add(textFieldCorCabelo);        
        
        labelAcessorio = new JLabel("Acessório");
        labelAcessorio.setBounds(new Rectangle(10,310,200,25));
        editaPainelJPanel.add(labelAcessorio);
        textFieldAcessorio = new JTextField();
        textFieldAcessorio.setBounds(new Rectangle(120,310,200,25));
        editaPainelJPanel.add(textFieldAcessorio);        
        
        labelEmail = new JLabel("E-mail:");
        labelEmail.setBounds(new Rectangle(325,310,200,25));
        editaPainelJPanel.add(labelEmail);
        textFieldEmail = new JTextField();
        textFieldEmail.setBounds(new Rectangle(410,310,160,25));
        editaPainelJPanel.add(textFieldEmail);        
        
        labelRg = new JLabel("RG");
        labelRg.setBounds(new Rectangle(10,340,200,25));
        editaPainelJPanel.add(labelRg);
        textFieldRg = new JTextField();
        textFieldRg.setBounds(new Rectangle(120,340,200,25));
        editaPainelJPanel.add(textFieldRg);        
        
        cadastrar = new JButton("Editar");
        cadastrar.setBounds(new Rectangle(10,370,200,25));
        cadastrar.setSize(110,30);
        cadastrar.setActionCommand("editar");
        cadastrar.addActionListener(this);
        editaPainelJPanel.add(cadastrar);        
        
        limparDados = new JButton("Restaurar");
        limparDados.setBounds(new Rectangle(120,370,200,25));
        limparDados.setSize(200,30);
        limparDados.setActionCommand("LIMPAR");
        limparDados.addActionListener(this);
        editaPainelJPanel.add(limparDados);
    }        

    
    public void actionPerformed(ActionEvent ae) {
        String comando = ae.getActionCommand();
        if ("Buscar".equals(comando)) {
            procuraUuario = buscaTorcedor.getText();
            for(int i=0; i<this.torcedorList.size(); i++){
                Torcedor objr = (Torcedor) torcedorList.elementAt(i);
                if(objr.getNome().equals(procuraUuario)){
                    this.posicaoUsuario = i;
                    this.nome.setText(objr.getNome());
                    this.estado.setText(this.torcedorList.elementAt(i).getEstado());
                    this.cidade.setText(this.torcedorList.elementAt(i).getCidade());
                    this.textFieldEmail.setText(this.torcedorList.elementAt(i).getEmail());
                    String cpfText = String.valueOf(this.torcedorList.elementAt(i).getCpf());
                    this.cpf.setText(cpfText);
                    String alturaString = String.valueOf(this.torcedorList.elementAt(i).getAltura());
                    this.textFieldAltura.setText(alturaString);            
                    this.textFieldAcessorio.setText(this.torcedorList.elementAt(i).getAcessorio());
                    this.textFieldCorCabelo.setText(this.torcedorList.elementAt(i).getCorCabelo());
                    this.tatu.setText(this.torcedorList.elementAt(i).getTatuagem());
                    this.marca.setText(this.torcedorList.elementAt(i).getMancha());
                    this.textFieldRg.setText(this.torcedorList.elementAt(i).getRg());
                    this.textFieldTelefone.setText(this.torcedorList.elementAt(i).getTelefone());
                    this.cep.setText(this.torcedorList.elementAt(i).getCep());
                    String resid = String.valueOf(this.torcedorList.elementAt(i).getNumeroResidencia());
                    this.textFieldNumero.setText(resid);
                    this.textFieldComplemento.setText(this.torcedorList.elementAt(i).getComplemento());
                    this.textFieldBairro.setText(this.torcedorList.elementAt(i).getBairro());
                    //this.fieldData.setValue(this.torcedorList.elementAt(i).getData());
                }                
            }
        }
        else if("editar".equals(comando)) {
            String nomeTorcedor = this.nome.getText();
            String estado = this.estado.getText();
            String cidade = this.cidade.getText();
            String email = this.textFieldEmail.getText();
            String cpf = this.cpf.getText();            
            String altoString = this.textFieldAltura.getText();         
            Float alto = Float.valueOf(altoString);
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
            
            this.torcedorList.elementAt(this.posicaoUsuario).setNome(nomeTorcedor);
            this.torcedorList.elementAt(this.posicaoUsuario).setEstado(estado);
            this.torcedorList.elementAt(this.posicaoUsuario).setCidade(cidade);
            this.torcedorList.elementAt(this.posicaoUsuario).setEmail(email);
            this.torcedorList.elementAt(this.posicaoUsuario).setCpf(cpf);                        
            this.torcedorList.elementAt(this.posicaoUsuario).setAltura(alto);
            this.torcedorList.elementAt(this.posicaoUsuario).setAcessorio(acessorio);
            this.torcedorList.elementAt(this.posicaoUsuario).setCorCabelo(corCabelo);
            this.torcedorList.elementAt(this.posicaoUsuario).setTatuagem(tatuagem);
            this.torcedorList.elementAt(this.posicaoUsuario).setMancha(mancha);
            this.torcedorList.elementAt(this.posicaoUsuario).setData(data);
            this.torcedorList.elementAt(this.posicaoUsuario).setRg(rg);
            this.torcedorList.elementAt(this.posicaoUsuario).setSexo(sexo);
            this.torcedorList.elementAt(this.posicaoUsuario).setEstadoCivil(civil);
            this.torcedorList.elementAt(this.posicaoUsuario).setTelefone(tel);
            this.torcedorList.elementAt(this.posicaoUsuario).setCep(cep);
            this.torcedorList.elementAt(this.posicaoUsuario).setNumeroResidencia(resid);
            this.torcedorList.elementAt(this.posicaoUsuario).setComplemento(complemento);
            this.torcedorList.elementAt(this.posicaoUsuario).setBairro(bairro);
        }
        else if("LIMPAR".equals(comando)) {
            this.nome.setText(this.torcedorList.elementAt(this.posicaoUsuario).getNome());
            this.estado.setText(this.torcedorList.elementAt(this.posicaoUsuario).getEstado());
            this.cidade.setText(this.torcedorList.elementAt(this.posicaoUsuario).getCidade());
            this.textFieldEmail.setText(this.torcedorList.elementAt(this.posicaoUsuario).getEmail());
            String cpfText = String.valueOf(this.torcedorList.elementAt(this.posicaoUsuario).getCpf());
            this.cpf.setText(cpfText);
            String alturaString = String.valueOf(this.torcedorList.elementAt(this.posicaoUsuario).getAltura());
            this.textFieldAltura.setText(alturaString);            
            this.textFieldAcessorio.setText(this.torcedorList.elementAt(this.posicaoUsuario).getAcessorio());
            this.textFieldCorCabelo.setText(this.torcedorList.elementAt(this.posicaoUsuario).getCorCabelo());
            this.tatu.setText(this.torcedorList.elementAt(this.posicaoUsuario).getTatuagem());
            this.marca.setText(this.torcedorList.elementAt(this.posicaoUsuario).getMancha());
            this.textFieldRg.setText(this.torcedorList.elementAt(this.posicaoUsuario).getRg());
            this.textFieldTelefone.setText(this.torcedorList.elementAt(this.posicaoUsuario).getTelefone());
            this.cep.setText(this.torcedorList.elementAt(this.posicaoUsuario).getCep());
            String resid = String.valueOf(this.torcedorList.elementAt(this.posicaoUsuario).getNumeroResidencia());
            this.textFieldNumero.setText(resid);
            this.textFieldComplemento.setText(this.torcedorList.elementAt(this.posicaoUsuario).getComplemento());
            this.textFieldBairro.setText(this.torcedorList.elementAt(this.posicaoUsuario).getBairro());   
        }
    }
}
