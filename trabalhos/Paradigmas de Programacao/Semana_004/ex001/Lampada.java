package Semana_004.ex001;

public class Lampada {
    private boolean estado;

    public Lampada(boolean estado) {
        this.estado = estado;
    }

    public void mudarEstado() {
        this.estado = !this.estado;
    }

    public void mostrarEstado() {
        if (this.estado == true) {
            System.out.println("Estado: ligada");
        } else {
            System.out.println("Estado: desligada");
        }
    }
    
}
