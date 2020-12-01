//Ejemplo para probar atributos y m�todos de instancia y clase, y visibilidad de �stos

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
    
    //m�todo de instancia p�blico
    public void setNombre(String otroNombre){
        nombre=otroNombre;  //modifica un atributo privado
    }
    
    //m�todo de instancia privado
    private void nuevaTemporada(){
        temporadas++;  //modifica un atributo privado, tambi�n podr�a acceder a un atributo p�blico
    }
    
    public void setNombreDeOtraSerie(Serie otraSerie, String otroNombre){
        //la instancia que ejecuta este m�todo le pide a otra instancia diferente que ejecute un m�todo privado
        otraSerie.setNombre(otroNombre); 
    }
    
    //m�todo de instancia toString que genera un string legible con los valores de los atributos de instancia
    @Override  //este m�todo redefine el m�todo heredado de la clase Object
    public String toString(){
        String cadena="";
        for(String c : creadores ){
            cadena= cadena + "    "+ c;
        }
        return "T�tulo: " + nombre+ "\n Plataforma: "+ plataforma+ " \n Temporadas: " + Integer.toString(temporadas) + "\n G�nero: "+ genero + "\n Creadores: "+ cadena;
    //observar que este m�todo de instancia consulta un atributo de clase (plataforma)
    }
    
    //m�todo de instancia que puede cambiar una variable de clase: Peligroso, no hacer!!!
    public void cambiaPlataforma(String otraPlataforma){
        plataforma=otraPlataforma;
    }
    
     //m�todo de clase para cambiar una variable de clase
    public static void setPlataforma(String otraPlataforma){
        plataforma=otraPlataforma;
    }
    
    
    //m�todo de clase que crea instancias y env�a mensajes a �stas para invocar a m�todos p�blicos y privados
    public static void main(String args[]){  
        
        // Pensar qu� hace el programa y qu� debe salir por pantalla antes de ejecutarlo.
        
        System.out.println("Creando series y mostr�ndolas en pantalla");
        ArrayList<String> guionistas1= new ArrayList<>();
        guionistas1.add("David Benioff");
        guionistas1.add("D.B.Weiss");
        Serie serie1= new Serie("Juego de Tronos", 8, "Fantas�a", guionistas1);
        System.out.println(serie1.toString());
        
        ArrayList<String> guionistas2= new ArrayList<>();
        guionistas2.add("Carlos Montero");
        guionistas2.add("Dar�o Madrona");
        Serie serie2= new Serie("Elite", 3, "Drama Juvenil", guionistas2);
        System.out.println(serie2.toString());
        
        System.out.println("Consultando y modificando las series creadas");
        
        //como este m�todo de clase est� dentro de la misma clase, en Java se puede hacer lo siguiente:
        
        serie1.nuevaTemporada(); //Desde el m�todo de clase se puede invocar a un m�todo de instancia privado
        serie1.setNombre("Mundo de Dragones"); //tambi�n p�blico, claro
        serie1.creadores.set(0,"yo"); //se puede acceder a atributos privados y cambiarlos
        serie1.setNombreDeOtraSerie(serie2, "Ricos"); //una instancia cambia un atributo de otra instancia
        serie1.cambiaPlataforma("HBO");  //observa que una instancia, serie1, ha cambiado la plataforma de todas las instancias de Serie existentes
        System.out.println(serie1.toString());
        System.out.println(serie2.toString());
        
        Serie.setPlataforma("Amazon Prime"); //esto si tiene sentido, que la clase cambie la plataforma de todas sus instancias con un m�todo de clase
        System.out.println(serie1.toString());
        System.out.println(serie2.toString());
    }
    
    
}
