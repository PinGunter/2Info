/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

import java.util.ArrayList;

/**
 *
 * @author salva
 */
public class TestP1 {

    public static void main(String[] args) {
        int jugadores[] = new int[4];
        int leToca;
        for (int i = 0; i < 100; i++) {
            leToca = Dado.getInstance().quienEmpieza(4);
            for (int j = 0; j < 4; j++) {
                if (leToca == j) {
                    jugadores[j] += 1;
                }
            }
        }
        //quien comienza
        System.out.println("J0:" + jugadores[0]);
        System.out.println("J1:" + jugadores[1]);
        System.out.println("J2:" + jugadores[2]);
        System.out.println("J3:" + jugadores[3]);

        //dado
        System.out.println("Activamos modo debug del dado");
        Dado.getInstance().setDebug(true);
        System.out.println(Diario.getInstance().leerEvento());
        for (int i = 0; i < 5; i++) {
            System.out.println(Dado.getInstance().tirar());
        }
        System.out.println("Desctivamos modo debug del dado");
        Dado.getInstance().setDebug(false);
        System.out.println(Diario.getInstance().leerEvento());
        for (int i = 0; i < 5; i++) {
            System.out.println(Dado.getInstance().tirar());
        }
        System.out.println("Ultimo resultado:" + Dado.getInstance().getUltimoResultado());

        System.out.println("Salgo de la carcel?");
        boolean salir = Dado.getInstance().salgoDeLaCarcel();
        System.out.println("Resultado: " + Dado.getInstance().getUltimoResultado() + "--> " + salir);

        //enumerados
        System.out.println(TipoCasilla.DESCANSO);
        System.out.println(TipoSorpresa.IRCARCEL);
        System.out.println(OperacionesJuego.COMPRAR);
        System.out.println(EstadosJuego.INICIO_TURNO);

        //mazo sorpresas
        MazoSorpresas mazo = new MazoSorpresas();
        Sorpresa primera = new Sorpresa("Primera");
        Sorpresa segunda = new Sorpresa("Segunda");
        mazo.alMazo(primera);
        mazo.alMazo(segunda);
        System.out.println("Siguiente sorpresa: " + mazo.siguiente().getNom());
        mazo.inhabilitarCartaEspecial(segunda);
        System.out.println(Diario.getInstance().leerEvento());
        mazo.habilitarCartaEspecial(segunda);
        System.out.println(Diario.getInstance().leerEvento());

        //tablero
        Tablero tablero = new Tablero(3);
        ArrayList<Casilla> casillas = new ArrayList<>();
        for (int i = 0; i < 6; i++) {
            casillas.add(new Casilla("Casilla: " + i));
            tablero.añadeCasilla(casillas.get(i));
        }
        tablero.añadeJuez();
        int destino = 0;
        int origen = 0;
        //lanzamos dado
        for (int i = 0; i < 15; i++) {
            if (i == 0) {
                destino = tablero.nuevaPosicion(i, Dado.getInstance().tirar());
                System.out.println("Origen: " + 0 + " Destino: " + destino + "\t Dado: " + Dado.getInstance().getUltimoResultado());
            }                
            else{                
                origen = destino;
                destino = tablero.nuevaPosicion(origen,Dado.getInstance().tirar());
                System.out.println("Origen: " + origen + " Destino: " + destino + "\t Dado: " + Dado.getInstance().getUltimoResultado());
            }
            
        }

//        Casilla c1 = new Casilla("primera");
//        Casilla c2 = new Casilla("segunda");
//        Casilla c3 = new Casilla("tercera");
//        Casilla c4 = new Casilla("cuarta");
//        Casilla c5 = new Casilla("quinta");
    }
}
