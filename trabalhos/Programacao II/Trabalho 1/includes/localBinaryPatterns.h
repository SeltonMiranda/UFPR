#ifndef __LBP__
#define __LBP__

#include "./image.h"

// Quantidade possível de padrões LBP
// (no tipo de imagem que estou usando)
#define MAX_PATTERNS 256 

// Aplica o lbp para cada pixel da imagem, retorna para o ponteiro
// lbpImage a imagem lbp após extrair as características
// retorna 1 se sucesso e 0 se falha
int LBP_apply(Image* LBP, Image* image);

// Cria o histograma a partir da imagem lbp retorna o vetor no
// ponteiro hist, o retorno da função é 1 se sucesso
// ou 0 em caso de falha
void LBP_histogram(float hist[MAX_PATTERNS], Image *LBP);

// Lê o vetor de caracteristicas presente em um arquivo,
// colocando-o no vetor passado como parâmetro 
// retorna 1 em caso de sucesso e 0 em caso de falha
int LBP_read_histogram(float hist[MAX_PATTERNS], const char* name);

// Escreve o histograma passado como parâmetro em um
// arquivo, retorna 1 em caso de sucesso e 0 em caso de falha
int LBP_write_histogram(float hist[MAX_PATTERNS], const char* name); 

// Compara dois floats, usado no qsort
//int compare_floats(const void *a, const void *b)

// Normalização do histograma pelo método *minimax*
// **Nota: Modifica o próprio histograma**
void LBP_normalize(float hist[MAX_PATTERNS]);

// Retorna a distância *euclidiana* entre dois vetores
float LBP_dist(float hist_1[MAX_PATTERNS], float hist_2[MAX_PATTERNS]);
#endif // __LBP__
