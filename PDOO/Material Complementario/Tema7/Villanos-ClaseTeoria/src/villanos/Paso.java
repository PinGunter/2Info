/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package villanos;

import java.util.Date;

/**
 *
 * @author salva
 */
public class Paso {

    private String descripcion;
    private Date fechaLimite;
    private boolean terminado;
    private int inversion;
    private int ganancia;

    public Paso(String desc, Date fecha, int inver, int ganan) {
        descripcion = desc;
        fechaLimite = fecha;
        inversion = inver;
        ganancia = ganan;
        terminado = false;
    }

    public int getInversion() {

    }

    public int getGanancia() {

    }

    public void setTerminado(boolean estado) {

    }
}
