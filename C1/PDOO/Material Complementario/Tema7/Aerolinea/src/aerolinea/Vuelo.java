/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package aerolinea;

import java.util.ArrayList;

/**
 *
 * @author pingu
 */
public class Vuelo {

    ArrayList<Viaje> viajes;
    Avion a;

    public Vuelo() {
        viajes = new ArrayList<>();
        a = null;
    }

    public void reservar(Pasajero pasajero) {
        boolean plazas = plazasLibres();
        if (plazas) {
            Asiento s = a.eligeAsientoLibre();
            Viaje elViaje = new Viaje(pasajero, s);
            if (plazas) { //Esto estaba mal en el diagrama
                viajes.add(elViaje);
            }
        }

    }
}
