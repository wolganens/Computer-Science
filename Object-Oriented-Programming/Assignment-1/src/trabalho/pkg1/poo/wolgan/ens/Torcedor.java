package trabalho.pkg1.poo.wolgan.ens;

import java.io.Serializable;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

public class Torcedor implements Serializable{
    private String cadastradoPor,rg,telefone,cep,cpf,bairro,estadoCivil,email,nome,estado,cidade,acessorio,corCabelo,tatuagem,mancha,sexo,complemento;
    private int numeroResidencia;
    private float altura;
    private int id;
    private static Date nascimento;
    
    public Torcedor(int id) {
        this.id = id;
    }
    public void seCadastradoPor(String gerenciador){
        this.cadastradoPor = gerenciador;
    }
    public String getCadastradoPor(){
        return this.cadastradoPor;
    }
    public Date getData(){
        return this.nascimento;
    }
    
    public void setData(Date data){
        this.nascimento = data;
    }
    
    public String getRg() {
        return rg;
    }

    public String getTelefone() {
        return telefone;
    }

    public String getCep() {
        return cep;
    }

    public String getCpf() {
        return cpf;
    }

    public String getBairro() {
        return bairro;
    }

    public String getEstadoCivil() {
        return estadoCivil;
    }

    public String getEmail() {
        return email;
    }

    public String getNome() {
        return nome;
    }

    public String getEstado() {
        return estado;
    }

    public String getCidade() {
        return cidade;
    }

    public String getAcessorio() {
        return acessorio;
    }

    public String getCorCabelo() {
        return corCabelo;
    }

    public String getTatuagem() {
        return tatuagem;
    }

    public String getMancha() {
        return mancha;
    }

    public String getSexo() {
        return sexo;
    }

    public String getComplemento() {
        return complemento;
    }

    public int getNumeroResidencia() {
        return numeroResidencia;
    }

    public float getAltura() {
        return altura;
    }

    public int getId() {
        return id;
    }
    public void setRg(String rg) {
        this.rg = rg;
    }

    public void setTelefone(String telefone) {
        this.telefone = telefone;
    }

    public void setCep(String cep) {
        this.cep = cep;
    }

    public void setCpf(String cpf) {
        this.cpf = cpf;
    }

    public void setBairro(String bairro) {
        this.bairro = bairro;
    }

    public void setEstadoCivil(String estadoCivil) {
        this.estadoCivil = estadoCivil;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setEstado(String estado) {
        this.estado = estado;
    }

    public void setCidade(String cidade) {
        this.cidade = cidade;
    }

    public void setAcessorio(String acessorio) {
        this.acessorio = acessorio;
    }

    public void setCorCabelo(String corCabelo) {
        this.corCabelo = corCabelo;
    }

    public void setTatuagem(String tatuagem) {
        this.tatuagem = tatuagem;
    }

    public void setMancha(String mancha) {
        this.mancha = mancha;
    }

    public void setSexo(String sexo) {
        this.sexo = sexo;
    }

    public void setComplemento(String complemento) {
        this.complemento = complemento;
    }

    public void setNumeroResidencia(int numeroResidencia) {
        this.numeroResidencia = numeroResidencia;
    }

    public void setAltura(float altura) {
        this.altura = altura;
    }    
    
}