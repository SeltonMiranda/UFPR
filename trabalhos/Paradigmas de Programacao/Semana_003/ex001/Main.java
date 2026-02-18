package Semana_003.ex001;

public class Main {
    public static void main(String[] args) {
        Autor autor = new Autor("Machado de Assis", "Brasileiro");
        Livro livro = new Livro("Memorias Postumas de Bras Cubas", 1890, autor);

        System.out.println("Livro: " + livro.getTitulo() + " Ano: " + livro.getAno());
        System.out.println("Autor: " + livro.getAutor().getNome() + " Nacionalidade: " + livro.getAutor().getNacionalidade());
    }
}
