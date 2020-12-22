package civitas;
import java.util.ArrayList;

/**
 *
 * @author abel
 */
public class SorpresaCasaHotel extends Sorpresa {
    
    private int valor;
    
    SorpresaCasaHotel(int valor, String texto){
        this.texto = texto;
        this.valor = valor;  
    }
    
    @Override
    void aplicarAJugador(int actual, ArrayList<Jugador> todos){
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            todos.get(actual).modificarSaldo(valor * todos.get(actual).cantidadCasasHoteles());
        }
    }
}
