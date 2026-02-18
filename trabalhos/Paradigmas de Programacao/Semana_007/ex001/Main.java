package Semana_007.ex001;

import java.util.TreeSet;

public class Main {
    public static void main(String[] args) {
        TreeSet<Personagem> personagens = new TreeSet<>();
        Personagem p1 = new Mago("maria", 10, 2);
        Personagem p2 = new Arqueiro("Joao", 5, 5);
        Personagem p3 = new Guerreiro("Arthur", 15, 20);

        personagens.add(p3);
        personagens.add(p2);
        personagens.add(p1);

        for (Personagem p : personagens) {
            System.out.println(p.calcularDano());
        }
    }
}
