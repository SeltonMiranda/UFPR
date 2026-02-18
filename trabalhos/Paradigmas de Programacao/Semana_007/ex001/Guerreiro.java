package Semana_007.ex001;

public class Guerreiro extends Personagem{

    public Guerreiro(String nome, int nivel, int forcaBase) {
        super(nome, nivel, forcaBase);
    }

    @Override
    double calcularDano() {
        return this.getForcaBase() * this.getNivel() * 1.2;
    }
    
}
