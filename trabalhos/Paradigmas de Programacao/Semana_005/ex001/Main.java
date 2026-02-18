package Semana_005.ex001;
import java.util.List;
import java.util.ArrayList;


// Preguiça
public class Main {

    public static void main() {
        List<CartaoWeb> cartoes = new ArrayList<CartaoWeb>();
        cartoes.add(new CartaoAniversario("Joao"));
        cartoes.add(new CartaoDiaDosNamorados("Joao"));
        cartoes.add(new CartaoNatal("Joao"));

        for (CartaoWeb cartao : cartoes) {
            System.out.println(cartao.retornarMensagem("Maria"));
        }
    }
}
