package Semana_004.ex001;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        LampadaFluorescente lf = new LampadaFluorescente(false, 20);    
        LampadaLed ld = new LampadaLed(true);
        Scanner sc = new Scanner(System.in);
        String resposta;

        System.out.println("(LED): ");
        ld.mostrarEstado();
        System.out.println("(Fluorescente): ");
        lf.mostrarEstado();

        System.out.println("Escolha o tipo de lâmpada para mudar o estado (LED ou Fluorescente):");
        resposta = sc.nextLine();
        if (resposta.equals("LED")) {
            ld.mudarEstado();
        } else if (resposta.equals("Fluorescente")) {
            lf.mudarEstado();
        }

        System.out.println("(LED): ");
        ld.mostrarEstado();
        System.out.println("(Fluorescente): ");
        lf.mostrarEstado();
        sc.close();
    }
}
