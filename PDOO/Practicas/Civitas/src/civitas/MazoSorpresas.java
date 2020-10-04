/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;
import java.util.ArrayList;
import java.util.Collections;
/**
 *
 * @author salva
 */
public class MazoSorpresas {
    private ArrayList<Sorpresa> sorpresas;
    private boolean barajada;
    private int usadas;
    private boolean debug;
    private ArrayList<Sorpresa> cartasEspeciales;
    private Sorpresa ultimaSorpresa;
    
    MazoSorpresas(){
        init();
        debug = false;
    }
    
    MazoSorpresas(boolean d){
        init();
        debug = d;
        if (d)
            Diario.getInstance().ocurreEvento("debug mazo: true");
    }
    
    private void init(){
        sorpresas = new ArrayList<>();
        cartasEspeciales = new ArrayList<>();
        barajada = false;
        usadas = 0;
    }
    
    void alMazo(Sorpresa s){
        if (!barajada){
            sorpresas.add(s);
        }
    }
    
    Sorpresa siguiente(){
        if (!barajada || usadas == 0){
            usadas = 0;
            barajada = true;
            if (!debug)
                Collections.shuffle(sorpresas);
        }
        usadas += 1;
        ultimaSorpresa = sorpresas.get(0);
        sorpresas.remove(0);
        sorpresas.add(ultimaSorpresa);
        return ultimaSorpresa;
    }
    
    void inhabilitarCartaEspecial(Sorpresa sorpresa){
        boolean estaEnMazo = sorpresas.contains(sorpresa);
        if (estaEnMazo){
            sorpresas.remove(sorpresa);
            cartasEspeciales.add(sorpresa);
            Diario.getInstance().ocurreEvento("Se inhabilita carta sorpresa");
        }
    }
    
    void habilitarCartaEspecial(Sorpresa sorpresa){
        boolean estaEnMazo = cartasEspeciales.contains(sorpresa);
        if (estaEnMazo){
            cartasEspeciales.remove(sorpresa);
            sorpresas.add(sorpresa);
            Diario.getInstance().ocurreEvento("Se habilitad carta sorpresa");  
        }
    }
}
