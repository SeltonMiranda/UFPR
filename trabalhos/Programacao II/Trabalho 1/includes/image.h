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
    P2 = 0,
    P5 = 1
} FORMAT_TYPE;

typedef struct Image {
    FORMAT_TYPE type; // Formato da imagem
    uint32_t width; // Comprimento da imagem
    uint32_t height; // Altura da imagem
    uint8_t* pixels; // Vetor de pixels
    uint8_t maxval; // Valor máximo que o pixel pode assumir
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

// Rotaciona uma imagem por alpha graus
int image_rotate_by_x_degrees(Image* image, Image* rotated_img,
                                double alpha);

// Aplica o filtro negativo na imagem, retorna em output
int image_negative_filter(Image* input, Image* output);

int image_treshold_filter(Image* input, Image* output);
int image_mean_filter(Image* input, Image* output);
int image_median_filter(Image* input, Image* output, int mask);
#endif // __IMAGE__
