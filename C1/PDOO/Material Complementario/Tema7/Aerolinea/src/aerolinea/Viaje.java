/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package aerolinea;

/**
 *
 * @author pingu
 */
public class Viaje {

    public Viaje(Pasajero pasajero, Asiento s) {
        setPasajero(pasajero);
        pasajero.seguroProtocoloSeguridad();
    }

    public void setPasajero(Pasajero pasajero) {

    }
}
