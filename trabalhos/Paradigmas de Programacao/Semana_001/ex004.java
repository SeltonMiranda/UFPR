package Semana_001;

import java.util.Scanner;

public class ex004 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int peso = sc.nextInt();
        int normal = 0;

        while (peso != -1 ) {
            int altura = sc.nextInt();
            if (peso / (altura * altura) <= 25) {
                normal++;
            }
            peso = sc.nextInt();
        }
        System.out.println("Pessoas com peso normal: " + normal);

        sc.close();
    }
}
