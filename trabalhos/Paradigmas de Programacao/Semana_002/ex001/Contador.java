package Semana_002.ex001;

public class Contador {
    private int count;

    public int getCount() {
        return count;
    }

    public void setCount(int count) {
        this.count = count;
    }

    public void zero() {
        this.count = 0;
    }

    public void inc() {
        this.count++;
    }

    public void dec() {
        if (this.count > 0) {
            this.count--;
        }
    }
}
