package Semana_004.ex001;

public class LampadaFluorescente extends Lampada {
    private int comprimento;

    public LampadaFluorescente(boolean estado, int comprimento) {
        super(estado);
        this.comprimento = comprimento;
    }

    public int getComprimento() {
        return comprimento;
    }

    public void setComprimento(int comprimento) {
        this.comprimento = comprimento;
    }

}
