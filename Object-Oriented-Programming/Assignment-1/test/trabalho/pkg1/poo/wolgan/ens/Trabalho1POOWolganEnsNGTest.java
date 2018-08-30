/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package trabalho.pkg1.poo.wolgan.ens;

import static org.testng.Assert.*;
import org.testng.annotations.AfterClass;
import org.testng.annotations.AfterMethod;
import org.testng.annotations.BeforeClass;
import org.testng.annotations.BeforeMethod;
import org.testng.annotations.Test;

/**
 *
 * @author win7
 */
public class Trabalho1POOWolganEnsNGTest {
    
    public Trabalho1POOWolganEnsNGTest() {
    }

    @BeforeClass
    public static void setUpClass() throws Exception {
    }

    @AfterClass
    public static void tearDownClass() throws Exception {
    }

    @BeforeMethod
    public void setUpMethod() throws Exception {
    }

    @AfterMethod
    public void tearDownMethod() throws Exception {
    }

    /**
     * Teste de método isSet, da classe Trabalho1POOWolganEns.
     */
    @Test
    public void testIsSet() {
        System.out.println("isSet");
        String usuario = "";
        Trabalho1POOWolganEns instance = new Trabalho1POOWolganEns();
        boolean expResult = false;
        boolean result = instance.isSet(usuario);
        assertEquals(result, expResult);
        // TODO verifica o código de teste gerado e remove a chamada default para falha.
        fail("O caso de teste \u00e9 um prot\u00f3tipo.");
    }

    /**
     * Teste de método verificaSenha, da classe Trabalho1POOWolganEns.
     */
    @Test
    public void testVerificaSenha() {
        System.out.println("verificaSenha");
        String senha = "";
        Trabalho1POOWolganEns instance = new Trabalho1POOWolganEns();
        boolean expResult = false;
        boolean result = instance.verificaSenha(senha);
        assertEquals(result, expResult);
        // TODO verifica o código de teste gerado e remove a chamada default para falha.
        fail("O caso de teste \u00e9 um prot\u00f3tipo.");
    }

    /**
     * Teste de método main, da classe Trabalho1POOWolganEns.
     */
    @Test
    public void testMain() {
        System.out.println("main");
        String[] args = null;
        Trabalho1POOWolganEns.main(args);
        // TODO verifica o código de teste gerado e remove a chamada default para falha.
        fail("O caso de teste \u00e9 um prot\u00f3tipo.");
    }
    
}
