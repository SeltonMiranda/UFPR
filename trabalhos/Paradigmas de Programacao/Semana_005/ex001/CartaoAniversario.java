package Semana_005.ex001;

public class CartaoAniversario extends CartaoWeb {
    
    public CartaoAniversario(String destinatario) {
        super(destinatario);
    }

    @Override
    String retornarMensagem(String remetente) {
        return "Feliz aniversário " + remetente + "!\n";
    }
}
