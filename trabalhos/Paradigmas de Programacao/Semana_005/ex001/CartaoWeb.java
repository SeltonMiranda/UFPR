package Semana_005.ex001;

public abstract class CartaoWeb {
    private String destinatario;

    public CartaoWeb(String destinatario) {
        this.destinatario = destinatario;
    }

    public String getDestinatario() {
        return destinatario;
    }

    public void setDestinatario(String destinatario) {
        this.destinatario = destinatario;
    }

    abstract String retornarMensagem(String remetente);
}
