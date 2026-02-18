Trabalho 1: Solução de Sistemas Lineares Esparsos com Pré-condicionadores

O método dos Gradientes Conjugados é um método iterativo para resolução de sistemas lineares na forma Ax=b. Uma vantagem do método é que cada iteração tem um custo computacional de O(n²), onde n é a dimensão do sistema. Se o método convergir em i iterações, o custo total é O(i n² ). Se i<<n, o método se torna muito atrativo em relação ao uso de Eliminação de Gauss (que tem complexidade O(n³).

Além disso, para sistemas esparsos, o custo de cada iteração pode ser consideravelmente reduzido se forem processados apenas os elementos não nulos da matriz.

O método dos Gradientes Conjugados na sua forma direta, no entanto, apresenta problemas de instabilidade numérica. Para amenizar o problema, usa-se pré-condicionadores M , transformando o sistema:

Ax = b → M−1Ax = M−1b

O pré-condicionador de Jacobi é a matriz diagonal de A: M = D. Este pré-condicionador é bom apenas quando A é estritamente diagonal dominante. O pré-condicionador SSOR (symmetric successive over-relaxation) apresenta melhores resultados e é dado por:

A = L + D + U

M = (D + ωL)D−1 (D + ωU ), ω ∈ [0, 2]

onde L e U são respectivamente a matriz triangular inferior e superior, com diagonal principal NULA e D é a matriz diagonal composta pelos elementos da diagonal principal de A.

Com ω = 1, temos o pré-condicionador Gauss-Seidel; com ω > 1, temos um condicionador com sobrerelaxamento, que tende a aumentar a taxa de convergência do sistema.

A utilização de précondicionadores pode acelerar a convergência, mas só é vantajosa quando a matriz M é facilmente inversível, ou o custo de calcular a solução do sistema M y=r (onde r é o resíduo) é pequeno quando comparado à solução do sistema original.
Objetivo

O objetivo deste trabalho é implementar um programa computacional para testar a eficiência do método dos Gradientes Conjugados com diferentes pré-condicionadores para a resolução de sistemas esparsos nos quais a matriz A é k-diagonal.

Implemente o método de Gradientes Conjugados para achar uma solução x̄ dentro de uma certa tolerância ε. Use o vetor com valores todos iguais a zero como estimativa inicial da solução. Deve ser implementado:

    O método sem pré-condicionador: M = I
    O método com pré-condicionador de Jacobi: M = D

Os pré-condicionadores a de Gauss-Seidel e SSOR apresentam melhor convergência, mas o custo de calcular a solução do sistema My=r é equivalente ao custo de solucionar o sistema original. Portanto, utiliza-se métodos para calcular soluções aproximadas para My=r, como a Fatoração de Cholesky Incompleta. A implementação destes pré-condicionadores é opcional e será considerada como um Bônus.

    O método com pré-condicionador de Gauss-Seidel: M = (D + ωL)D−1 (D + ωU ), com ω = 1.0
    O método com pré-condicionador SSOR: M = (D + ωL)D−1 (D + ωU ), com ω > 1.0

O programa deve "falhar graciosamente" com mensagens de erro apropriadas caso ocorram erros numéricos ou o método não convirja para a solução.
Execução do Programa

O pacote de software a ser construído deve gerar um executável chamado cgSolver , que deve ler da entrada padrão (stdin) 5 (cinco)  valores:

n
k
ω
maxit
ε

onde:

    n: (n>10)  a dimensão do Sistema Linear.
    k: (k>1 e k ímpar)  o número de diagonais da matriz A.
    ω:  o pré-condicionador a ser utilizado:

        ω=-1: sem pré-condicionador
        ω=0.0 : pré-condicionador de Jacobi
        ω=1.0 pré-condicionador de Gauss-Seidel (opcional)
        1.0 < ω < 2.0: pré-condicionador SSOR (opcional)

    maxit:  o número máximo de iterações a serem executadas.
    ε: o erro aproximado absoluto máximo, considerando a norma maxima em x ( max ( |xi - xi-1| ) < ε ).

Entrada de Dados

Os valores não-nulos (das diagonais) da matriz de coeficientes (A) devem ser calculados através da função "generateRandomA"  (vide arquivo sislin.c). Observe que o sistema linear resultante não atende às condições para uso do método do gradiente conjugado, e precisa ser transformado antes da aplicação do método.

Os valores do vetor de termos independentes (b) devem ser gerados através da função "generateRandomB"  (vide arquivo sislin.c).

 

Antes da primeira chamada destas funções, e somente uma vez em todo código, você deve inicializar a sequência de números aleatóreos chamando a função:

srandom(20252);

 Saída de Dados

O resultado deve ser enviado para a saída padrão (stdout) de acordo com o exemplo abaixo. Os valores do vetor solução e resíduo devem ser impressos com printf("%.16g", valor).  Os valores de tempo e normas devem ser impressos com printf("%.8g", valor)


n
x_1 x_2 ... x_n
norma
resíduo
tempo_pc
tempo_iter
tempo_residuo

 

Onde:

    norma: norma máxima do erro aproximado em x após última iteração (||x||∞ = max|xi - xi-1|);
    residuo: A norma euclidiana do resíduo (||r||L2), onde r= b - Ax
    Tempo: deve ser calculado em milisegundos, utilizando-se da função timestamp(), do módulo utils.c .
        Tempo PC: tempo para calcular a matriz pré-condicionante M e preparar o SL para o uso do pré-condicionante. Não incluir tempo de leitura ou geração da matriz de entrada, nem a impressão dos resultados ou cálculo do erro.
        Tempo iter: Tempo médio para calcular uma iteração do método, inclusive o cálculo do erro.
        Tempo residuo: Tempo para calcular a norma euclidiana do resíduo ao final do processo.

MENSAGENS DE ERRO:

Em caso de erros, uma mensagem explicando o ocorrido deve ser impressa na saída padrão de erros (stderr) e a execução do programa deve ser encerrada com código diferente de 0.
Produto a ser Entregue

O trabalho deve ser desenvolvido por um grupo composto por no máximo DOIS alunos regularmente matriculados na disciplina. O grupo NÃO PODE SER ALTERADO no próximo trabalho.

Cada grupo deve entregar um pacote de software completo contendo os fontes em linguagem C. O pacote deve ser arquivado e compactado com tar(1) e gzip(1) em um arquivo chamado login1.tgz (se grupo com 1 membro) ou login1-login2.tgz (se grupo com 2 membros), onde login1 e login2 são os logins dos alunos que compõem o grupo.

O pacote deve ter a seguinte estrutura de diretório e arquivos:

    ./login1-login2/: diretório principal;
    ./login1-login2/LEIAME;
    ./login1-login2/Makefile;

Note que a extração dos arquivos de login1-login2.tgz deve criar o diretório login1-login2 contendo todos os arquivo acima. Os arquivos fonte (*.c e *.h) também devem estar contidos no diretório, ou em algum sub-diretório, desde que o Makefile funcione.

DOCUMENTAÇÃO

Deve ser produzido um arquivo LEIAME contendo as seguintes informações:

    autoria do software, isto é, nome e RA dos membros do grupo;
    Documentação das estruturas de dados e de todos os módulos (a descrição de cada função dos módulos deve ser colocada no código fonte como comentário).

Makefile

O arquivo Makefile deve possuir as regras necessárias para compilar os módulos individualmente e gerar o programa executável. As seguintes regras devem existir OBRIGATORIAMENTE:

    all: compila e produz um executável chamado cgSolver no diretório login1-login2/;
    clean: remove todos os arquivos temporários e os arquivos gerados pelo Makefile (*.o, executável, *.bak, etc.).

Entrega

O prazo final para a entrega deste trabalho é dia 18 de outubro de 2025, 23:59:00h, IMPRETERIVELMENTE.

    O trabalho deve ser entregue via Moodle
    No texto de entrega DEVE CONSTAR OBRIGATORIAMENTE o Nome e Números de Registro Acadêmico (RA) dos membros do grupo;

Avaliação

APENAS OS TRABALHOS QUE FUNCIONAREM SERÃO CORRIGIDOS. Se o trabalho não compilar ou acusar falha de segmentação (Segmentation fault) prematura durante os testes realizados pelo professor (sem que qualquer operação se efetue a contento), trará para o grupo NOTA 0 (ZERO). Também receberão NOTA 0 (ZERO) trabalhos plagiados de qualquer fonte, e/ou com códigos idênticos ou similares. Além disso, apenas trabalhos entregues no prazo marcado receberão nota.

Os itens de avaliação do trabalho e respectivas pontuações são:

    Qualidade da documentação (20 pontos)
    Entrada e saída: funcionamento do programa de acordo com a especificação no que tange execução, entrada e saída (20 pontos)
    Funcionamento: corretude das respostas nos testes executados (50 pontos)
    Eficiência das estruturas de dados utilizadas, desde que devidamente justificadas na documentação (10 pontos)

Defesa: A defesa do trabalho será oral, e definirá a nota individual de cada membro da equipe, de acordo com seu conhecimento a respeito do trabalho.

Os grupos deverão marcar data e horário para demonstração no  Agendamento de Demonstrações T1, no tópico Trabalho 1.
