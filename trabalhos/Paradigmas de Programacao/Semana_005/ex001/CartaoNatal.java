package Semana_005.ex001;

public class CartaoNatal extends CartaoWeb {
    public CartaoNatal(String destinatario) {
        super(destinatario);
    }

    @Override
    String retornarMensagem(String remetente) {
        return "Feliz Natal " + remetente + "!\n";
    }

    
}
