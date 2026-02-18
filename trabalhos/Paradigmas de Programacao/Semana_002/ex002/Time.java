package Semana_002.ex002;

public class Time {
   private int hora; 
   private int minuto; 

   public int getHora() {
    return hora;
}
   public void setHora(int hora) {
    this.hora = hora;
   }
   public int getMinuto() {
    return minuto;
   }
   public void setMinuto(int minuto) {
    this.minuto = minuto;
   }

   public boolean anterior(int h, int m) {
    if (h < this.hora) {
        return true;
    } else if (h == this.hora) {
        if (m < this.minuto) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
   }

   public boolean posterior(int h, int m) {
        if (h > this.hora) {
            return true;
        } else if (h == this.hora) {
            if (m > this.minuto) return true;
            return false;
        } else {
            return false;
        }
   }

   public boolean equals(int h, int m) {
    return h == this.hora && m == this.minuto;
   }

   public String toString() {
        return this.hora + ":" + this.minuto;
   }
}
