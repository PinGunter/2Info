/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package villanos;

import java.util.ArrayList;
import esbirros.Mayordomo;

/**
 *
 * @author salva
 */
public class Villano {

    //atributos de instancia
    public String nombre;
    String esconditeSecreto;
    private int fortuna;

    //atributos de clase
    public static String Asociacion = "VillanosSA";

    //atributos de referencia
    private ArrayList<Plan> planes;
    Mayordomo mayordomo;

    //constructor por defecto
    public Villano(String nombre, String esconditeSecreto, int fortuna) {
        this.nombre = nombre;
        this.esconditeSecreto = esconditeSecreto;
        this.fortuna = fortuna;
        this.mayordomo = null;
        this.planes = new ArrayList<>();
        planes.add(new Plan());
    }

    private void setFortuna(int cantidad) {

    }

    public boolean seguirPlanPrioritario() {

    }

    public Plan primerPlanActivo() {

    }

    public static void setAsociacion(Asociacion Asociacion) {

    }
}
