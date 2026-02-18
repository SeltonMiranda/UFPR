O objetivo deste exercício é implementar programas para a solução de Equações Diferenciais Ordinárias.
Especificação

Implementar programas para resolver a equação diferencial abaixo, considerando as condições de contorno indicadas:

y^{´´} + (x+1)y^{´} -  2xy = (1 - x^2) e^{-x} , x \in (0, 1) , y(0) = -1 e y(1) = 0

Gere resultados para n = 5, 10, 100, 1000 (malha x).

Seu programa deve exibir a matriz aumentada do sistema linear resultante (diagonais e termos independentes apenas), sua solução (calculada com o método de Gauss-Seidel), a norma L2 do resíduo e o tempo gasto para a solução.

Use como critério de parada do método como sendo o máximo de 50 iterações.

Você deve implementar duas versões do método de Gauss-Seidel, calculando o tempo gasto em cada versão:

    Gerar os valores das diagonais e termos independentes em vetores para depois aplicar Gauss-Seidel usando estes vetores;
    Aplicar Gauss-Seidel calculando diretamente os valores de diagonais e termos independentes, sem usar vetores;

 
Arquivos auxiliares

Os arquivos utils.* contém funções de uso geral, incluindo a função timestamp(), a ser usada neste trabalho e nos próximos.

Os arquivo edo.h contém definições de tipos para a implementação do programa.

Os demais arquivos são sugestões de módulos para o desenvolvimento do programa.
