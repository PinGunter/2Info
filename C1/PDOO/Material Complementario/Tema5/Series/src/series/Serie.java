//Ejemplo para probar atributos y métodos de instancia y clase, y visibilidad de éstos

package series;

import java.util.ArrayList;


public class Serie {
    //atributos de instancia
    private String nombre;
    private int temporadas;
    public String genero;
    private ArrayList <String> creadores;
    
    //atributo de clase
    private static String plataforma="Netflix"; 
    
    //constructor
    
    Serie(String nombre, int temporadas, String genero, ArrayList<String> creadores){
        this.nombre=nombre;
        this.temporadas= temporadas;
        this.genero=genero;
        this.creadores=creadores;
    }
    
    //método de instancia público
    public void setNombre(String otroNombre){
        nombre=otroNombre;  //modifica un atributo privado
    }
    
    //método de instancia privado
    private void nuevaTemporada(){
        temporadas++;  //modifica un atributo privado, también podría acceder a un atributo público
    }
    
    public void setNombreDeOtraSerie(Serie otraSerie, String otroNombre){
        //la instancia que ejecuta este método le pide a otra instancia diferente que ejecute un método privado
        otraSerie.setNombre(otroNombre); 
    }
    
    //método de instancia toString que genera un string legible con los valores de los atributos de instancia
    @Override  //este método redefine el método heredado de la clase Object
    public String toString(){
        String cadena="";
        for(String c : creadores ){
            cadena= cadena + "    "+ c;
        }
        return "Título: " + nombre+ "\n Plataforma: "+ plataforma+ " \n Temporadas: " + Integer.toString(temporadas) + "\n Género: "+ genero + "\n Creadores: "+ cadena;
    //observar que este método de instancia consulta un atributo de clase (plataforma)
    }
    
    //método de instancia que puede cambiar una variable de clase: Peligroso, no hacer!!!
    public void cambiaPlataforma(String otraPlataforma){
        plataforma=otraPlataforma;
    }
    
     //método de clase para cambiar una variable de clase
    public static void setPlataforma(String otraPlataforma){
        plataforma=otraPlataforma;
    }
    
    
    //método de clase que crea instancias y envía mensajes a éstas para invocar a métodos públicos y privados
    public static void main(String args[]){  
        
        // Pensar qué hace el programa y qué debe salir por pantalla antes de ejecutarlo.
        
        System.out.println("Creando series y mostrándolas en pantalla");
        ArrayList<String> guionistas1= new ArrayList<>();
        guionistas1.add("David Benioff");
        guionistas1.add("D.B.Weiss");
        Serie serie1= new Serie("Juego de Tronos", 8, "Fantasía", guionistas1);
        System.out.println(serie1.toString());
        
        ArrayList<String> guionistas2= new ArrayList<>();
        guionistas2.add("Carlos Montero");
        guionistas2.add("Darío Madrona");
        Serie serie2= new Serie("Elite", 3, "Drama Juvenil", guionistas2);
        System.out.println(serie2.toString());
        
        System.out.println("Consultando y modificando las series creadas");
        
        //como este método de clase está dentro de la misma clase, en Java se puede hacer lo siguiente:
        
        serie1.nuevaTemporada(); //Desde el método de clase se puede invocar a un método de instancia privado
        serie1.setNombre("Mundo de Dragones"); //también público, claro
        serie1.creadores.set(0,"yo"); //se puede acceder a atributos privados y cambiarlos
        serie1.setNombreDeOtraSerie(serie2, "Ricos"); //una instancia cambia un atributo de otra instancia
        serie1.cambiaPlataforma("HBO");  //observa que una instancia, serie1, ha cambiado la plataforma de todas las instancias de Serie existentes
        System.out.println(serie1.toString());
        System.out.println(serie2.toString());
        
        Serie.setPlataforma("Amazon Prime"); //esto si tiene sentido, que la clase cambie la plataforma de todas sus instancias con un método de clase
        System.out.println(serie1.toString());
        System.out.println(serie2.toString());
    }
    
    
}
