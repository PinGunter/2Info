package civitas;

import java.util.ArrayList;
import juegoTexto.Controlador;
import juegoTexto.VistaTextual;

/**
 *
 * @author abel
 */
public class TestP4 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        ArrayList<String> jugadores = new ArrayList<>();
        jugadores.add("Salva");
        jugadores.add("Abel");

        VistaTextual vista = new VistaTextual();
        CivitasJuego juego = new CivitasJuego(jugadores);
        Dado.getInstance().setDebug(Boolean.TRUE);
        Controlador controlador = new Controlador(juego, vista);
        controlador.juega();
    }
    
}
