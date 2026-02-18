package Semana_002.ex002;

public class Main {
    public static void main(String[] args) {
        Time t1 = new Time();
        Time t2 = new Time();

        t1.setHora(2);
        t2.setHora(2);
        t1.setMinuto(23);
        t2.setMinuto(38);

        if (t1.equals(t2.getHora(), t2.getMinuto())) {
            System.out.println("iguais");
        } else if (t1.anterior(t2.getHora(), t2.getMinuto())) {
            System.out.println("anterior");
        } else {
            System.out.println("posterior");
        }
    }
}
