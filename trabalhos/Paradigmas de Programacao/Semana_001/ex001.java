package Semana_001;

import java.util.Scanner;

public class ex001 {

  public static void main() {
    Scanner scanner = new Scanner(System.in);

    int num = scanner.nextInt();
    if (num % 2 == 0) {
      System.out.println("par");
    } else {
      System.out.println("ímpar");
    }
    scanner.close();
  }
}