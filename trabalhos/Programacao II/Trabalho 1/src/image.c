#include "../includes/image.h"

#include <string.h>

int image_read(const char* path, Image* image)
{
    char type[3];
    PGM_TYPE img_type;

    FILE* input = fopen(path, "rb");
    if (input == NULL) return 0;

    fscanf(input, "%2s", type);
    if (strcmp(type, "P2") == 0) {
        img_type = P2;
    } else if (strcmp(type, "P5") == 0) {
        img_type = P5;
    } else {
        fclose(input);
        fprintf(stderr, "Sorry, not implemented yet :))))\n");
        return 0;
    }

    // Como os desenvolvedores do kernel do linux fazem
    int ret = 0;
    switch(img_type) {
        case P2:
            ret = read_P2_PGM(input, image);
            break;
        case P5:
            ret = read_P5_PGM(input, image);
            break;
    }
    fclose(input);
    return ret;
}

// Lê uma imagem em binário
int read_P5_PGM(FILE* input, Image* image)
{
    image->type = P5;
    fscanf(input, "%u %u", &image->width, &image->height);
    fscanf(input, "%hhu", &image->maxval);
    image->pixels = malloc(image->width * image->height);
    if (image->pixels == NULL) return 0;

    if (fread(image->pixels, sizeof(char),
              image->width * image->height, input) == 0) {
        free(image->pixels);
        return 0;
    }
    image_chop_blank_rows(image);
    return 1;
}

// Lê uma imagem em ascii
int read_P2_PGM(FILE* input, Image* image)
{
    image->type = P2;
    fscanf(input, "%u %u", &image->width, &image->height);
    fscanf(input, "%hhu", &image->maxval);
    image->pixels = malloc(image->width * image->height);
    if (image->pixels == NULL) return 0;

    for (uint32_t i = 0; i < image->width * image->height; i++) {
        unsigned char c;
        if (fscanf(input, "%hhu", &c) != 1) {
            free(image->pixels);
            return 0;
        } else {
            image->pixels[i] = c;
        }
    }
    image_chop_blank_rows(image);
    return 1;
}

void image_chop_blank_rows(Image *image)
{
    uint32_t blank_rows = 0;
    for (uint32_t y = 0; y < image->height; y++) {
        if (image->pixels[y * image->width] == 255) {
            blank_rows++;
        }
    }
    image->height -= (blank_rows + 1); // São 80 linhas em branco
}

int image_write(const char* name, Image* image)
{
    if (name == NULL) return 0;

    FILE* output = fopen(name, "wb");
    if (output == NULL) return 0;

    switch(image->type) {
        case P2:
            write_P2_PGM(output, image);
            break;
        case P5:
            write_P5_PGM(output, image);
            break;
        default:
            fprintf(stderr, "Sorry, not implemented yet:)))))))\n");
            return 0;
    }
    fclose(output);
    return 1;
}

// Escreve uma imagem em ascii
void write_P2_PGM(FILE* output, Image* image)
{
    fprintf(output, "%s\n", "P2");
    fprintf(output, IMG_FMT, IMG_ARGS(image));
    //fprintf(output, "%u\n", image->maxval);
    for (uint32_t y = 0; y < image->height; y++) {
        for (uint32_t x = 0; x < image->width; x++) {
            fprintf(output, "%hhu", image->pixels[y * (image->width) + x]);

            if (x < image->width - 1)
                fprintf(output, " ");
        }
        fprintf(output, "\n");
    }
}

// Escreve uma imagem em binário
void write_P5_PGM(FILE* output, Image* image)
{
    fprintf(output, "%s\n", "P5");
    fprintf(output, IMG_FMT, IMG_ARGS(image));
    //fprintf(output, "%u\n", image->maxval);
    fwrite(image->pixels, 1, image->width * image->height, output);
}

void image_destroy(Image* image)
{
    free(image->pixels);
}
