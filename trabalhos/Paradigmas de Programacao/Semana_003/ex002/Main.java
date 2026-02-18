package Semana_003.ex002;

public class Main {
    public static void main(String[] args) {
        Autor autor = new Autor("Machado de Assis", "Brasileiro");
        Livro livro = new Livro("Memorias Postumas de Bras Cubas", 1890, autor);

        livro.exibir();
    }
}
