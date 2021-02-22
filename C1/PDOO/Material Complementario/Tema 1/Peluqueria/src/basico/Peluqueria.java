
package basico;

import java.time.LocalDateTime;
import java.time.Month;
import java.util.ArrayList;

public class Peluqueria {  //Clase con visibilidad pública. Su constructor es el que ya existe por defecto
    
    ArrayList<Cita> citas= new ArrayList<>();
       
    Cita darCita(Persona persona){ //Da una cita en un día y hora aleatorios
       	int year= (int)(Math.random()*2+2020);	//hasta 2 años a partir del 2020
        int dia= (int) (Math.random()*30+1);
        int hora= (int) (Math.random()*8+9);      
        LocalDateTime fecha= LocalDateTime.of(year, Month.OCTOBER, dia, hora, 0);
        Cita cita = new Cita(fecha,persona);
        citas.add(cita);
        System.out.println(cita.getFecha());
        return cita;
    }
    
    void cambiarColorPelo(Persona p, ColorPelo colorNuevo){
        p.pelo = colorNuevo;
    }
    
    void anularCita(Cita borrar){
        System.out.println("Peluqueria: cita anulada");
        citas.remove(borrar);
    }
    
}
