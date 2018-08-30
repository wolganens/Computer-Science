package trabalho.pkg1.poo.wolgan.ens;
import java.util.*;

public class Admin{
    
    private final String usuario;
    private final String senha;
    
    public Admin(String usuario, String senha){
        this.usuario = usuario;
        this.senha = senha;
    }
    
    public String getSenha(){
        return this.senha;
    }

    public String getUsuario(){
        return this.usuario;
    }
}