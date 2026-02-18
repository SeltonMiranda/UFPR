package Semana_007.ex002;

public class Monitor {
    private String nome;
    private String grr;
    private int codDisciplina;
    public Monitor(String nome, String grr, int codDisciplina) {
        this.nome = nome;
        this.grr = grr;
        this.codDisciplina = codDisciplina;
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
    public int getCodDisciplina() {
        return codDisciplina;
    }
    public void setCodDisciplina(int codDisciplina) {
        this.codDisciplina = codDisciplina;
    }

    
}
