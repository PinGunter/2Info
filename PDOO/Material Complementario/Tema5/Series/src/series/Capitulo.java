package series;

import java.util.ArrayList;

/**
 *
 * @author mjfortiz
 */
public class Capitulo {

    private int numero;
    private String titulo;
    private String descripcion;
    private ArrayList<String> elenco;
    private static int contadorCapitulos = 0;

    private Serie miSerie;

    Capitulo() {  //"constructor" sin argumentos, da valores por defecto
        numero = 1;
        titulo = "El Comienzo";
        descripcion = null;
    }

    Capitulo(int numero, String tit, String des) { //constructor que inicializa todos los atributos
        this.numero = numero;
        titulo = tit;
        descripcion = des;
        elenco = new ArrayList<>(); //dar un valor por defecto a algún atributo
    }

    Capitulo(String tit, String des) { //constructor que inicializa atributos
        contadorCapitulos = contadorCapitulos + 1;
        numero = contadorCapitulos;
        titulo = tit;
        descripcion = des;
        elenco = new ArrayList<>(); //dar un valor por defecto a algún atributo
    }

    Capitulo(Capitulo otroCapitulo) { //constructor de copia
        numero = otroCapitulo.numero;
        titulo = otroCapitulo.titulo;
        descripcion = otroCapitulo.descripcion;
        elenco = otroCapitulo.elenco;

    }

    @Override
    public String toString() {
        return "numero de capitulo: " + numero + ", titulo: " + titulo + ", descripcion "
                + descripcion;
    }

    public static void main(String args[]) {
        Capitulo cap = new Capitulo(); // llamando al constructor por defecto, si no hay
        System.out.println(cap);

        Capitulo capA = new Capitulo(); //llamada a constructor sin argumentos
        System.out.println(capA);
        Capitulo capB = new Capitulo();
        System.out.println(capB);

//        Llamando al constructor con tres argumentos
        Capitulo capC = new Capitulo(1, "El caballo", "Se encuentran un caballo");
        System.out.println(capC);
        Capitulo capD = new Capitulo(2, "El lago", "Se montan en una barca");
        System.out.println(capD);

//        Llamando al constructor con dos argumentos que dá valores por defecto
        Capitulo capE = new Capitulo("El bicho", "El bicho le pica");
        System.out.println(capE);
        Capitulo capF = new Capitulo("La medicina", "Se toma la medicina");
        System.out.println(capF);
        Capitulo capG = new Capitulo(8, "La trampa", "Le tienden una trampa");
        System.out.println(capG);

//        Llamando al constructor de copia
        Capitulo capituloCopiado = new Capitulo(capG);
        System.out.println(capituloCopiado);

//        Probando a ver que son dos objetos diferentes, aunque sí compartirán el elenco por ser no invariable
        capG.numero = 99;
        System.out.println(capituloCopiado);
    }

}
