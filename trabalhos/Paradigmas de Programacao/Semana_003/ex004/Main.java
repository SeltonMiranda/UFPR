package Semana_003.ex004;

public class Main {
    public static void main(String[] args) {
        ItemPedido p1 = new ItemPedido("Pizza", 35);
        ItemPedido p2 = new ItemPedido("Suco", 8);
        Pedido pedido = new Pedido(101);
        pedido.addItem(p1);
        pedido.addItem(p2);

        pedido.imprimirPedido();
    }
}
