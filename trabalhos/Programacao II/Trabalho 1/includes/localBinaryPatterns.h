#ifndef __LBP__
#define __LBP__

#include "./image.h"
#include "./directoryHandler.h"

// Define o número máximo de padrões LBP possíveis
#define MAX_PATTERNS 256 

/* Aplica o LBP a cada pixel da imagem de entrada.
 * A imagem resultante com as características extraídas é armazenada no ponteiro LBP.
 * @param LBP: Ponteiro para a estrutura Image onde a imagem processada será armazenada.
 * @param image: Ponteiro para a estrutura Image contendo a imagem de entrada.
 * @return Retorna 1 em caso de sucesso e 0 em caso de falha.
 */
int LBP_apply(Image* LBP, Image* image);

/* Cria o histograma a partir da imagem LBP processada.
 * Cada índice do vetor representa a frequência de um padrão LBP específico.
 * @param hist: Vetor onde o histograma será armazenado.
 * @param LBP: Ponteiro para a estrutura Image contendo a imagem LBP.
 */
void LBP_histogram(float hist[MAX_PATTERNS], Image* LBP);

/* Lê um histograma de um arquivo e armazena-o no vetor fornecido.
 * @param hist: Vetor onde o histograma lido será armazenado.
 * @param name: Nome do arquivo de onde o histograma será lido.
 * @return Retorna 1 em caso de sucesso e 0 em caso de falha.
 */
int LBP_read_histogram(float hist[MAX_PATTERNS], const char* name);

/* Escreve o histograma fornecido em um arquivo.
 * @param hist: Vetor contendo o histograma a ser escrito.
 * @param name: Nome do arquivo onde o histograma será salvo.
 * @return Retorna 1 em caso de sucesso e 0 em caso de falha.
 */
int LBP_write_histogram(float hist[MAX_PATTERNS], const char* name); 

/* Normaliza o histograma fornecido utilizando o método minimax.
 * **Nota: Modifica o próprio vetor do histograma fornecido.**
 * @param hist: Vetor do histograma a ser normalizado.
 */ 
void LBP_normalize(float hist[MAX_PATTERNS]);

/* Calcula e retorna a distância euclidiana entre dois vetores de histogramas.
 * @param hist_1: Primeiro vetor de histograma.
 * @param hist_2: Segundo vetor de histograma.
 * @return A distância euclidiana entre os dois vetores.
 */
float LBP_dist(float hist_1[MAX_PATTERNS], float hist_2[MAX_PATTERNS]);

/* Processa uma imagem, aplica o LBP e gera o histograma resultante.
 * O histograma é então salvo em um arquivo.
 * @param filepath: Caminho para a imagem a ser processada.
 * @return Retorna 1 em caso de sucesso e 0 em caso de falha.
 */
int process_image(const char* filepath);

/* Busca a imagem mais similar dentro de um diretório baseado no histograma LBP.
 * Compara o histograma da imagem fornecida com os histogramas das imagens do diretório.
 * @param dir: Ponteiro para o diretório onde as imagens serão buscadas.
 * @param img_path: Caminho para a imagem de referência.
 * @param hist_from_img_arg: Histograma da imagem de referência.
 * @param index: Índice da imagem mais similar encontrada.
 * @return A distância da imagem mais similar encontrada.
 */
float find_similar_image(Directory* dir, const char* img_path, float hist_from_arg[MAX_PATTERNS], size_t *index);

#endif // __LBP__
