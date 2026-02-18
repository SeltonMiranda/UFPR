package Semana_007.ex002;

import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        List<Monitor> monitores = new ArrayList<>();
        monitores.add(new Monitor("joao", "123", 1062));
        monitores.add(new Monitor("Maria", "321", 1003));
        monitores.add(new Monitor("Ana", "124", 1231));

        for (Monitor m : monitores) {
            System.out.println("Nome: "+m.getNome() + " grr: "+m.getGrr()+" codigo: "+m.getCodDisciplina());
        }
    }
}
