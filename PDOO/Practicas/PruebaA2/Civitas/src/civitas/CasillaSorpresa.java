package civitas;

import java.util.ArrayList;

/**
 *
 * @author salva
 */
public class CasillaSorpresa extends Casilla{
    private MazoSorpresas mazo;
    //private Sorpresa sorpresa;
    
    CasillaSorpresa(MazoSorpresas mazo, String nombre){
        super(nombre);
        this.mazo = mazo;
    //    this.sorpresa = null;
    }
    
    @Override
    public String toString(){
//        if(sorpresa == null){
//            sorpresa = mazo.siguiente();
//        }
//        String info = super.toString();
//        info += "\n¡Has caído en una sorpresa!";
//        info += sorpresa.toString();
//        return info;
        String s = super.toString();
        return s;
    }
    
    @Override
    void recibeJugador(int actual, ArrayList<Jugador> todos){
        if (jugadorCorrecto(actual, todos)) {
            Sorpresa sorpresa = mazo.siguiente();
            informe(actual, todos);
            sorpresa.aplicarAJugador(actual, todos);
        }
    }
}
