package Semana_007.ex003;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        List<Professor> professores = new LinkedList<>();
        professores.add(new Professor("Joao", "123"));
        professores.add(new Professor("maria", "324"));
        professores.add(new Professor("arthur", "2145"));
        professores.add(new Professor("ana", "9213"));
        professores.add(new Professor("felipe", "213"));

        String matricula = "2145";
        Iterator<Professor> it = professores.iterator();
        while (it.hasNext()) {
            Professor p = it.next();
            if (p.getGrr().equals(matricula)) {
                it.remove();
                break;
            }
        }
    }
}
