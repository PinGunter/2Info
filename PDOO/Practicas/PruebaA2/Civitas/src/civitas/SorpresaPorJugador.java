package civitas;
import java.util.ArrayList;
/**
 *
 * @author abel
 */
public class SorpresaPorJugador extends Sorpresa {
    
    private int valor;
    
    SorpresaPorJugador(int valor, String texto){
        this.texto = texto;
        this.valor = valor;      
    }
    
    @Override
    void aplicarAJugador(int actual, ArrayList<Jugador> todos){
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            SorpresaPorJugador s = new SorpresaPorJugador(valor, "");

            for (int i = 0; i < todos.size(); i++) // o todos.size();
            {
                if (i != actual) {
                    todos.get(i).paga(s.valor);
                }
            }

            SorpresaPorJugador s1 = new SorpresaPorJugador(valor * (todos.size() - 1), "");
            todos.get(actual).recibe(s1.valor);
        }  
    }
}
