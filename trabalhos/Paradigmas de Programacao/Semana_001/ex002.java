package Semana_001;

public class ex002 {
    public static void main(String[] args) {
        int sum = 0;
        int it = 10;
        int i = 0;
        int num = 0;
        while (i < it) {
            if (num % 3 == 0) {
                sum += num;
                i++;
            }
            num++;
        }

        System.out.println("Soma dos 10 primeiros números múltiplos de 3: " + sum);
    }
}
