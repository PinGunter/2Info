/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

import java.util.ArrayList;

/**
 *
 * @author salva
 */
public class Tablero {
    private int numCasillaCarcel;
    private ArrayList<Casilla> casillas;
    private int porSalida;
    private boolean tieneJuez;
    
    Tablero(int indice){
        if (indice >= 1)
            numCasillaCarcel = indice;
        else
            numCasillaCarcel = 1;
        casillas.add(new Casilla("Salida"));
        porSalida = 0;
        tieneJuez = false;
    }
    
    private boolean correcto(){
        return casillas.size() > numCasillaCarcel && tieneJuez;
    }
    
    private boolean correcto(int numCasilla){
        return numCasilla > 0 && numCasilla < casillas.size();
    }
    
    int getCarcel(){
        return numCasillaCarcel;
    }
    
    int getPorSalida(){
        if (porSalida > 0){
            porSalida -= 1;
            return porSalida+1;
        }
        return porSalida;
    }
    
    void añadeCasilla(Casilla casilla){
        if (numCasillaCarcel == casillas.size())
            casillas.add(new Casilla("Cárcel"));
        casillas.add(casilla);
        if (numCasillaCarcel == casillas.size())
            casillas.add(new Casilla("Cárcel"));
    }
    
    void añadeJuez(){
        if (!tieneJuez){
            casillas.add(new Casilla("Juez"));
            tieneJuez = true;
        }
    }
    
    Casilla getCasilla(int numCasilla){
        if (this.correcto(numCasilla))
            return casillas.get(numCasilla);
        else
            return null;
    }
    
    int nuevaPosicion(int actual, int tirada){
        
    }
}
