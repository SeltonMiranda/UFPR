#include "../includes/image.h"

#include <string.h>
#include <errno.h>
#include <ctype.h>

int image_read(const char* path, Image* image)
{
    char type[3];
    FORMAT_TYPE img_type;

    FILE* input = fopen(path, "rb");
    if (input == NULL) return 0;

    // Lê o tipo de pgm
    fscanf(input, "%2s", type);
    if (strcmp(type, "P2") == 0) {
        img_type = P2;
    } else if (strcmp(type, "P5") == 0) {
        img_type = P5;
    } else {
        fclose(input);
        return 0;
    }

    // Como os desenvolvedores do kernel do linux fazem
    int ret = 0;
    image->type = img_type;
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

static void skip_comments(FILE* input)
{
    int c;
    while ((c = fgetc(input)) != EOF) {
        if (c == '#') {
            while ((c = fgetc(input)) != EOF && c != '\n');
        } else if (!isspace(c)) {
            ungetc(c, input);
            break;
        }
    }
}

int read_P5_PGM(FILE* input, Image* image)
{
    skip_comments(input);
    fscanf(input, "%u %u", &image->width, &image->height);
    skip_comments(input);
    fscanf(input, "%hhu", &image->maxval);
    skip_comments(input);
    image->pixels = malloc(image->width * image->height);
    if (image->pixels == NULL) {
        return 0;
    }

    if (fread(image->pixels, sizeof(char),
        image->width * image->height, input) == 0)
    {
        free(image->pixels);
        return 0;
    }
    return 1;
}

int read_P2_PGM(FILE* input, Image* image)
{
    skip_comments(input);
    fscanf(input, "%u %u", &image->width, &image->height);
    skip_comments(input);
    fscanf(input, "%hhu", &image->maxval);
    skip_comments(input);
    image->pixels = malloc(image->width * image->height);
    if (image->pixels == NULL) return 0;

    for (uint32_t i = 0; i < image->width * image->height; i++) {
        uint8_t c;
        if (fscanf(input, "%hhu", &c) != 1) {
            free(image->pixels);
            return 0;
        } else {
            image->pixels[i] = c;
        }
    }
    return 1;
}

int image_write(const char* name, Image* image)
{
    FILE* output = fopen(name, "wb");
    if (output == NULL) {
        return 0; 
    }

    switch(image->type) {
        case P2:
            write_P2_PGM(output, image);
            break;
        case P5:
            write_P5_PGM(output, image);
            break;
        default:
            return 0;
    }
    fclose(output);
    return 1;
}

// Escreve uma imagem em ascii
void write_P2_PGM(FILE* output, Image* image)
{
    fprintf(output, "P2\n%u %u\n%hhu\n",
            image->width, image->height, image->maxval);
    for (uint32_t y = 0; y < image->height; y++) {
        for (uint32_t x = 0; x < image->width; x++) {
            fprintf(output, "%hhu", image->pixels[y * (image->width) + x]);

            if (x < image->width - 1)
                fprintf(output, " ");
        }
        if (y < image->height -1) {
            fprintf(output, "\n");
        }
    }
}

// Escreve uma imagem em binário
void write_P5_PGM(FILE* output, Image* image)
{
    fprintf(output, "P5\n%u %u\n%hhu\n",
            image->width, image->height, image->maxval);
    fwrite(image->pixels, 1, image->width * image->height, output);
}

void image_destroy(Image* image)
{
    free(image->pixels);
}
