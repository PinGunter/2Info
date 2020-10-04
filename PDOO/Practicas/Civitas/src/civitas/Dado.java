/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;
import java.util.Random;
/**
 *
 * @author salva
 */
public class Dado {
    private Random random;
    private int ultimoResultado;
    private boolean debug;
    
    static final private Dado instance = new Dado();
    static final private int SalidaCarcel = 5;
    
    private Dado(){
        debug = false;
        random = new Random();
    }
    
    static Dado getInstance(){
        return instance;
    }
    
    int tirar(){
        int tirada = 0;
        if (debug){
            tirada = 1;
        } else {
            tirada = random.nextInt(6)+1;
        }
        ultimoResultado = tirada;
        return tirada;
    }
    
    boolean salgoDeLaCarcel(){
        int tirada = tirar();
        if (tirada >= SalidaCarcel){
            ultimoResultado = tirada;
        }
        return tirada >= SalidaCarcel;
    }
    
    int quienEmpieza(int n){
        return random.nextInt(n);
    }
    
    void setDebug(Boolean d){
        debug = d;
        Diario.getInstance().ocurreEvento("Dado debug:"+d);
    }
    
    int getUltimoResultado(){
        return ultimoResultado;
    }
}
