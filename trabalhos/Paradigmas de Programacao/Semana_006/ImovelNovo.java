package Semana_006;

public class ImovelNovo extends Imovel {

    public ImovelNovo(Endereco endereco, double preco) {
        super(endereco, preco);
    }

    @Override
    double calcularValorImovel() {
        return this.getPreco() * 5;
    }
}
