package Semana_003.ex003;

import java.util.List;
import java.util.ArrayList;

public class Turma {
    private int codigo;
    private String professor;
    private List<Aluno> alunos;

    public Turma(int codigo, String professor) {
        this.codigo = codigo;
        this.professor = professor;
        this.alunos = new ArrayList<Aluno>();
    }
    public Turma(int codigo, String professor, List<Aluno> alunos) {
        this.codigo = codigo;
        this.professor = professor;
        this.alunos = alunos;
    }
    public int getCodigo() {
        return codigo;
    }
    public void setCodigo(int codigo) {
        this.codigo = codigo;
    }
    public String getProfessor() {
        return professor;
    }
    public void setProfessor(String professor) {
        this.professor = professor;
    }
    public List<Aluno> getAlunos() {
        return alunos;
    }
    public void setAlunos(List<Aluno> alunos) {
        this.alunos = alunos;
    }

    public void adicionarAluno(Aluno a) {
        this.alunos.add(a);
    }

    
}
