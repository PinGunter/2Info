package juegoTexto;

import civitas.CivitasJuego;
import civitas.Diario;
import civitas.OperacionesJuego;
import civitas.SalidasCarcel;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;
import civitas.Casilla;
import civitas.Jugador;
import civitas.Respuestas;
import civitas.TituloPropiedad;

//Se cambia visibilidad de paquete a public para usarlo en el main de prueba
public class VistaTextual {

    CivitasJuego juegoModel;
    private int iGestion = -1;
    private int iPropiedad = -1;
    private static String separador = "=====================";

    private Scanner in;

    //Se cambia visibilidad de paquete a public para usarlo en el main de prueba
    public VistaTextual() {
        in = new Scanner(System.in);
    }

    void mostrarEstado(String estado) {
        System.out.println(estado);
    }

    void pausa() {
        System.out.print("Pulsa una tecla");
        in.nextLine();
    }

    int leeEntero(int max, String msg1, String msg2) {
        Boolean ok;
        String cadena;
        int numero = -1;
        do {
            System.out.print(msg1);
            cadena = in.nextLine();
            try {
                numero = Integer.parseInt(cadena);
                ok = true;
            } catch (NumberFormatException e) { // No se ha introducido un entero
                System.out.println(msg2);
                ok = false;
            }
            if (ok && (numero < 0 || numero >= max)) {
                System.out.println(msg2);
                ok = false;
            }
        } while (!ok);

        return numero;
    }

    int menu(String titulo, ArrayList<String> lista) {
        String tab = "  ";
        int opcion;
        System.out.println(titulo);
        for (int i = 0; i < lista.size(); i++) {
            System.out.println(tab + i + "-" + lista.get(i));
        }

        opcion = leeEntero(lista.size(),
                "\n" + tab + "Elige una opción: ",
                tab + "Valor erróneo");
        return opcion;
    }

    SalidasCarcel salirCarcel() {
        int opcion = menu("Elige la forma para intentar salir de la carcel",
                new ArrayList<>(Arrays.asList("Pagando", "Tirando el dado")));
        return (SalidasCarcel.values()[opcion]);
    }

    Respuestas comprar() {
        int opcion = menu("¿Desea comprar la calle?",
                new ArrayList<>(Arrays.asList("NO", "SI")));
        return (Respuestas.values()[opcion]);
    }

    void gestionar() {
        iGestion = menu("¿Qué número de gestión inmobiliaria desea elegir?",
                new ArrayList<>(Arrays.asList("Vender", "Hipotecar", "Cancelar hipoteca",
                        "Construir casa", "Construir hotel", "Terminar")));
        ArrayList<String> propiedades = new ArrayList<>();
        for (int i = 0; i < juegoModel.getJugadorActual().getPropiedades().size(); i++) {
            propiedades.add(juegoModel.getJugadorActual().getPropiedades().get(i).getNombre());
        }
        if (iGestion != 5) {
            iPropiedad = menu("Indique la propiedad a la que desea aplicar la gestión: ", propiedades);
        }

    }

    public int getGestion() {
        return iGestion;
    }

    public int getPropiedad() {
        return iPropiedad;
    }

    void mostrarSiguienteOperacion(OperacionesJuego operacion) {
        System.out.println("Siguiente operación que se va a realizar");
        System.out.println(operacion);
    }

    void mostrarEventos() {
        while (Diario.getInstance().eventosPendientes()) {
            System.out.println(Diario.getInstance().leerEvento());
        }
    }

    public void setCivitasJuego(CivitasJuego civitas) {
        juegoModel = civitas;
        this.actualizarVista();
    }

    public void actualizarVista() {
        System.out.println("Jugador actual: ");
        System.out.println(juegoModel.infoJugadorTexto());
        System.out.println("Posicion actual: ");
        System.out.println(juegoModel.getCasillaActual());
    }

}
