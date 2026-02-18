package Semana_001;

import java.util.Scanner;

public class ex003 {
    public static int f(int x) {
        if (0 <=x && x < 5) return x;
        if (5 <= x && x < 10) return 2 * x + 1;
        return x - 3;
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int x = sc.nextInt();
        System.out.println("f(x): " + f(x));
        sc.close();
    }
}
