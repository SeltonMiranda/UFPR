#ifndef __IMAGE__
#define __IMAGE__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Formato de impressão da struct Image
#define IMG_FMT "%u %u\n%hhu\n"
#define IMG_ARGS(img) (img)->width, (img)->height, (img)->maxval
// Uso:
// fprintf/printf("something:"IMG_FMT, IMG_ARGS(image));
// --> A linguagem C concatena strings "s1""s2" no printf/fprintf

typedef enum {
    P2 = 0,
    P5 = 1
} PGM_TYPE;

typedef struct Image {
    PGM_TYPE type; // tipo do PGM
    uint32_t width; // Comprimento da imagem
    uint32_t height; // Altura da imagem
    unsigned char* pixels; // Vetor de pixels
    unsigned char maxval; // Valor máximo que o pixel pode assumir
} Image;

// Retorna 1 em caso de sucesso e 0 em caso de falha
// as informações sobre a imagem são guardadas na **struct Image**
int image_read(const char* path, Image* image);

// Lê uma imagem PGM no format P2
int read_P2_PGM(FILE* input, Image* image);

// Lê uma imagem PGM no format P5
int read_P5_PGM(FILE* input, Image* image);

// Escreve num arquivo uma imagem PGM no formato P2
void write_P2_PGM(FILE* output, Image* image);

// Escreve num arquivo uma imagem PGM no formato P5
void write_P5_PGM(FILE* output, Image* image);

// Recorta as linhas em branco presentes na imagem
// OBS: É necessária essa função, pois as imagens contidas
// no diretório ../imagens/ possuem a escala que foram tiradas
// e isso pode influenciar negativamente o algoritmo LBP
void image_chop_blank_rows(Image* image);

// Cria uma imagem no diretório atual
// retorna 1 em caso de sucesso e 0 em caso de falha
int image_write(const char* name, Image* image);

// Desaloca memória da imagem
void image_destroy(Image* image);

#endif // __IMAGE__