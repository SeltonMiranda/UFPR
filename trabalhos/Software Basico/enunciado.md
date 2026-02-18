Projetos de Implementação
    6.1 implemente o algoritmo proposto na Seção 6.1.2 em assembly.
    6.2 implemente as seguintes variações:
        (a) faça a fusão de nós livres;
        (b) use duas regiões: uma para as informações gerenciais e uma para os nós;
        (c) minimize o número de chamadas ao serviço brk alocando espaços múltiplos de 4096 bytes por vez. Se for solicitado um espaço maior, digamos 5000 bytes, então será alocado um espaço de 4096 ∗ 2 = 8192 bytes para acomodá-lo.
        (d) utilize duas listas: uma com os nós livres e uma com os ocupados;
        (e) escreva variações do algoritmo de escolha dos nós livres:
            • first fit: percorre a lista do início e escolhe o primeiro nó com tamanho maior ou igual ao solicitado;
            • best fit: percorre toda a lista e seleciona o nó com menor bloco, que é maior do que o solicitado;
            • next fit: é first fit em uma lista circular. A busca começa onde a última parou.
    6.3 implemente (em C) um gerenciador que usa o algoritmo Buddy.
    6.4 implemente um procedimento que imprime um mapa da memória da região da heap em todos os algoritmos propostos aqui. Cada byte da parte gerencial do nó deve ser impresso com o caractere "#". O caractere usado para a impressão dos bytes do bloco de cada nó depende se o bloco estiver livre ou ocupado. Se estiver livre, imprime o caractere -". Se estiver ocupado, imprime o caractere "+".


Especificação (2025/1): Página 97 (Projetos de Implementação) 
itens -> 6.1, 6.2-a, 6.2-d, 6.4 

link: [LivroSB](https://www.inf.ufpr.br/bmuller/assets/material/livroSB.pdf)