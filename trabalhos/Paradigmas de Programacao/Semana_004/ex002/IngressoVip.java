package Semana_004.ex002;

public class IngressoVip extends Ingresso {
    private double adicionalVip;

    public IngressoVip(double valor, double adicionalVip) {
        super(valor);
        this.adicionalVip = adicionalVip;
    }

    public double getAdicionalVip() {
        return adicionalVip;
    }

    public void setAdicionalVip(double adicionalVip) {
        this.adicionalVip = adicionalVip;
    }

    public double valorIngresso() {
        return this.getValor() + this.getAdicionalVip();
    }
}
