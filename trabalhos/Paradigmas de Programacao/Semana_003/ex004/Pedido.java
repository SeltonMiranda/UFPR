package Semana_003.ex004;

import java.util.ArrayList;
import java.util.List;

public class Pedido {
    private int numero;
    private List<ItemPedido> itens;
    public Pedido(int numero) {
        this.numero = numero;
        this.itens = new ArrayList<ItemPedido>();
    }
    public Pedido(int numero, List<ItemPedido> itens) {
        this.numero = numero;
        this.itens = itens;
    }
    public int getNumero() {
        return numero;
    }
    public void setNumero(int numero) {
        this.numero = numero;
    }
    public List<ItemPedido> getItens() {
        return itens;
    }
    public void setItens(List<ItemPedido> itens) {
        this.itens = itens;
    }
    public void addItem(ItemPedido item) {
        this.itens.add(item);
    }
    public double calcularValorPedido() {
        double sum = 0;
        for (ItemPedido item : this.getItens()) {
            sum += item.getPreco();
        }
        return sum;
    }
    public void imprimirPedido() {
        System.out.println("Pedido #" + this.getNumero());
        List<ItemPedido> itens = this.getItens();
        for (int i = 0; i < itens.size(); i++) {
            ItemPedido item = itens.get(i);
            System.out.println(i + " - " + item.getNome() + " ($" + item.getPreco() + ")");
        }
        System.out.println("Total: $" + this.calcularValorPedido());
    }
}
