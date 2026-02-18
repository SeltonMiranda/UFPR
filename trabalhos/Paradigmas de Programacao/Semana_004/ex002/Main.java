package Semana_004.ex002;

public class Main {
    public static void main(String[] args) {
        IngressoVip iv = new IngressoVip(10, 5);
        IngressoCamarote ic = new IngressoCamarote(10, 5, 20);
        IngressoNormal in = new IngressoNormal(10);

        in.imprimir();
        iv.imprimirValor();
        ic.imprimirValor();
    }
}
