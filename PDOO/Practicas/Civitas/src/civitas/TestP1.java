/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

/**
 *
 * @author salva
 */
public class TestP1 {
    public static void main(String[] args) {
        int jugadores[] = new int[4];
        int leToca;
        for (int i=0; i < 100; i++){
            leToca = Dado.getInstance().quienEmpieza(4);
            for (int j=0; j < 4; j++){
                if (leToca == j)
                    jugadores[j] += 1;
            }
        }
        System.out.println("J0:"+jugadores[0]);
        System.out.println("J1:"+jugadores[1]);
        System.out.println("J2:"+jugadores[2]);
        System.out.println("J3:"+jugadores[3]);

    }
}
