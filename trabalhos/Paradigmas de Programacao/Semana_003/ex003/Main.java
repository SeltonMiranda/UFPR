package Semana_003.ex003;

public class Main {
    public static void main(String[] args) {
        Aluno joao = new Aluno("Joao");
        Aluno maria = new Aluno("maria");
        Aluno ana = new Aluno("ana");

        Turma turma = new Turma(234, "Rachel");
        turma.adicionarAluno(ana); 
        turma.adicionarAluno(maria); 
        turma.adicionarAluno(joao); 

        for (Aluno a : turma.getAlunos()) {
            System.out.println("Nome: " + a.getNome());
        }
    }
}
