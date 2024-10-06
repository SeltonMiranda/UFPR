#include "../includes/localBinaryPatterns.h"

#include <string.h>
#include <errno.h>
#include <math.h>
#include <float.h>

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
            if (y != 0 && y != LBP->height - 1) {
                if (x != 0 && x != LBP->width - 1) {
                    uint8_t class = LBP->pixels[y * (LBP->width) + x];
                    hist[class]++;
                }
            }
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

int process_image(const char* filepath)
{
    Image current_img;
    Image current_LBP_img;
    float histogram[MAX_PATTERNS];

    if(!image_read(filepath, &current_img)) {
        return 0;
    }

    LBP_apply(&current_LBP_img, &current_img);
    LBP_histogram(histogram, &current_LBP_img);
    LBP_normalize(histogram);

    replace_extension(filepath, ".lbp");
    LBP_write_histogram(histogram, filepath);
    image_destroy(&current_img);
    image_destroy(&current_LBP_img);
    return 1;
}

float find_most_similar_image(Directory* dir, const char* img_path, float hist_from_img_arg[MAX_PATTERNS], size_t* index)
{
    float min_dist = FLT_MAX;
    for (size_t i = 0; i < dir->d_count; i++) {
        if (strcmp(dir->docs[i], img_path) == 0) 
            continue;

        char img_dir_LBP_name[MAX_NAME_LEN];
        char img_dir_LBP_full_path[MAX_PATH_LEN];

        float hist_from_dir[MAX_PATTERNS];
        float dist;

        // Pega a imagem dentro do diretório e renomeia-a como .lbp
        strncpy(img_dir_LBP_name, dir->docs[i], MAX_NAME_LEN);
        replace_extension(img_dir_LBP_name, ".lbp");

        // Verifica se o .lbp da imagem está presente no diretório,
        // caso contrário, cria-o
        if (!is_lbp_in_dir(dir->dir_name, img_dir_LBP_name)) {
            char img_full_path[MAX_PATH_LEN];
            snprintf(img_full_path, MAX_PATH_LEN, "%s/%s",
                    dir->dir_name, dir->docs[i]);
            if (!process_image(img_full_path)) {
                continue;
            }
        } 

        snprintf(img_dir_LBP_full_path, MAX_PATH_LEN, "%s/%s",
                dir->dir_name, img_dir_LBP_name);
        LBP_read_histogram(hist_from_dir, img_dir_LBP_full_path);

        dist = LBP_dist(hist_from_img_arg, hist_from_dir);
        if (dist < min_dist) {
            min_dist = dist;
            *index = i;
        }
    }
    return min_dist;
}
