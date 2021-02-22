package civitas;
import java.util.ArrayList;
/**
 *
 * @author pingu
 */
public class CasillaJuez extends Casilla {
    private static int carcel;
    
    CasillaJuez(int carcel, String nombre){
        super(nombre);
        this.carcel = carcel;
    }
    
    @Override
    public String toString(){
        String info = super.toString();
        info += "\n¡Has caído en el Juez, VE A LA CÁRCEL!";
        return info;
    }
    
    @Override
    void recibeJugador(int actual, ArrayList<Jugador> todos){
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            todos.get(actual).encarcelar(carcel);
        }
    }
    
}
