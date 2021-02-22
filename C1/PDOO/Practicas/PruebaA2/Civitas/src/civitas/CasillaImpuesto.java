package civitas;

import java.util.ArrayList;

/**
 *
 * @author salva
 */
public class CasillaImpuesto extends Casilla{
    private float importe; //debe ser positivo porque en "paga" de jugador se multiplica por -1
    
    CasillaImpuesto(float importe, String nombre){
        super(nombre);
        this.importe = importe;
    }
    
    @Override
    public String toString(){
        String info = super.toString();
        info += "\nImporte del impuesto: " + importe;
        return info;
    }
    
    @Override
    void recibeJugador(int actual, ArrayList<Jugador> todos){
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            todos.get(actual).pagaImpuesto(importe);
        }
    }
    
}
