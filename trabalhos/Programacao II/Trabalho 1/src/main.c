#include "../includes/localBinaryPatterns.h"
#include "../includes/dirManipulation.h"

#include <getopt.h>
#include <string.h>
#include <float.h>

#define PGM_EXT ".pgm"
#define LBP_EXT ".lbp"

void convert_images_2_LBP(Directory* dir)
{
    for (ssize_t i = 0; i <= dir->d_count; i++) {
        Image current_img;
        Image current_LBP_img;
        float histogram[MAX_PATTERNS];

        // Carregando imagem na mémoria e criando o histograma
        image_read(dir->docs[i], &current_img);
        LBP_apply(&current_LBP_img, &current_img);
        LBP_histogram(histogram, &current_LBP_img);
        LBP_normalize(histogram);

        // Escrevendo o histograma num arquivo
        replace_extension(dir->docs[i], LBP_EXT);
        LBP_write_histogram(histogram, dir->docs[i]);
        image_destroy(&current_img);
        image_destroy(&current_LBP_img);
    }
}

int get_distances(Directory* dir, float hist[], const char* img_path, float dist[])
{
    for (ssize_t i = 0; i <= dir->d_count; i++) {
        float hist_2_compare[MAX_PATTERNS];
        float calculated_dist;

        if (strcmp(img_path, dir->docs[i]) == 0) {
            /* Se o nome são iguais, colocamos o maior valor possível de
             * float assim evita que sempre a mesma imagem seja comparada
             */
            dist[i] = FLT_MAX; 
        } else {
            if (!LBP_read_histogram(hist_2_compare, dir->docs[i])) {
                fprintf(stderr, "ERROR: Could not read file %s\n", dir->docs[i]);
                return 0;
            }
            calculated_dist = LBP_dist(hist, hist_2_compare);
            dist[i] = calculated_dist;
        }
    }
    return 1;
}

int is_in_dir(Directory* dir, const char* filename) {
    for (ssize_t i = 0; i <= dir->d_count; i++) {
        if (strcmp(dir->docs[i], filename) == 0)
            return 1;
    }
    return 0;
}

float find_min_value(float* dist, ssize_t len, ssize_t *min_idx)
{
    float min = dist[0];
    *min_idx = 0;
    for (ssize_t i = 1; i < len; i++) {
        if (min > dist[i]) {
            min = dist[i];
            *min_idx = i;
        }
    }
    return min;
}

int main(int argc, char** argv)
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
                    return EXIT_SUCCESS;
                } else {
                    fprintf(stderr, "Argument -i is missing\n");
                    return EXIT_FAILURE;
                }

            default:
                return EXIT_FAILURE;
        }
    }

    if (i_flag && d_flag) {
        // Talvez seja melhor jogar isso fora do if externo
        // assim eu não preciso verificar para .pgm e .lbp
        // ||||
        // vvvv
        if (!dir_get_files_by_ext(&dir, dir_path, LBP_EXT)) {
            dir_get_files_by_ext(&dir, dir_path, PGM_EXT);
            if (!is_in_dir(&dir, img_path)) {
                fprintf(stderr, "ERROR: File %s does not exist\n", img_path);
                return EXIT_FAILURE;
            }
        // ^^^^
        // ||||
            convert_images_2_LBP(&dir);
        }

        float hist[MAX_PATTERNS];
        float dist[dir.d_count];
        ssize_t min_idx;
        float min;

        replace_extension(img_path, LBP_EXT);
        if (!is_in_dir(&dir, img_path)) {
            fprintf(stderr, "ERROR: File %s does not exist\n", img_path);
            return EXIT_FAILURE;
        }
        LBP_read_histogram(hist, img_path);

        if (!get_distances(&dir, hist, img_path, dist))
            return EXIT_FAILURE;

        min = find_min_value(dist, dir.d_count, &min_idx);
        replace_extension(dir.docs[min_idx], PGM_EXT);
        printf("Imagem mais similar: %s %.6f\n", dir.docs[min_idx], min);
    }
    return EXIT_SUCCESS;

}
