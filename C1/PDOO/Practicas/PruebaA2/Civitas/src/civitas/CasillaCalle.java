package civitas;

import java.util.ArrayList;

/**
 *
 * @author salva
 */
public class CasillaCalle extends Casilla{
    private TituloPropiedad titulo;
    private float importe; // para hacer más sencillo el acceso al precio compra
    
    public CasillaCalle(TituloPropiedad titulo){
        super(titulo.getNombre());
        this.titulo = titulo;
        this.importe = titulo.getPrecioCompra();
    }
    
    public TituloPropiedad getTituloPropiedad(){
        return titulo;
    }
    
    @Override
    public String toString(){
        String info = super.toString();
        info += "\nPrecio: " + importe;
        if (titulo.tienePropietario()){
            info += "\nPropietario: " + titulo.getPropietario().getNombre();
            info += "\nNúmero de casas: " + titulo.getNumCasas();
            info += "\nNúmero de hoteles: " + titulo.getNumHoteles();
            info += "\nPrecio de alquiler: " + titulo.getPrecioAlquiler();
        } else{
            info += "\nLa casilla no tiene dueño";
        }
        return info;
    }
    
    @Override
    void recibeJugador(int actual, ArrayList<Jugador> todos){
        if (jugadorCorrecto(actual, todos)) {
        informe(actual, todos);
        Jugador jugador = todos.get(actual);
        if (!titulo.tienePropietario()) {
            jugador.puedeComprarCasilla();
        } else {
            titulo.tramitarAlquiler(jugador);
        }
    }
}
}
