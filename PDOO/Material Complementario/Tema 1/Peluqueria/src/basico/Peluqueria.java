
package basico;

import java.time.LocalDateTime;
import java.time.Month;
import java.util.ArrayList;

public class Peluqueria {  //Clase con visibilidad pública. Su constructor es el que ya existe por defecto
    
    ArrayList<LocalDateTime> citas= new ArrayList<>();
       
    LocalDateTime darCita(){ //Da una cita en un día y hora aleatorios
       	int year= (int)(Math.random()*2+2020);	//hasta 2 años a partir del 2020
        int dia= (int) (Math.random()*30+1);
        int hora= (int) (Math.random()*8+9);      
        LocalDateTime cita= LocalDateTime.of(year, Month.OCTOBER, dia, hora, 0);
        citas.add(cita);
        return cita;
    }
    
}
