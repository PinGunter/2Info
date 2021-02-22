/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

import java.util.ArrayList;

/**
 *
 * @author abelrios
 */
public class CivitasJuego {

    private int indiceJugadorActual;
    private MazoSorpresas mazo;
    private Tablero tablero;
    private ArrayList<Jugador> jugadores;
    private GestorEstados gestorEstados;
    private EstadosJuego estado;

    static int numJugadores = 4;
    static final int casillaCarcel = 5;
    static final int numCasillas = 20;

    public CivitasJuego(ArrayList<String> nombres) {
        jugadores = new ArrayList<>();
        for (int i = 0; i < nombres.size(); i++) {
            Jugador j = new Jugador(nombres.get(i));
            jugadores.add(j);
        }
        numJugadores = jugadores.size();
        gestorEstados = new GestorEstados();
        gestorEstados.estadoInicial();
        estado = EstadosJuego.INICIO_TURNO;

        indiceJugadorActual = Dado.getInstance().quienEmpieza(jugadores.size());

        mazo = new MazoSorpresas(true);
        tablero = new Tablero(casillaCarcel);
        inicializarMazoSorpresas(this.tablero); // hacer
        inicializarTablero(this.mazo); // hacer

    }

    private void inicializarTablero(MazoSorpresas mazo) {
        tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("Huerta Los Patos", 100, 0.27f, 300, 300, 300)));
        tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("Calle Rodahuevo", 200, 0.53f, 300, 300, 300)));
        tablero.añadeCasilla(new CasillaSorpresa(mazo, "SUERTE"));
        tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("Calle Recogidas", 400, 0.51f, 600, 600, 600)));
//         carcel (ya añadida)
        tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("Avenida de la Constitución", 500, 0.11f, 700, 700, 700)));
        tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("Huerta Jorobado", 600, 0.6f, 800, 800, 800)));
        tablero.añadeCasilla(new CasillaSorpresa(mazo, "SUERTE"));
        tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("Calle Hierbabuena", 800, 0.08f, 1000, 1000, 1000)));
        tablero.añadeCasilla(new Casilla("Parking Gratuito")); // DESCANSO
        tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("Estación de Autobuses", 1000, 0.75f, 1200, 1200, 1200)));
        tablero.añadeCasilla(new CasillaSorpresa(mazo, "SUERTE"));
        tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("Calle Periodista Daniel Saucedo Aranda", 1100, 0.59f, 1300, 1300, 1300)));
        tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("Calle Periodista Rafael Gómez", 1200, 0.9f, 1400, 1400, 1400)));
        tablero.añadeJuez(); // JUEZ
        tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("Calle Real de la Alhambra", 1300, 0.18f, 1500, 1500, 1500)));
        tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("Calle Pedro Antonio de Alarcón", 1340, 0.77f, 1540, 1540, 1540)));
        tablero.añadeCasilla(new CasillaImpuesto(1000f, "Impuesto")); // IMPUESTO
        tablero.añadeCasilla(new CasillaCalle(new TituloPropiedad("Calle Marqués de Larios", 1800, 0.64f, 2000, 2000, 2000)));
    }

    private void inicializarMazoSorpresas(Tablero t) { // AÑADIR
        mazo.alMazo(new SorpresaConvertirEspeculador(500, "Te conviertes en jugador especulador, ahora pagarás menos impuestos y podrás evitar la cárcel"));
        mazo.alMazo(new SorpresaPagarCobrar( -300, "Multa por exceso de velocidad. Paga 300"));
        mazo.alMazo(new SorpresaCasaHotel( -300, "La nueva PS5 ocupa demasiado espacio, debes hacer reformas. Paga 300 por cada casa u hotel"));
        mazo.alMazo(new SorpresaCasilla( t, 19, "Es la feria de Málaga y no te la puedes perder. Avanza hasta Calle Marqués de Larios"));
        mazo.alMazo(new SorpresaCarcel( t));
        mazo.alMazo(new SorpresaPorJugador( 250, "Vas a cenar con tus amigos pero se les olvida la cartera. Cada jugador te paga 250"));
        mazo.alMazo(new SorpresaSalirCarcel( mazo));
        mazo.alMazo(new SorpresaCasilla( t, 13, "Suspendes el examen de PDOO y tienes que ir a revisión. Ve a la ETSIIT"));
        mazo.alMazo(new SorpresaCasaHotel( 350, "Hay un terremoto y el seguro te paga 350 por cada casa y hotel "));
        mazo.alMazo(new SorpresaPagarCobrar( 600, "Te conviertes en tu propio jefe y ganas 600"));
        mazo.alMazo(new SorpresaPorJugador( -350, "Vas de fiesta con tus amigos sin medidas de seguridad y ahora debes pagarle la PCR"));
    }

    private void contabilizarPasosPorSalida(Jugador jugadorActual) {
        if (tablero.getPorSalida() > 0) {
            jugadorActual.pasaPorSalida();
        }
    }

    private void pasarTurno() {
        indiceJugadorActual = (indiceJugadorActual + 1) % numJugadores;
//        if (indiceJugadorActual < numJugadores - 1) {
//            indiceJugadorActual++;
//        } else {
//            indiceJugadorActual = 0;
//        }
    }

    public void siguientePasoCompletado(OperacionesJuego operacion) {
        estado = gestorEstados.siguienteEstado(getJugadorActual(), estado, operacion);

    }

    public boolean construirCasa(int ip) {
        return jugadores.get(indiceJugadorActual).construirCasa(ip);
    }

    public boolean construirHotel(int ip) {
        return jugadores.get(indiceJugadorActual).construirHotel(ip);
    }

    public boolean vender(int ip) {
        return jugadores.get(indiceJugadorActual).vender(ip);
    }

    public boolean hipotecar(int ip) {
        return jugadores.get(indiceJugadorActual).hipotecar(ip);
    }

    public boolean cancelarHipoteca(int ip) {
        return jugadores.get(indiceJugadorActual).cancelarHipoteca(ip);
    }

    public boolean salirCarcelPagando() {
        return jugadores.get(indiceJugadorActual).salirCarcelPagando();
    }

    public boolean salirCarcelTirando() {
        return jugadores.get(indiceJugadorActual).salirCarcelTirando();
    }

    // Debemos hacerlo publico para usarlo en VistaTextual
    public boolean finalDelJuego() {
        boolean res = false;
        for (int i = 0; i < jugadores.size(); i++) {
            if (jugadores.get(i).enBancarrota()) {
                return true;
            }
        }
        return false;
    }

    private ArrayList<Jugador> ranking() {
        ArrayList<Jugador> ranking = new ArrayList<Jugador>();

        for (int i = 0; i < jugadores.size(); i++) {
            ranking.add(jugadores.get(i));
        }

        for (int i = 0; i < ranking.size(); i++) {
            for (int j = i + 1; j < ranking.size(); j++) {
                if (ranking.get(i).compareTo(ranking.get(j)) < 0) {
                    Jugador jug = new Jugador(ranking.get(i));
                    ranking.set(i, ranking.get(j));
                    ranking.set(j, jug);
                }
            }
        }
        return ranking;

    }

    public void mostrarRanking() {
        ArrayList<Jugador> ranking = ranking();
        for (int i = 0; i < ranking.size(); i++) {
            System.out.println("Posicion " + i + ": "
                    + ranking.get(i));
        }
    }

    //se cambia visibilidad de paquete->publica para poder usarse en vista_textual
    public Casilla getCasillaActual() {
        return tablero.getCasilla(jugadores.get(indiceJugadorActual).getNumCasillaActual());
    }

    public Jugador getJugadorActual() {
        return jugadores.get(indiceJugadorActual);
    }

    public String infoJugadorTexto() {
        String info = jugadores.get(indiceJugadorActual).toString();
        return info;
    }

    // necesita dos llamadas al metodo contabilizarpasoporsalida(jugadoractual)
    private void avanzaJugador() {
        Jugador jugadorActual = jugadores.get(indiceJugadorActual);
        int posicionActual = jugadorActual.getNumCasillaActual();
        int tirada = Dado.getInstance().tirar();
        int posicionNueva = tablero.nuevaPosicion(posicionActual, tirada);
        Casilla casilla = tablero.getCasilla(posicionNueva);
        contabilizarPasosPorSalida(jugadores.get(indiceJugadorActual)); // contabilizarPasosPorSalida(jugadores.get(jugadorActual))
        jugadorActual.moverACasilla(posicionNueva);
        casilla.recibeJugador(indiceJugadorActual, jugadores); // hacer recibeJugador (clase Casilla)
        contabilizarPasosPorSalida(jugadores.get(indiceJugadorActual));
    }

    //boolean comprar()
    public Boolean comprar() {
        Jugador jugadorActual = jugadores.get(indiceJugadorActual);
        int numCasillaActual = jugadorActual.getNumCasillaActual();
        Casilla casilla = tablero.getCasilla(numCasillaActual);
        TituloPropiedad titulo = ((CasillaCalle)casilla).getTituloPropiedad(); // getTitulo es getTituloPropiedad ???
        boolean res = jugadorActual.comprar(titulo);

        return res;
    }

    //OperacionesJuego siguientePaso()
    public OperacionesJuego siguientePaso() {
        Jugador jugadorActual = jugadores.get(indiceJugadorActual);
        OperacionesJuego operacion = gestorEstados.operacionesPermitidas(jugadorActual, estado);
        if (operacion == OperacionesJuego.PASAR_TURNO) {
            pasarTurno();
            siguientePasoCompletado(operacion);
        }
        if (operacion == OperacionesJuego.AVANZAR) {
            avanzaJugador();
            siguientePasoCompletado(operacion);
        }
        return operacion;
    }

}
