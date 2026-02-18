package Semana_006;

public class ImovelVelho extends Imovel {

    public ImovelVelho(Endereco endereco, double preco) {
        super(endereco, preco);
    }

    @Override
    double calcularValorImovel() {
        return this.getPreco() * 2;
    }

    
}
