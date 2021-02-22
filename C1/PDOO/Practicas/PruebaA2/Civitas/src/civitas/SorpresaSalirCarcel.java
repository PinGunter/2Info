package civitas;
import java.util.ArrayList;
/**
 *
 * @author abel
 */
public class SorpresaSalirCarcel extends Sorpresa {
    
    private MazoSorpresas mazo;
    
    SorpresaSalirCarcel(MazoSorpresas mazo){
        this.texto = "Quedas libre de la carcel";
        this.mazo = mazo;
    }
    
    @Override
    void aplicarAJugador(int actual, ArrayList<Jugador> todos) {
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            Boolean loTienen = false;
            for (int i = 0; i < todos.size() && !loTienen; i++) {
                if (todos.get(i).tieneSalvoconducto()) {
                    loTienen = true;
                }
            }

            if (!loTienen) {
                todos.get(actual).obtenerSalvoconducto(new SorpresaSalirCarcel(mazo));
                salirDelMazo();
            }
        }
    }
    
    void salirDelMazo() {
        mazo.inhabilitarCartaEspecial(this);
    }

    void usada() {       
        mazo.habilitarCartaEspecial(this);
    }    
}
