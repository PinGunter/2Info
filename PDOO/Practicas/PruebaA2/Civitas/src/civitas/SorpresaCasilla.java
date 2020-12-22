package civitas;
import java.util.ArrayList;
/**
 *
 * @author abel
 */
public class SorpresaCasilla extends Sorpresa {
    
    private Tablero tablero;
    private int valor;
    
    SorpresaCasilla(Tablero tablero, int valor, String texto){
        this.tablero = tablero;
        this.valor = valor;
        this.texto = texto;
    }
    
    @Override
    void aplicarAJugador(int actual, ArrayList<Jugador> todos){ // Revisar
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            int casilla = todos.get(actual).getNumCasillaActual();
            int tirada = tablero.calcularTirada(casilla, valor);
            int n = tablero.nuevaPosicion(casilla, tirada);
            todos.get(actual).moverACasilla(n);
            tablero.getCasilla(n).recibeJugador(actual, todos);
        }
    }
    
}
