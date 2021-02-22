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

    Tablero(int indice) {
        casillas = new ArrayList<>();
        if (indice >= 1) {
            numCasillaCarcel = indice;
        } else {
            numCasillaCarcel = 1;
        }
        casillas.add(new Casilla("Salida"));
        porSalida = 0;
        tieneJuez = false;
    }

    private boolean correcto() {
        return casillas.size() > numCasillaCarcel && tieneJuez;
    }

    private boolean correcto(int numCasilla) {
        return numCasilla >= 0 && numCasilla < casillas.size() && this.correcto();
    }

    int getCarcel() {
        return numCasillaCarcel;
    }

    int getPorSalida() {
        if (porSalida > 0) {
            porSalida -= 1;
            return porSalida + 1;
        }
        return porSalida;
    }

    void añadeCasilla(Casilla casilla) {
        if (numCasillaCarcel == casillas.size()) {
            casillas.add(new Casilla("Cárcel"));
        }
        casillas.add(casilla);
        if (numCasillaCarcel == casillas.size()) {
            casillas.add(new Casilla("Cárcel"));
        }
    }

    void añadeJuez() {
        if (!tieneJuez) {
            casillas.add(new CasillaJuez(numCasillaCarcel, "Juez"));
            tieneJuez = true;
        }
    }

    Casilla getCasilla(int numCasilla) {
        if (this.correcto(numCasilla)) {
            return casillas.get(numCasilla);
        } else {
            return null;
        }
    }

    int nuevaPosicion(int actual, int tirada) {
        int nueva = actual + tirada;
        if (!this.correcto()) {
            return -1;
        } else {
            if (nueva >= casillas.size()) {
                nueva = nueva % casillas.size();
                porSalida += 1;
            }
            return nueva;

        }
    }

    int calcularTirada(int origen, int destino) {
        int tirada = destino - origen;
        if (tirada < 0) {
            tirada += casillas.size();
        }
        return tirada;
    }
}
