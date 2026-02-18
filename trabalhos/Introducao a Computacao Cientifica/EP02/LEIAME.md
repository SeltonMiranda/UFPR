**Nome: Selton Miranda Rolim**
**GRR:  20235688**

  Neste EP02, foram implementadas implementadas funções que calculam uma EDO através do método de Gauss-Seidel.
Nos testes realizados com as EDO's contidas no arquivo edos.dat, usando a matriz tridiagonal gerada a partir
da EDO no método de Gauss-Seidel se saiu melhor do que calculando diretamente utilizando a EDO.
  Isso provavelmente acontece porque, utilizando diretamente a EDO, há muito mais operações de ponto flutuante
sendo calculadas ao contrário da matriz tridiagonal.
  Portanto, gerar uma matriz tridiagonal a partir de uma EDO para calcular o sistema Ax = B é mais rápido.

 ---

 Para testar com o likwid faça:
 ```bash
 make
 python3 run_likwid_test.py <arquivoComEntrada> (exemplo teste.dat)

```

Para rodar sem o likwid faça:
```bash
make
./resolveEDO < <arquivoComEntrada>
```
