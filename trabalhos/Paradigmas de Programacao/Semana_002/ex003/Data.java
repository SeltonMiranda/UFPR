package Semana_002.ex003;

public class Data {
    private int dia;
    private int mes;
    private int ano;

    public int getDia() {
        return dia;
    }
    public void setDia(int dia) {
        this.dia = dia;
    }
    public int getMes() {
        return mes;
    }
    public void setMes(int mes) {
        this.mes = mes;
    }
    public int getAno() {
        return ano;
    }
    public void setAno(int ano) {
        this.ano = ano;
    }
    
    public boolean anterior(Data d) {
        if (this.ano < d.ano) {
            return true;
        } else if (this.ano == d.ano) {
            if (this.mes < d.mes) {
                return true;
            } else if (this.dia < d.dia) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

   public boolean posterior(Data d) {
        if (this.ano > d.ano) {
            return true;
        } else if (this.ano == d.ano) {
            if (this.mes > d.mes) {
                return true;
            } else if (this.dia > d.dia) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        } 
   }

   public boolean equals(Data d) {
    return this.ano == d.ano && this.mes == d.mes && this.dia == d.dia;
   }

   public String toString() {
        return this.dia + "/" + this.mes + "/" + this.ano;
   }
}
