EP-02 - Sistemas Lineares

Objetivo

Implementar um programa para calcular a solução de uma família de Equações Diferenciais Ordinárias (EDO's) usando o Método de Gauss-Seidel.

Enunciado

Considere uma EDO genérica do tipo y'' + py' + qy = r(x), onde p e q são coeficientes reais e r(x) = r1x + r2x² + r3cos(x) + r4ex , sendo r1, r2, r3  e r4 coeficientes reais.

Faça um programa chamado resolveEDO que leia pela entrada padrão (stdin) a definição de uma família de EDO's genéricas e gera na saída a solução destas EDO.

O formato de entrada dos dados consiste de:

    1ª linha: quantidade de pontos da malha da EDO;
    2ª linha: intervalo a e b onde a EDO é válida;
    3ª linha: os valores de contorno  y(a) e y(b);
    4ª linha: os coeficientes p e q da EDO genérica;
    5ª linha em diante: uma ou mais linhas contendo os coeficientes r1, r2, r3  e r4 da definição da função r(x), representando diversas  EDO's que diferem apenas no valor de r(x).

O programa deverá gerar na saída padrão (stdout), para cada EDO, a ordem do Sistema linear tri-diagonal 1ª linha, seguida da matriz aumentada do SL tridiagonal (matriz de coeficientes e termos independentes, veja exemplo abaixo).

Após, deve ser exibida a solução do SL, obtida usando-se o Método de Gauss-Seidel. O critério de parada deve ser a quantidade máxima de iterações (100) e a norma L2 do resíduo (≤ 10-⁵).

A norma L2 do resíduo para um SL Ax = B é dada  por:

        R = B - Ax é o resíduo 
        ||R|| = sqrt(somatório i = 1 até n de (|R_i)|^2)  é a norma L2 do resíduo

Finalmente devem ser impressos  a quantidade de iterações do método, a norma L2 do resíduo, e o tempo em milisegundos gasto no cálculo da solução.

Todos os cálculos de ponto flutuante devem ser efetuados com precisão dupla e com arredondamento para baixo (use a função  fesetround ).

Os valores de saída devem ser mostrados com 15  casas decimais (formato "%.15e"). O valor do tempo da solução deve ser exibido com 8 casas decimais (formato "%.8e").

ATENÇÃO: nada deve ser impresso além dos valores citados, pois os resultados serão verificados via script. Implementações que não respeitarem essa restrição receberão nota zero. 

Exemplo de Execução do programa

Entrada:

5
0 3.14159265
2 -2
0.5 -0.7
0 0 0 0
0 0 1 0

Saída:

5
 -2.191908974027051e+00  1.130899693749999e+00  0.000000000000000e+00  0.000000000000000e+00  0.000000000000000e+00 -1.738200612500001e+00
  8.691003062500000e-01 -2.191908974027051e+00  1.130899693749999e+00  0.000000000000000e+00  0.000000000000000e+00  0.000000000000000e+00
  0.000000000000000e+00  8.691003062500000e-01 -2.191908974027051e+00  1.130899693749999e+00  0.000000000000000e+00  0.000000000000000e+00
  0.000000000000000e+00  0.000000000000000e+00  8.691003062500000e-01 -2.191908974027051e+00  1.130899693749999e+00 -0.000000000000000e+00
  0.000000000000000e+00  0.000000000000000e+00  0.000000000000000e+00  8.691003062500000e-01 -2.191908974027051e+00  2.261799387499999e+00

  8.670021162851619e-01  1.434097810760343e-01 -3.883423041890597e-01 -8.628986168079400e-01 -1.374028244474588e+00
25
  9.654027516477739e-06
  2.69700004e-03

5
 -2.191908974027051e+00  1.130899693749999e+00  0.000000000000000e+00  0.000000000000000e+00  0.000000000000000e+00 -1.500774831387082e+00
  8.691003062500000e-01 -2.191908974027051e+00  1.130899693749999e+00  0.000000000000000e+00  0.000000000000000e+00  1.370778388748534e-01
  0.000000000000000e+00  8.691003062500000e-01 -2.191908974027051e+00  1.130899693749999e+00  0.000000000000000e+00  4.920811303936179e-10
  0.000000000000000e+00  0.000000000000000e+00  8.691003062500000e-01 -2.191908974027051e+00  1.130899693749999e+00 -1.370778380225440e-01
  0.000000000000000e+00  0.000000000000000e+00  0.000000000000000e+00  8.691003062500000e-01 -2.191908974027051e+00  2.024373606879162e+00

  7.069575324298638e-01  4.315653657812325e-02 -3.384462306215883e-01 -6.891446957414636e-01 -1.196814970002608e+00
25
  8.260028095304346e-06
  2.25899997e-03

 

 

No exemplo acima, duas EDO's foram solucionadas, ambas válidas no intervalo x e (0, pi) e com condições de contorno y(0) = -2 e
y(pi) = 2:

    y'' + 0.5y' - 0.7y = 0
    y'' + 0.5y' - 0.7y = cos(x)

Execução do LIKWID

Faça um script que após executar o programa resolveEDO, use o LIKWID para exibir APENAS as informações abaixo:

    Operações aritméticas: utilizar o grupo FLOPS_DP do LIKWID e reportar o contador FP_ARITH_INST_RETIRED_SCALAR_DOUBLE (quantidade de instruções aritméticas de ponto flutuante em dupla precisão). Devem ser obtidos estes valores usando-se o Método de Gauss-Seidel no cálculo de cada solução das EDO's (vide abaixo).

Exemplo de execução do script

Entrada:

5
0 3.14159265
2 -2
0.5 -0.7
0 0 0 0
0 0 1 0

Saída:

5
 -2.191908974027051e+00  1.130899693749999e+00  0.000000000000000e+00  0.000000000000000e+00  0.000000000000000e+00 -1.738200612500001e+00
  8.691003062500000e-01 -2.191908974027051e+00  1.130899693749999e+00  0.000000000000000e+00  0.000000000000000e+00  0.000000000000000e+00
  0.000000000000000e+00  8.691003062500000e-01 -2.191908974027051e+00  1.130899693749999e+00  0.000000000000000e+00  0.000000000000000e+00
  0.000000000000000e+00  0.000000000000000e+00  8.691003062500000e-01 -2.191908974027051e+00  1.130899693749999e+00 -0.000000000000000e+00
  0.000000000000000e+00  0.000000000000000e+00  0.000000000000000e+00  8.691003062500000e-01 -2.191908974027051e+00  2.261799387499999e+00

  8.670021162851619e-01  1.434097810760343e-01 -3.883423041890597e-01 -8.628986168079400e-01 -1.374028244474588e+00
25
  9.654027516477739e-06
  2.69700004e-03

5
 -2.191908974027051e+00  1.130899693749999e+00  0.000000000000000e+00  0.000000000000000e+00  0.000000000000000e+00 -1.500774831387082e+00
  8.691003062500000e-01 -2.191908974027051e+00  1.130899693749999e+00  0.000000000000000e+00  0.000000000000000e+00  1.370778388748534e-01
  0.000000000000000e+00  8.691003062500000e-01 -2.191908974027051e+00  1.130899693749999e+00  0.000000000000000e+00  4.920811303936179e-10
  0.000000000000000e+00  0.000000000000000e+00  8.691003062500000e-01 -2.191908974027051e+00  1.130899693749999e+00 -1.370778380225440e-01
  0.000000000000000e+00  0.000000000000000e+00  0.000000000000000e+00  8.691003062500000e-01 -2.191908974027051e+00  2.024373606879162e+00

  7.069575324298638e-01  4.315653657812325e-02 -3.384462306215883e-01 -6.891446957414636e-01 -1.196814970002608e+00
25
  8.260028095304346e-06
  2.25899997e-03

FP_ARITH_INST_RETIRED_SCALAR_DOUBLE,1467
FP_ARITH_INST_RETIRED_SCALAR_DOUBLE,1467

É imprescindível que sejam respeitadas as seguintes condições:

    Os códigos devem ser compilados com GCC e a opção -O0

    O código deve ser instrumentado com a biblioteca do LIKWID;

    Os códigos devem ser compilados na mesma máquina utilizada para os testes. Você pode escolher um computador de sua preferência, desde que possua os contadores Likwid especificados. Não utilize as servidoras de processamento do DInf que tenham uso compartilhado. Elas podem ser máquinas virtuais e o compartilhamento impede medidas de desempenho. Em caso de dúvida, consulte o professor.

Makefile

O arquivo Makefile deve possuir as regras necessárias para compilar os módulos individualmente e gerar o programa executável. As seguintes regras devem existir OBRIGATORIAMENTE:

all: compila e produz um executável chamado resolveEDO no diretório corrente;

purge: remove todos os arquivos temporários e os arquivos gerados pela compilação do programa (*.o, executável, etc.). 

Código Modular

Você deve deixar seu código modular, com funções e arquivos específicos para implementar cada parte do programa. O programa principal deve estar em um módulo separado dos demais (resolveEDO.c), contendo apenas a função main().

As funções/código-fonte devem conter comentários adequados descrevendo cada função.

A documentação do código deve conter:

    Nome e GRR (em cada código-fonte)

    A descrição de cada função e dos seus parâmetros

    A descrição das estruturas de dados

    Todos os possíveis códigos de erro que a função pode produzir, explicando o significado de cada um deles

    Explicações sobre o algoritmo que por ventura sejam necessárias para a compreensão do código

O que deve ser entregue

Este exercício deve ser feito individualmente. Deve-se entregar os códigos-fonte do programa (em linguagem C), makefile e um arquivo LEIAME contendo o nome do(a) aluno(a) e limitações do programa (por exemplo, casos que o programa não funciona). Todos estes itens devem estar sob o diretório <login> (por exemplo, bff21/*) e este diretório deve ser salvo e compactado em um arquivo do tipo <login>.tgz (por exemplo, usando o comando  tar  -cvzf  <login>.tgz   <login>/* ). 

Note que a extração dos arquivos de <login>.tgz deve criar o diretório <login> contendo todos os arquivo acima. Os arquivos fonte também devem estar contidos no diretório, ou em algum sub-diretório, desde que o Makefile funcione. O script anexo a este enunciado deve ser utilizado para verificar se a entrega está conforme à especificação.
