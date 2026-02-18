package Semana_003.ex002;

public class Autor {
    private String Nome;
    private String nacionalidade;
    public Autor(String nome, String nacionalidade) {
        Nome = nome;
        this.nacionalidade = nacionalidade;
    }
    public String getNome() {
        return Nome;
    }
    public void setNome(String nome) {
        Nome = nome;
    }
    public String getNacionalidade() {
        return nacionalidade;
    }
    public void setNacionalidade(String nacionalidade) {
        this.nacionalidade = nacionalidade;
    }
}
