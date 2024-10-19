#ifndef __IMAGE__
#define __IMAGE__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M_PI 3.14159265358979323846
#define SIND(a) (sin(((a) * M_PI)/180.0))
#define COSD(a) (cos(((a) * M_PI)/180.0))
#define DEFAULT_THRESHOLD 0.5

typedef enum {
    P2 = 0, // Formato ASCII para imagens em tons de cinza
    P5 = 1  // Formato binário para imagens em tons de cinza
} FORMAT_TYPE;

typedef struct Image {
    FORMAT_TYPE type; // Tipo de formato da imagem (P2 ou P5)
    uint32_t width;   // Largura da imagem em pixels
    uint32_t height;  // Altura da imagem em pixels
    uint8_t* pixels;  // Ponteiro para o array de pixels da imagem
    uint8_t maxval;   // Valor máximo que um pixel pode assumir, no caso 255
} Image;

/**
 * Lê uma imagem PGM a partir do arquivo especificado.
 * @param path: Caminho para o arquivo de imagem a ser lido.
 * @param image: Ponteiro para a estrutura Image onde as informações da imagem serão armazenadas.
 * @return Retorna 1 em caso de sucesso e 0 em caso de falha.
 */
int image_read(const char* path, Image* image);

/**
 * Lê uma imagem PGM no formato P2 (ASCII).
 * @param input: Ponteiro para o arquivo de entrada.
 * @param image: Ponteiro para a estrutura Image onde as informações da imagem serão armazenadas.
 * @return Retorna 1 em caso de sucesso e 0 em caso de falha.
 */
int read_P2_PGM(FILE* input, Image* image);

/**
 * Lê uma imagem PGM no formato P5 (binário).
 * @param input: Ponteiro para o arquivo de entrada.
 * @param image: Ponteiro para a estrutura Image onde as informações da imagem serão armazenadas.
 * @return Retorna 1 em caso de sucesso e 0 em caso de falha.
 */
int read_P5_PGM(FILE* input, Image* image);

/**
 * Escreve uma imagem PGM no formato P2 (ASCII) em um arquivo.
 * @param output: Ponteiro para o arquivo de saída.
 * @param image: Ponteiro para a estrutura Image contendo a imagem a ser escrita.
 */
void write_P2_PGM(FILE* output, Image* image);

/**
 * Escreve uma imagem PGM no formato P5 (binário) em um arquivo.
 * @param output: Ponteiro para o arquivo de saída.
 * @param image: Ponteiro para a estrutura Image contendo a imagem a ser escrita.
 */
void write_P5_PGM(FILE* output, Image* image);

/**
 * Cria e escreve uma imagem PGM no diretório atual com o nome especificado.
 * @param name: Nome do arquivo a ser criado.
 * @param image: Ponteiro para a estrutura Image contendo a imagem a ser salva.
 * @return Retorna 1 em caso de sucesso e 0 em caso de falha.
 */
int image_write(const char* name, Image* image);

/**
 * Desaloca a memória associada à imagem.
 * @param image: Ponteiro para a estrutura Image cuja memória será liberada.
 */
void image_destroy(Image* image);

// Rotaciona uma imagem por alpha graus
int image_rotate_by_x_degrees(Image* image, Image* rotated_img,
                                double alpha);

// Aplica o filtro negativo na imagem, retorna em output
int image_negative_filter(Image* input, Image* output);

int image_treshold_filter(Image* input, Image* output);
int image_mean_filter(Image* input, Image* output);
int image_median_filter(Image* input, Image* output, int mask);
#endif // __IMAGE__
