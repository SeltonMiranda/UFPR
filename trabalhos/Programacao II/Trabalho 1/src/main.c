#include "../includes/localBinaryPatterns.h"
#include "../includes/dirManipulation.h"

#include <getopt.h>
#include <string.h>
#include <float.h>

/* Converte as imagens presentes no diretório em LBP,
 * criando os histogramas e salvando-os no próprio diretório
 * de entrada
 */
void convert_images_2_LBP(Directory* dir)
{
    for (size_t i = 0; i < dir->d_count; i++) {
        Image current_img;
        Image current_LBP_img;
        float histogram[MAX_PATTERNS];
        char full_path[MAX_PATH_LEN];
        snprintf(full_path, MAX_PATH_LEN, "%s/%s", dir->dir_name, dir->docs[i]);

        // Carregando imagem na mémoria e criando o histograma image_read(full_path, &current_img);
        LBP_apply(&current_LBP_img, &current_img);
        LBP_histogram(histogram, &current_LBP_img);
        LBP_normalize(histogram);

        // Escrevendo o histograma num arquivo
        replace_extension(full_path, ".lbp");
        LBP_write_histogram(histogram, full_path);
        image_destroy(&current_img);
        image_destroy(&current_LBP_img);
    }
}

/* Calcula as distâncias de cada histograma com o histograma da imagem de entrada
 * retorna um vetor de distancias em hist[], retorna 1 em caso de sucesso e 0 em caso de falha
 */
int get_distances(Directory* dir, float hist[], const char* lbp_path, float dist[])
{
    for (size_t i = 0; i < dir->d_count; i++) {
        float hist_2_compare[MAX_PATTERNS];

        if (strcmp(lbp_path, dir->docs[i]) == 0) {
            /* Se o nome são iguais, colocamos o maior valor possível de
             * float assim evita que sempre a mesma imagem seja comparada
             */
            dist[i] = FLT_MAX; 
        } else {
            char full_LBP_path[MAX_PATH_LEN];
            snprintf(full_LBP_path, MAX_PATH_LEN, "%s/%s", dir->dir_name, dir->docs[i]);

            if (!LBP_read_histogram(hist_2_compare, full_LBP_path)) {
                fprintf(stderr, "ERROR: Could not read file %s\n", dir->docs[i]);
                return 0;
            }
            dist[i] = LBP_dist(hist, hist_2_compare);
        }
    }
    return 1;
}

/*
 * Verifica se o arquivo está presente no diretório
 * retorna 1 caso esteja presente e 0 caso contrário
 */
int is_in_dir(Directory* dir, const char* filename) {
    for (size_t i = 0; i < dir->d_count; i++) {
        if (strcmp(dir->docs[i], filename) == 0)
            return 1;
    }
    return 0;
}

/*
 * Encontra a menor distância presente no vetor de distâncias,
 * retorna o valor da menor distância e o indíce da mesma, no parâmetro
 */
float find_min_value(float* dist, size_t len, size_t *min_idx)
{
    float min = dist[0];
    *min_idx = 0;
    for (size_t i = 1; i < len; i++) {
        if (min > dist[i]) {
            min = dist[i];
            *min_idx = i;
        }
    }
    return min;
}

int main() 
{
    Image input;
    Image output;
    image_read("lena.pgm", &input);
    image_rotate_by_x_degrees(&input, &output, 90.0);
    image_write("lena-rotate.pgm", &output);
    return 0;
}

int main2(int argc, char** argv)
{
    if (argc < 3) {
        fprintf(stderr, "ERROR: Not enough arguments\n");
        return EXIT_FAILURE;
    }

    int i_flag = 0, d_flag = 0;
    int opt;
    Image image; 
    Directory dir;
    char *dir_path = NULL;
    char *img_path = NULL;

    while ((opt = getopt(argc, argv, "d:i:o:h:")) != -1) {
        switch(opt) {
            case 'd':
                dir_path = optarg;
                d_flag = 1;
                break;

            case 'i':
                img_path = optarg;
                i_flag = 1;
                break;

            case 'o':
                if (i_flag) {
                    char *new_img_path = optarg;
                    Image LBP;

                    image_read(img_path, &image);
                    LBP_apply(&LBP, &image);
                    image_write(new_img_path, &LBP);

                    image_destroy(&LBP);
                    image_destroy(&image);
                    return 0;
                } else {
                    fprintf(stderr, "Argument -i is missing\n");
                    return 1;
                }
            default:
                return 1;
        }
    }

    if (i_flag && d_flag) {
        if (!dir_get_files_by_ext(&dir, dir_path, ".lbp")) {
            dir_get_files_by_ext(&dir, dir_path, ".pgm");
            if (!is_in_dir(&dir, img_path)) {
                fprintf(stderr, "ERROR: File %s does not exist\n", img_path);
                fprintf(stderr, "img_path: %s\n", img_path);
                return 1;
            }
            convert_images_2_LBP(&dir);
        }
        dir_get_files_by_ext(&dir, dir_path, ".lbp");

        char img_LBP_path[MAX_NAME_LEN];
        char full_LBP_path[MAX_PATH_LEN];
        float hist[MAX_PATTERNS];
        float dist[dir.d_count];
        size_t min_idx;
        float min;

        strncpy(img_LBP_path, img_path, MAX_NAME_LEN);
        replace_extension(img_LBP_path, ".lbp");

        // Note que o conteúdo do diretório sao os arquivos ".lbp"
        if (!is_in_dir(&dir, img_LBP_path)) {
            fprintf(stderr, "ERROR: File %s does not exist\n", img_LBP_path);
            return 1;
        }

        snprintf(full_LBP_path, MAX_PATH_LEN, "%s/%s", dir.dir_name, img_LBP_path);
        LBP_read_histogram(hist, full_LBP_path);
        if (!get_distances(&dir, hist, img_LBP_path, dist))
            return 1;

        min = find_min_value(dist, dir.d_count, &min_idx);
        replace_extension(dir.docs[min_idx], ".pgm");
        printf("Imagem mais similar: %s %.6f\n", dir.docs[min_idx], min);
    }
    return 0;
}
