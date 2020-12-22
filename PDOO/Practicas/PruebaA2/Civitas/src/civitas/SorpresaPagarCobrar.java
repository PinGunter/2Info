package civitas;
import java.util.ArrayList;
/**
 *
 * @author abel
 */
public class SorpresaPagarCobrar extends Sorpresa {
    
    private float valor;
    
    SorpresaPagarCobrar(int valor, String texto){
        
        this.texto = texto;
        this.valor = valor;       
    }
    
    @Override
    void aplicarAJugador(int actual, ArrayList<Jugador> todos){
        if(jugadorCorrecto(actual, todos)){
            informe(actual, todos);
            todos.get(actual).modificarSaldo(valor);
        }
    }
}
