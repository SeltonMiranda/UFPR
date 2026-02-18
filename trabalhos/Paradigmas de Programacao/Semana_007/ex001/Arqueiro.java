package Semana_007.ex001;

public class Arqueiro extends Personagem{

    public Arqueiro(String nome, int nivel, int forcaBase) {
        super(nome, nivel, forcaBase);
    }

    @Override
    double calcularDano() {
        return this.getForcaBase() * this.getNivel() + 15;
    }
    
}
