#include "../includes/localBinaryPatterns.h"

#include <string.h>
#include <math.h>

int LBP_apply(Image* LBP, Image* image)
{
    LBP->pixels = calloc(image->width * image->height, sizeof(char));
    if (LBP->pixels == NULL) return 0;
    LBP->width = image->width;
    LBP->height = image->height;
    LBP->maxval = image->maxval;
    LBP->type = image->type;

    // Aplica o LBP em sentido horário a partir do pixel superior esquerdo
    // em relação ao pixel central
    for (uint32_t y = 1; y < image->height - 1; y++) { 
        for (uint32_t x = 1; x < image->width - 1; x++) {
            unsigned char center = image->pixels[y * (image->width) + x];
            unsigned char code = 0; 
            code |= (image->pixels[(y - 1) * (image->width) + (x - 1)] > center) << 7;
            code |= (image->pixels[(y - 1) * (image->width) + (x - 0)] > center) << 6;
            code |= (image->pixels[(y - 1) * (image->width) + (x + 1)] > center) << 5;
            code |= (image->pixels[(y - 0) * (image->width) + (x + 1)] > center) << 4;
            code |= (image->pixels[(y + 1) * (image->width) + (x + 1)] > center) << 3;
            code |= (image->pixels[(y + 1) * (image->width) + (x - 0)] > center) << 2;
            code |= (image->pixels[(y + 1) * (image->width) + (x - 1)] > center) << 1;
            code |= (image->pixels[(y - 0) * (image->width) + (x - 1)] > center) << 0;
            // Armazena o valor LBP na imagem LBP
            LBP->pixels[y * (LBP->width) + x] = code;
        }
    }
    return 1;
}

void LBP_histogram(float hist[MAX_PATTERNS], Image* LBP)
{
    if (LBP == NULL) return;

    for (size_t i = 0; i < MAX_PATTERNS; i++) {
        hist[i] = 0;
    }
    //memset(hist, 0, MAX_PATTERNS * sizeof(float));

    // Itera sobre os pixels e atualiza o histograma
    for (uint32_t y = 0; y < LBP->height; y++) {
        for (uint32_t x = 0; x < LBP->width; x++) {
            unsigned char class = LBP->pixels[y * (LBP->width) + x];
            hist[class]++;
        }
    }
}

static int compare_floats(const void *a, const void *b)
{
    float float_a = *((float*)a);
    float float_b = *((float*)b);
    return (float_a > float_b) - (float_a < float_b);
}

void LBP_normalize(float hist[MAX_PATTERNS])
{
    float sortedHist[MAX_PATTERNS]; // Array para armazenar a cópia do histograma
    float high_frequency, low_frequency;

    memcpy(sortedHist, hist, MAX_PATTERNS * sizeof(float));
    qsort(sortedHist, MAX_PATTERNS, sizeof(float), compare_floats);
    
    // Pega o valor minímo e máximo
    low_frequency = sortedHist[0];    
    high_frequency = sortedHist[MAX_PATTERNS - 1];

    for (uint32_t i = 0; i < MAX_PATTERNS; i++) {
        float normValue = (hist[i] - low_frequency) / (high_frequency - low_frequency);
        hist[i] = normValue;
    }
}

int LBP_write_histogram(float hist[MAX_PATTERNS], const char* name)
{
    FILE* output = fopen(name, "wb");  
    if (output == NULL) return 0;

    if (fwrite(hist, sizeof(float), MAX_PATTERNS, output) == 0) {
        fclose(output);
        return 0;
    }
    fclose(output);
    return 1;
}

int LBP_read_histogram(float hist[MAX_PATTERNS], const char* name)
{
    FILE* input = fopen(name, "rb");
    if (input == NULL) return 0;
    
    if (fread(hist, sizeof(float), MAX_PATTERNS, input) == 0) {
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
        float diff = hist_1[i] - hist_2[i]; // Diferença entre dois floats
        diffs[i] = diff * diff; // diff^2
    }

    float summation = kahan_sum(diffs);
    return sqrt(summation);
}
