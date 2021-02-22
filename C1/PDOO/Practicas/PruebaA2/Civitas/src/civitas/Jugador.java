/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

import java.util.ArrayList;

/**
 *
 * @author Salva
 */
public class Jugador implements Comparable<Jugador> {
    //atributos de instancia

    private String nombre;
    private boolean puedeComprar;
    private float saldo;
    protected boolean encarcelado;
    private int numCasillaActual;

    //atributos de clase
    protected static int CasasMax = 4;
    protected static int CasasPorHotel = 4;
    protected static int HotelesMax = 4;
    protected static float PasoPorSalida = 1000;
    protected static float PrecioLibertad = 200;
    private static float SaldoInicial = 7500;
    protected static int FactorEspeculador = 2;
    //atributos de referencia
    ArrayList<TituloPropiedad> propiedades;
    SorpresaSalirCarcel salvoconducto;

    Jugador(String nombre) {
        this.nombre = nombre;
        puedeComprar = false;
        saldo = SaldoInicial;
        encarcelado = false;
        numCasillaActual = 0;
        propiedades = new ArrayList<TituloPropiedad>();
        salvoconducto = null;
    }

    protected Jugador(Jugador otro) {
        this.nombre = otro.nombre;
        this.puedeComprar = otro.puedeComprar;
        this.saldo = otro.saldo;
        this.encarcelado = otro.encarcelado;
        this.numCasillaActual = otro.numCasillaActual;
        this.propiedades = otro.propiedades;
        this.salvoconducto = otro.salvoconducto;
    }

    protected boolean debeSerEncarcelado() {
        boolean carcel = !encarcelado;
        if (carcel) {
            if (tieneSalvoconducto()) {
                perderSalvoconducto();
                Diario.getInstance().ocurreEvento("Jugador " + nombre + " se libra de la carcel");
                carcel = false;
            }
        }
        return carcel;
    }

    boolean encarcelar(int numCasillaCarcel) {
        if (debeSerEncarcelado()) {
            moverACasilla(numCasillaCarcel);
            encarcelado = true;
            Diario.getInstance().ocurreEvento("Jugador " + nombre + " va la carcel");
        }
        return encarcelado;
    }

    boolean obtenerSalvoconducto(Sorpresa s) {
        boolean obtiene = !encarcelado;
        if (obtiene) {
            salvoconducto = ((SorpresaSalirCarcel)s);
            //  salvoconducto.tipo = TipoSorpresa.SALIRCARCEL;
        }
        return obtiene;
    }

    private void perderSalvoconducto() {
        salvoconducto.usada();
        salvoconducto = null;
    }

    boolean tieneSalvoconducto() {
        return salvoconducto != null;
    }

    boolean puedeComprarCasilla() {
        puedeComprar = !encarcelado;
        return puedeComprar;
    }

    boolean paga(float cantidad) {
        return modificarSaldo(-1f * cantidad);
    }

    boolean pagaImpuesto(float cantidad) {
        if (encarcelado) {
            return false;
        } else {
            return paga(cantidad);
        }
    }

    boolean pagaAlquiler(float cantidad) {
        return pagaImpuesto(cantidad);
    }

    boolean recibe(float cantidad) {
        if (encarcelado) {
            return false;
        } else {
            return modificarSaldo(cantidad);
        }
    }

    boolean modificarSaldo(float cantidad) {
        this.saldo += cantidad;
        if (cantidad >= 0) {
            Diario.getInstance().ocurreEvento("Se incrementa el saldo del jugador: " + nombre + " en " + cantidad);
        } else {
            Diario.getInstance().ocurreEvento("Se decrementa el saldo del jugador: " + nombre + " en " + -1 * cantidad);
        }
        return true;
    }

    boolean moverACasilla(int numCasilla) {
        if (encarcelado) {
            return false;
        } else {
            numCasillaActual = numCasilla;
            puedeComprar = false;
            Diario.getInstance().ocurreEvento("Se mueve jugador: " + nombre + " a casilla: " + numCasilla);
            return true;
        }
    }

    protected boolean puedoGastar(float precio) {   //se cambia para usarse en jugador especulador
        if (encarcelado) {
            return true;
        } else {
            return saldo >= precio;
        }
    }

    boolean vender(int ip) {
        boolean vendido = false;
        if (!encarcelado) {
            if (existeLaPropiedad(ip)) {
                if (propiedades.get(ip).vender(this)) {
                    Diario.getInstance().ocurreEvento("Se vende propiedad " + propiedades.get(ip).getNombre() + " del jugador " + nombre);
                    propiedades.remove(ip);
                    vendido = true;
                }
            }
        }
        return vendido;
    }

    boolean tieneAlgoQueGestionar() {
        return propiedades.size() > 0;
    }

    private boolean puedeSalirCarcelPagando() {
        return saldo >= PrecioLibertad;
    }

    boolean salirCarcelPagando() {
        boolean sale = false;
        if (encarcelado && puedeSalirCarcelPagando()) {
            paga(PrecioLibertad);
            encarcelado = false;
            Diario.getInstance().ocurreEvento("Jugador " + nombre + " sale de la carcel pagando " + PrecioLibertad);
            sale = true;
        }
        return sale;
    }

    boolean salirCarcelTirando() {
        boolean sale = Dado.getInstance().salgoDeLaCarcel();
        if (sale) {
            encarcelado = false;
            Diario.getInstance().ocurreEvento("Jugador " + nombre + " sale de la carcel tirando los dados");
        }
        return sale;
    }

    boolean pasaPorSalida() {
        modificarSaldo(PasoPorSalida);
        Diario.getInstance().ocurreEvento("Jugador: " + nombre + " pasa por salida");;
        return true;
    }

    public int compareTo(Jugador otro) {
        return Float.compare(saldo, otro.saldo);
    }

    int cantidadCasasHoteles() {
        int total = 0;
        for (int i = 0; i < propiedades.size(); i++) {
            total += propiedades.get(i).cantidadCasasHoteles();
        }
        return total;
    }

    boolean enBancarrota() {
        return saldo < 0;
    }

    private boolean existeLaPropiedad(int ip) {
        return ip >= 0 && ip < propiedades.size();
    }

    protected int getCasasMax() {   //cambiado para usarse en especulador
        return CasasMax;
    }

    int getCasasPorHotel() {
        return CasasPorHotel;
    }

    protected int getHotelesMax() { //cambiado para usarse en especulador
        return HotelesMax;
    }

    protected String getNombre() {
        return nombre;
    }

    int getNumCasillaActual() {
        return numCasillaActual;
    }

    private float getPrecioLibertad() {
        return PrecioLibertad;
    }

    private float getPremioPasoSalida() {
        return PasoPorSalida;
    }

    //cambiamos visibilidad de protected a public para usarlo en la vista textual en las opciones de gestion
    public ArrayList<TituloPropiedad> getPropiedades() {
        return propiedades;
    }

    boolean getPuedeComprar() {
        return puedeComprar;
    }

    //cambiamos la visibilidad de protected a public para facilitar la accesibilidad de la partida. Consultado al construir
    public float getSaldo() {
        return saldo;
    }

    public boolean isEncarcelado() {
        return encarcelado;
    }

    private boolean puedoEdificarCasa(TituloPropiedad propiedad) {
        boolean puedoEdificarCasa = false;
        float precio = propiedad.getPrecioEdificar();
        if (puedoGastar(precio)) {
            if (propiedad.getNumCasas() < getCasasMax()) {
                puedoEdificarCasa = true;
            }
        }
        return puedoEdificarCasa;
    }

    private boolean puedoEdificarHotel(TituloPropiedad propiedad) {
        boolean puedoEdificarHotel = false;
        float precio = propiedad.getPrecioEdificar();
        if (puedoGastar(precio)) {
            if (propiedad.getNumHoteles() < getHotelesMax() && propiedad.getNumCasas() >= getCasasPorHotel()) {
                puedoEdificarHotel = true;
            }
        }
        return puedoEdificarHotel;
    }

    @Override
    public String toString() {
        ArrayList<String> nombrePropiedades = new ArrayList<>();
        for (int i = 0; i < propiedades.size(); i++) {
            nombrePropiedades.add(propiedades.get(i).getNombre());
        }
        String info = "************\n";
        info = "Nombre: " + nombre
                //+ "\nPuede Comprar: " + puedeComprar
                + "\nSaldo: " + saldo
                + "\nEncarcelado: " + encarcelado
                + "\nPosicion: " + numCasillaActual
                //                + "\nCasasMax: " + CasasMax
                //                + "\nHotelesMax: " + HotelesMax
                //                + "\nPaso por Salida: " + PasoPorSalida
                //                + "\nPrecio Libertad: " + PrecioLibertad
                //                + "\nSaldo inicial: " + SaldoInicial
                + "\nPropiedades: " + nombrePropiedades
                + "\nSalvoconducto: " + salvoconducto;
        info += "\n************";
        return info;
    }

    boolean cancelarHipoteca(int ip) {
        boolean result = false;
        if (isEncarcelado()) {
            return result;
        }
        if (existeLaPropiedad(ip)) {
            TituloPropiedad propiedad = propiedades.get(ip);
            float cantidad = propiedad.getImporteCancelarHipoteca();
            boolean puedoGastar = puedoGastar(cantidad);
            if (puedoGastar) {
                result = propiedad.cancelarHipoteca(this);
                if (result) {
                    Diario.getInstance().ocurreEvento("El jugador " + nombre + " cancela la hipoteca de la propiedad " + propiedades.get(ip).getNombre());
                }
            }
        }

        return result;
    }

    boolean comprar(TituloPropiedad titulo) {
        boolean result = false;
        if (encarcelado) {
            return result;
        }
        if (puedeComprar) {
            float precio = titulo.getPrecioCompra();
            if (puedoGastar(precio)) {
                result = titulo.comprar(this);
                if (result) {
                    propiedades.add(titulo);
                    Diario.getInstance().ocurreEvento("El jugador " + this.nombre + " compra la propiedad " + titulo.toString());
                }
                puedeComprar = false;
            }
        }
        return result;
    }

    boolean hipotecar(int ip) {
        boolean result = false;
        if (encarcelado) {
            return result;
        }
        if (existeLaPropiedad(ip)) {
            TituloPropiedad propiedad = propiedades.get(ip);
            result = propiedad.hipotecar(this);
        }
        if (result) {
            Diario.getInstance().ocurreEvento("El jugador " + nombre + " hipoteca la propiedad " + propiedades.get(ip).getNombre());
        }
        return result;
    }

    boolean construirCasa(int ip) {
        boolean result = false;
        boolean puedoEdificarCasa = false;
        if (encarcelado) {
            return result;
        } else {
            boolean existe = existeLaPropiedad(ip);
            if (existe) {
                TituloPropiedad propiedad = propiedades.get(ip);
                puedoEdificarCasa = puedoEdificarCasa(propiedad);
                if (puedoEdificarCasa) {
                    result = propiedad.construirCasa(this);
                    if (result) {
                        Diario.getInstance().ocurreEvento("El jugador " + nombre + " construye una casa en la propiedad " + propiedades.get(ip).getNombre());
                    }
                }
            }
        }
        return result;
    }

    boolean construirHotel(int ip) {
        boolean result = false;
        if (encarcelado) {
            return result;
        }
        if (existeLaPropiedad(ip)) {
            TituloPropiedad propiedad = propiedades.get(ip);
            boolean puedoEdificarHotel = puedoEdificarHotel(propiedad);
            if (puedoEdificarHotel) {
                result = propiedad.construirHotel(this);
                int casasPorHotel = getCasasPorHotel();
                propiedad.derruirCasas(casasPorHotel, this);
                Diario.getInstance().ocurreEvento("El jugador " + nombre + " construye hotel en la propiedad " + propiedades.get(ip).getNombre());
            }
        }

        return result;
    }
}
