/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

/**
 *
 * @author Salva
 */
public class TituloPropiedad {

    //atributos de instancia
    private float alquilerBase;
    private static final float factorInteresesHipoteca = 1.1f;
    private float factorRevalorizacion;
    private float hipotecaBase;
    private boolean hipotecado;
    private String nombre;
    private int numCasas;
    private int numHoteles;
    private float precioCompra;
    private float precioEdificar;

    //atributo de referencia
    private Jugador propietario;

    //metodos
    TituloPropiedad(String nombre, float alquBase, float factrevalor, float hipbase,
            float precioComp, float precioEdifi) {
        this.nombre = nombre;
        alquilerBase = alquBase;
        factorRevalorizacion = factrevalor;
        hipotecaBase = hipbase;
        precioCompra = precioComp;
        precioEdificar = precioEdifi;
        propietario = null;
        numCasas = numHoteles = 0;
        hipotecado = false;

    }

    @Override
    public String toString() {
        String salida = "Nombre: " + nombre
                + "\nAlquiler Base: " + alquilerBase
                + "\nFactor de Revalorización: " + factorRevalorizacion
                + "\nFactor Intereses Hipoteca: " + factorInteresesHipoteca
                + "\nHipoteca Base: " + hipotecaBase
                + "\nHipotecado: " + hipotecado
                + "\nNúmero de casas: " + numCasas
                + "\nNúmero de Hoteles: " + numHoteles
                + "\nPrecio de compra: " + precioCompra
                + "\nPrecio de Edificar: " + precioEdificar;
        return salida;

    }

    //cambiada visibilidad de private a paquete para que el jugador sepa de antemano la cantidad que debe pagar
    float getPrecioAlquiler() {
        //  PrecioAlquiler=AlquilerBase*(1+(NumCasas*0.5)+(NumHoteles*2.5))
        float precio = alquilerBase * (1f + (numCasas * 0.5f) + (numHoteles * 2.5f));
        if (hipotecado || propietarioEncarcelado()) {
            precio = 0;
        }
        return precio;
    }

    private float getImporteHipoteca() {
        //CantidadRecibida=HipotecaBase*(1+(numCasas*0.5)+(numHoteles*2.5))
        float importe = hipotecaBase * (1 + (numCasas * 0.5f) + (numHoteles * 2.5f));
        return importe;
    }

    float getImporteCancelarHipoteca() {
        float importe = getImporteHipoteca() * factorInteresesHipoteca;
        return importe;
    }

    void actualizaPropietarioPorConversion(Jugador jugador) {
        propietario = jugador;
    }

    boolean cancelarHipoteca(Jugador jugador) {
        boolean result = false;
        if (hipotecado) {
            if (esEsteElPropietario(jugador)) {
                jugador.paga(getImporteCancelarHipoteca());
                hipotecado = false;
                result = true;
            }
        }
        return result;
    }

    int cantidadCasasHoteles() {
        return getNumCasas() + getNumHoteles();
    }

    boolean comprar(Jugador jugador) {
        boolean result = false;
        if (!tienePropietario()) {
            propietario = jugador;
            result = true;
            propietario.paga(precioCompra);
        }
        return result;
    }

    boolean construirCasa(Jugador jugador) {
        boolean result = false;
        if (esEsteElPropietario(jugador)) {
            propietario.paga(precioEdificar);
            numCasas = numCasas + 1;
            result = true;
        }
        return result;
    }

    boolean construirHotel(Jugador jugador) {
        boolean result = false;
        if (esEsteElPropietario(jugador)) {
            propietario.paga(precioEdificar);
            numHoteles = numHoteles + 1;
            result = true;
        }
        return result;
    }

    boolean derruirCasas(int n, Jugador jugador) {
        if (esEsteElPropietario(jugador) && getNumCasas() >= n) {
            numCasas -= n;
            return true;
        }
        return false;
    }

    private boolean esEsteElPropietario(Jugador jugador) {
        return jugador == getPropietario();
    }

    public boolean getHipotecado() {
        return hipotecado;
    }

//    cambiada visibilidad de paquete a publica para vista textual
    public String getNombre() {
        return nombre;
    }

    int getNumCasas() {
        return numCasas;
    }

    int getNumHoteles() {
        return numHoteles;
    }

    float getPrecioCompra() {
        return precioCompra;
    }

    //modificamos visibilidad de paquete a public para que la partida sea más accesible. Se consulta al construir casas y hoteles
    public float getPrecioEdificar() {
        return precioEdificar;
    }

    private float getPrecioVenta() {
        float precio = getPrecioCompra() + getPrecioEdificar() * cantidadCasasHoteles() * factorRevalorizacion;
        return precio;
    }

    Jugador getPropietario() {
        return propietario;
    }

    boolean hipotecar(Jugador jugador) {
        boolean salida = false;
        if (!hipotecado && esEsteElPropietario(jugador)) {
            propietario.recibe(getImporteHipoteca());
            hipotecado = true;
            salida = true;
        }
        return salida;
    }

    private boolean propietarioEncarcelado() {
        return getPropietario().isEncarcelado();
    }

    boolean tienePropietario() {
        return propietario != null;
    }

    void tramitarAlquiler(Jugador jugador) {
        if (tienePropietario()) {
            if (!esEsteElPropietario(jugador)) {
                float precio = getPrecioAlquiler();
                jugador.paga(precio);
                propietario.recibe(precio);
            }
        }
    }

    boolean vender(Jugador jugador) {
        if (esEsteElPropietario(jugador) && !hipotecado) {
            jugador.recibe(getPrecioVenta());
            propietario = null;
            numCasas = numHoteles = 0;
            return true;
        } else {
            return false;
        }
    }

}
