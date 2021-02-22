/**
 * @author Salva
 */
package juegoTexto;

import civitas.CivitasJuego;
import civitas.GestionesInmobiliarias;
import civitas.OperacionInmobiliaria;
import civitas.OperacionesJuego;
import civitas.Respuestas;
import civitas.SalidasCarcel;

public class Controlador {

    private CivitasJuego juego;
    private VistaTextual vista;

    //cambiamos la visibilidad de paquete a public para usarlo en el main de prueba
    public Controlador(CivitasJuego juego, VistaTextual vista) {
        this.juego = juego;
        this.vista = vista;
    }

    //cambiamos la visibilidad de paquete a public para poder usarlo en el main de prueba
    public void juega() {
        vista.setCivitasJuego(juego);
        while (!juego.finalDelJuego()) {
            vista.actualizarVista(); // comentado para mejorar visibilidad en la ejecucion
            vista.pausa();
            OperacionesJuego siguiente = juego.siguientePaso();
            vista.mostrarSiguienteOperacion(siguiente);
            if (siguiente != OperacionesJuego.PASAR_TURNO) {
                vista.mostrarEventos();
            }
            if (!juego.finalDelJuego()) {
                switch (siguiente) {
                    case COMPRAR:
                        Respuestas respuesta = vista.comprar();
                        if (respuesta == civitas.Respuestas.SI) {
                            juego.comprar();
                        }
                        juego.siguientePasoCompletado(siguiente);
                        break;
                    case GESTIONAR:
                        vista.gestionar();
                        int gestion = vista.getGestion();
                        int propiedad = vista.getPropiedad();
                        GestionesInmobiliarias gestion_inm = GestionesInmobiliarias.values()[gestion];
                        OperacionInmobiliaria operacion = new OperacionInmobiliaria(gestion_inm, propiedad);
                        switch (operacion.getGestion()) {
                            case VENDER:
                                juego.vender(propiedad);
                                break;
                            case HIPOTECAR:
                                juego.hipotecar(propiedad);
                                break;
                            case CANCELAR_HIPOTECA:
                                juego.cancelarHipoteca(propiedad);
                                break;
                            case CONSTRUIR_CASA:
//                                System.out.println("Precio de edificación: " + juego.getJugadorActual().getPropiedades().get(propiedad).getPrecioEdificar());
//                                System.out.println("Saldo actual: " + juego.getJugadorActual().getSaldo());
                                juego.construirCasa(propiedad);
                                break;
                            case CONSTRUIR_HOTEL:
                                juego.construirHotel(propiedad);
                                break;
                            case TERMINAR:
                                juego.siguientePasoCompletado(siguiente);
                                break;
                        }
                        break;
                    case SALIR_CARCEL:
                        SalidasCarcel salida = vista.salirCarcel();
                        switch (salida) {
                            case TIRANDO:
                                juego.salirCarcelTirando();
                                break;
                            case PAGANDO:
                                juego.salirCarcelPagando();
                                break;
                        }
                        juego.siguientePasoCompletado(siguiente);
                        break;

                }
            } else {
                System.out.println("======= RANKING ========");
                juego.mostrarRanking();
            }
        }
    }
}
