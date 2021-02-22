package civitas;

/**
 *
 * @author Salva
 */
public class JugadorEspeculador extends Jugador {

    private int maxCasas = FactorEspeculador * CasasMax;
    private int maxHoteles = FactorEspeculador * HotelesMax;

    private float fianza;
    private final float factorPagoImpuesto = 0.5f;

    JugadorEspeculador(Jugador otro, float fianza) {
        super(otro);
        this.fianza = fianza;
        actualizarPropiedades(otro);
    }

    //la dejamos o la quitamos?
    private void actualizarPropiedades(Jugador original) {
        original.getPropiedades().forEach((propiedad) -> {      // <- sugerido por NetBeans. Originalmente for (TituloPropiedad propiedad : original.getPropiedades()
            propiedad.actualizaPropietarioPorConversion(this);
        });
    }

    @Override
    public String toString() {
        String info = super.toString();
        info += "\n ---  Es jugador especulador. Paga menos impuestos y puede evitar la cárcel --- \n";
        info += "La fianza que paga es de " + fianza;
        return info;
    }

    @Override
    protected int getCasasMax() {
        return maxCasas;
    }

    @Override
    protected int getHotelesMax() {
        return maxHoteles;
    }

    @Override
    public boolean pagaImpuesto(float cantidad) {
        return super.pagaImpuesto(cantidad * factorPagoImpuesto);
    }

    @Override
    protected boolean debeSerEncarcelado() {
        boolean carcel = super.debeSerEncarcelado();
        if (carcel){
            if (puedoGastar(fianza)){
                paga(fianza);
                carcel = false;
            }
        }
        return carcel;
    }

}
