package Semana_006;

import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        List<Imovel> imoveis = new ArrayList<>(200);

        for (int i = 0; i < 200; i++) {
            if (i % 2 == 0) {
                Endereco e = new Endereco("Jardim Botanico",
                                            i, "Jardim Botanico", 
                                            "Curitiba", 
                                            "Paraná");
                imoveis.add(new ImovelNovo(e, 500 + i));
            } else {
                Endereco e = new Endereco("Teatro Guaíra",
                                            i, "Centro", 
                                            "Curitiba", 
                                            "Paraná");
                imoveis.add(new ImovelNovo(e, 200 + i));
            }
        }

        for (Imovel i : imoveis) {
            System.out.println("Imovel " + i + ":" + i.calcularValorImovel());
        }
    }
}
