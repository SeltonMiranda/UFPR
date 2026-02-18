package Semana_006;

public abstract class Imovel {
    private Endereco endereco;
    private double preco;
    public Imovel(Endereco endereco, double preco) {
        this.endereco = endereco;
        this.preco = preco;
    }
    public Endereco getEndereco() {
        return endereco;
    }
    public void setEndereco(Endereco endereco) {
        this.endereco = endereco;
    }
    public double getPreco() {
        return preco;
    }
    public void setPreco(double preco) {
        this.preco = preco;
    }

    abstract double calcularValorImovel();
}
