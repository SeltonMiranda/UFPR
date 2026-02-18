package Semana_007.ex001;

public class Mago extends Personagem{

    public Mago(String nome, int nivel, int forcaBase) {
        super(nome, nivel, forcaBase);
    }

    @Override
    double calcularDano() {
        return this.getForcaBase() * this.getNivel() * 1.5 - 10;
    }
    
}
