package Semana_004.ex002;

public class IngressoCamarote extends IngressoVip {
    private double adicionalCamarote;

    public IngressoCamarote(double valor, double valorAdicional, double adicionalCamarote) {
        super(valor, valorAdicional);
        this.adicionalCamarote = adicionalCamarote;
    }

    public double getAdicionalCamarote() {
        return adicionalCamarote;
    }

    public void setAdicionalCamarote(double adicionalCamarote) {
        this.adicionalCamarote = adicionalCamarote;
    }

    @Override
    public double valorIngresso() {
        return this.getAdicionalCamarote() + this.getAdicionalVip() + this.getValor();
    } 
}
