#include "../includes/localBinaryPatterns.h"

#include <string.h>
#include <errno.h>
#include <math.h>

static void copy_image_attributes_2_LBP(Image* LBP, Image* image)
{
    LBP->width = image->width;
    LBP->height = image->height;
    LBP->maxval = image->maxval;
    LBP->type = image->type;
}

int LBP_apply(Image* LBP, Image* image)
{
    // Inicializa os pixels da imagem LBP com zeros
    LBP->pixels = calloc(image->width * image->height, sizeof(uint8_t));
    if (LBP->pixels == NULL) {
        fprintf(stderr, "ERROR: Couldn't allocate memory for LBP pixels\n");
        return 0;
    } 
    copy_image_attributes_2_LBP(LBP, image);

    /**
     * Aplica o LBP em sentido horário a partir do pixel (p0..7)
     * superior esquerdo em relação ao pixel central (C)
     * ------->
     * p7 p6 p5 |
     * p0 C  p4 |
     * p1 p2 p3 v
     **/
    for (uint32_t y = 1; y < image->height - 1; y++) { 
        for (uint32_t x = 1; x < image->width - 1; x++) {
            uint8_t center = image->pixels[y * (image->width) + x];
            uint8_t pattern = 0; 
            // Zeros estão explícitos para melhorar a visualização do código
            pattern |= (image->pixels[(y - 1) * (image->width) + (x - 1)] > center) << 7;
            pattern |= (image->pixels[(y - 1) * (image->width) + (x - 0)] > center) << 6;
            pattern |= (image->pixels[(y - 1) * (image->width) + (x + 1)] > center) << 5;
            pattern |= (image->pixels[(y - 0) * (image->width) + (x + 1)] > center) << 4;
            pattern |= (image->pixels[(y + 1) * (image->width) + (x + 1)] > center) << 3;
            pattern |= (image->pixels[(y + 1) * (image->width) + (x - 0)] > center) << 2;
            pattern |= (image->pixels[(y + 1) * (image->width) + (x - 1)] > center) << 1;
            pattern |= (image->pixels[(y - 0) * (image->width) + (x - 1)] > center) << 0;
            LBP->pixels[y * (LBP->width) + x] = pattern; // Armazena o valor LBP na imagem LBP
        }
    }
    return 1;
}

void LBP_histogram(float hist[MAX_PATTERNS], Image* LBP)
{
    // Inicializa o histograma com zeros
    for (size_t i = 0; i < MAX_PATTERNS; i++) {
        hist[i] = 0;
    }

    // Itera sobre os pixels da imagem LBP e atualiza o histograma
    for (uint32_t y = 0; y < LBP->height; y++) {
        for (uint32_t x = 0; x < LBP->width; x++) {
            uint8_t class = LBP->pixels[y * (LBP->width) + x];
            hist[class]++;
        }
    }
}

// Função para comparar dois floats
static int compare_floats(const void *a, const void *b)
{
    float float_a = *((float*)a);
    float float_b = *((float*)b);
    return (float_a > float_b) - (float_a < float_b);
}

void LBP_normalize(float hist[MAX_PATTERNS])
{
    float sortedHist[MAX_PATTERNS];
    float high_frequency, low_frequency;

    // Copiando o vetor original para o vetor que será ordenado
    memcpy(sortedHist, hist, MAX_PATTERNS * sizeof(float));
    qsort(sortedHist, MAX_PATTERNS, sizeof(float), compare_floats);
    
    // Pegamos o valor minímo e máximo
    low_frequency = sortedHist[0];    
    high_frequency = sortedHist[MAX_PATTERNS - 1];

    // Normalização dos valores
    for (uint32_t i = 0; i < MAX_PATTERNS; i++) {
        float normValue = (hist[i] - low_frequency) / (high_frequency - low_frequency);
        hist[i] = normValue;
    }
}

int LBP_write_histogram(float hist[MAX_PATTERNS], const char* name)
{
    FILE* output = fopen(name, "wb");  
    if (output == NULL) {
        fprintf(stderr, "ERROR Couldn't open file %s: %s\n",
                name, strerror(errno));
        return 0;
    } 
    fwrite(hist, sizeof(float), MAX_PATTERNS, output);
    if (ferror(output)) {
        fprintf(stderr, "ERROR couldn't write to file %s: %s\n",
                name, strerror(errno));
        fclose(output);
        return 0;
    }
    fclose(output);
    return 1;
}

int LBP_read_histogram(float hist[MAX_PATTERNS], const char* name)
{
    FILE* input = fopen(name, "rb");
    if (input == NULL) {
        fprintf(stderr, "ERROR Couldn't open file %s: %s\n",
                name, strerror(errno));
        return 0;
    } 
    fread(hist, sizeof(float), MAX_PATTERNS, input);
    if (ferror(input)) {
        fprintf(stderr, "ERROR Couldn't read file %s: %s\n",
                name, strerror(errno));
        fclose(input);
        return 0;
    }
    fclose(input);
    return 1;
}

// Algoritmo de kahan para calcular o somatório de floats com maior 
// precisão, ref --> https://en.wikipedia.org/wiki/Kahan_summation_algorithm
static float kahan_sum(float *diffs)
{
    float sum = 0.0;
    float c = 0.0;
    for (size_t i = 0; i < MAX_PATTERNS; i++) {
        float y = diffs[i] - c;
        float t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
    return sum;
}

float LBP_dist(float hist_1[MAX_PATTERNS], float hist_2[MAX_PATTERNS])
{
    float diffs[MAX_PATTERNS];
    for (size_t i = 0; i < MAX_PATTERNS; i++) {
        float diff = hist_1[i] - hist_2[i];
        diffs[i] = diff * diff;
    }

    float summation = kahan_sum(diffs);
    return sqrt(summation);
}
