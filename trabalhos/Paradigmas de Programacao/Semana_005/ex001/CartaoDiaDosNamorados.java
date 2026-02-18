package Semana_005.ex001;

public class CartaoDiaDosNamorados extends CartaoWeb {
    public CartaoDiaDosNamorados(String destinatario) {
        super(destinatario);
    }

    @Override
    String retornarMensagem(String remetente) {
        return "Feliz Dia dos Namorados " + remetente + "!\n";
    }

    
}
