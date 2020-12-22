package civitas;
import java.util.ArrayList;
/**
 *
 * @author abel
 */
public class SorpresaConvertirEspeculador extends Sorpresa {
    
    private int valor;
    
    SorpresaConvertirEspeculador(int valor, String texto){
        this.valor = valor;
        this.texto = texto;
    }
    
    @Override
    void aplicarAJugador(int actual, ArrayList<Jugador> todos){
        if(jugadorCorrecto(actual, todos)){
            informe(actual, todos);
            todos.set(actual, new JugadorEspeculador(todos.get(actual), valor));
        }
    }
    
}
