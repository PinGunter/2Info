/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

/**
 *
 * @author salva
 */
import java.util.ArrayList;
import juegoTexto.VistaTextual;
import juegoTexto.Controlador;

public class Prueba {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        ArrayList<String> jugadores = new ArrayList<>();
        jugadores.add("Salva");
        jugadores.add("Abel");
        jugadores.add("Esther");
        jugadores.add("Juanma");

        VistaTextual vista = new VistaTextual();
        CivitasJuego juego = new CivitasJuego(jugadores);
        Dado.getInstance().setDebug(Boolean.TRUE);
        Controlador controlador = new Controlador(juego, vista);
        controlador.juega();
    }

}
