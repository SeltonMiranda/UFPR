package Semana_007.ex001;

public abstract class Personagem {
    private String nome;
    private int nivel;
    private int forcaBase;

    

    public Personagem(String nome, int nivel, int forcaBase) {
        this.nome = nome;
        this.nivel = nivel;
        this.forcaBase = forcaBase;
    }



    public String getNome() {
        return nome;
    }



    public void setNome(String nome) {
        this.nome = nome;
    }



    public int getNivel() {
        return nivel;
    }



    public void setNivel(int nivel) {
        this.nivel = nivel;
    }



    public int getForcaBase() {
        return forcaBase;
    }



    public void setForcaBase(int forcaBase) {
        this.forcaBase = forcaBase;
    }



    abstract double calcularDano();
}
