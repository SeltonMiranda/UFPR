#include "../includes/image.h"

#include <string.h>
#include <errno.h>
#include <ctype.h>

int image_read(const char* path, Image* image)
{
    char type[3];
    FORMAT_TYPE img_type;

    FILE* input = fopen(path, "rb"); if (input == NULL) return 0;

    // Lê o tipo de pgm
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

// Lê uma imagem em binário
int read_P5_PGM(FILE* input, Image* image)
{
    skip_comments(input);
    fscanf(input, "%u %u", &image->width, &image->height);
    skip_comments(input);
    fscanf(input, "%hhu", &image->maxval);
    image->pixels = malloc(image->width * image->height);
    if (image->pixels == NULL) {
        fprintf(stderr, "ERROR: Could not allocate memory for pixels\n");
        return 0;
    }
    if (fread(image->pixels, sizeof(char),
        image->width * image->height, input) == 0)
    {
        fprintf(stderr, "ERROR: Could not read file %s\n", strerror(errno));
        free(image->pixels);
        return 0;
    }
    // Precisa cortar uma parte da imagem :d
    //image_chop_blank_rows(image);
    return 1;
}

// Lê uma imagem em ascii
int read_P2_PGM(FILE* input, Image* image)
{
    skip_comments(input);
    fscanf(input, "%u %u", &image->width, &image->height);
    skip_comments(input);
    fscanf(input, "%hhu", &image->maxval);
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
    FILE* output = fopen(name, "wb");
    if (output == NULL) {
        fprintf(stderr, "ERROR: Could not open file %s: %s\n",
                name, strerror(errno));
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
            fprintf(stderr, "Sorry, not implemented yet :(\n");
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

int image_rotate_by_x_degrees(Image* image, Image* rotated_img, double alpha)
{
    double sinx = SIND(alpha);
    double cosx = COSD(alpha);

    // Calculamos qual vai ser a nova altura e comprimento
    uint32_t new_width = (uint32_t)(fabs(image->width * cosx) + fabs(image->height * sinx));
    uint32_t new_height = (uint32_t)(fabs(image->height * cosx) + fabs(image->width * sinx));

    rotated_img->pixels = malloc(new_width * new_height);
    if (rotated_img->pixels == NULL) {
        fprintf(stderr, "ERROR Couldn't allocate memory for rotated image\n");
        return 0;
    }

    rotated_img->width = new_width;
    rotated_img->height = new_height;
    rotated_img->maxval = image->maxval;
    rotated_img->type = image->type;

    // Centro da imagem original e rotacionada
    int32_t x_center = image->width / 2;
    int32_t y_center = image->height / 2;
    int32_t new_x_center = rotated_img->width / 2;
    int32_t new_y_center = rotated_img->height / 2;

    for (uint32_t y = 0; y < rotated_img->height; y++) {
        for (uint32_t x = 0; x < rotated_img->width; x++) {
            // Nova origem
            int32_t yt = y - new_y_center;
            int32_t xt = x - new_x_center;

            // Aplicando a matriz de rotação
            int32_t xRotate = lround(xt * cosx + yt * sinx) + x_center;
            int32_t yRotate = lround(-(xt * sinx) + yt * cosx) + y_center;

            if (xRotate >= 0 && xRotate < (int32_t)image->width &&
                yRotate >= 0 && yRotate < (int32_t)image->height)
            {
                rotated_img->pixels[y*rotated_img->width + x] = image->pixels[yRotate*image->width + xRotate]; 
            } else {
                rotated_img->pixels[y*rotated_img->width + x] = image->maxval; 
            }
        }
    }
    return 1;
}
