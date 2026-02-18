package Semana_003.ex001;

public class Livro {
    private String titulo;
    private int ano;
    public Livro(String titulo, int ano, Autor autor) {
        this.titulo = titulo;
        this.ano = ano;
        this.autor = autor;
    }
    private Autor autor;
    public String getTitulo() {
        return titulo;
    }
    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }
    public int getAno() {
        return ano;
    }
    public void setAno(int ano) {
        this.ano = ano;
    }
    public Autor getAutor() {
        return autor;
    }
    public void setAutor(Autor autor) {
        this.autor = autor;
    }


}
