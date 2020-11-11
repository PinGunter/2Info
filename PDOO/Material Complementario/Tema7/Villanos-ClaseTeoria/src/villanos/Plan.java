/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package villanos;

import java.util.ArrayList;
import java.util.Date;

/**
 *
 * @author salva
 */
public class Plan {

    private String nombre;
    private Date fechaConsecucion;
    private int prioridad;
    private int posicionPasoSiguiente;
    private boolean terminado;

    //Atributo de referencia
    private ArrayList<Paso> pasos;
    private ObjetivoMaligno miObjetivoMaligno;

    Plan(String nombre, Date fecha, int prioridad) {
        this.nombre = nombre;
        this.fechaConsecucion = fecha;
        this.prioridad = prioridad;
        this.posicionPasoSiguiente = 0;
        this.terminado = false;
        pasos = new ArrayList<>();
        //pasos.setPasos(); //suponiendo que existiera
        miObjetivoMaligno = null;
    }

    /* Opcion para hacer un constructor con parametros opcionales
      Plan(String nombre, Date fecha, int prioridad, int pps, boolean term) {
        this.nombre = nombre;
        this.fechaConsecucion = fecha;
        this.prioridad = prioridad;
        this.posicionPasoSiguiente = pps;
        this.terminado = term;
    }

    Plan (String n, Date f, int p){
        new(n,f,p,0,false);
    }
     */
    public boolean getTerminado() {
    }

    public boolean estaActivo() {
    }

    public void darPasoSiguiente() {
    }

    public int inversionPasoSiguiente() {
    }
}
