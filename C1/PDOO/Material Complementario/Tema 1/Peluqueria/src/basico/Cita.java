package basico;

/**
 *
 * @author salva
 */
import java.time.LocalDateTime;

public class Cita {
    private LocalDateTime fecha;
    private Persona persona;
    
    public Cita(LocalDateTime f, Persona p){
        fecha = f;
        persona = p;
    }
    
    public LocalDateTime getFecha(){
        return fecha;
    }
    
}
