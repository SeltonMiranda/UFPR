package Semana_003.ex003;

public class Aluno {
    private String nome;
    private String grr;

    public Aluno(String nome) {
        this.nome = nome;
        this.grr = null;
    }

    public Aluno(String nome, String grr) {
        this.nome = nome;
        this.grr = grr;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getGrr() {
        return grr;
    }

    public void setGrr(String grr) {
        this.grr = grr;
    }

    
}
