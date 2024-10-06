#include "../includes/localBinaryPatterns.h"
#include "../includes/directoryHandler.h"

#include <getopt.h>
#include <string.h>

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
        if (!dir_get_files_by_ext(&dir, dir_path, ".pgm"))
            return 1;

        // Verifica se a imagem passada como argumento existe
        if (!image_exists(&dir, img_path))
            return 1;

        size_t index;
        float min_dist;

        char img_LBP_name[MAX_NAME_LEN];
        char img_LBP_full_path[MAX_PATH_LEN];
        float hist_from_img_arg[MAX_PATTERNS];

        strncpy(img_LBP_name, img_path, MAX_NAME_LEN);
        replace_extension(img_LBP_name, ".lbp"); // input.pgm ---> input.lbp

        // Verifica se o .lbp da imagem passada como argumento
        // está presente no diretório, se não estiver cria-o
        if (!is_lbp_in_dir(dir_path, img_LBP_name)) {
            char img_full_path[MAX_PATH_LEN];
            snprintf(img_full_path, MAX_PATH_LEN, "%s/%s", dir.dir_name, img_path);
            process_image(img_full_path);
        } 

        // Carrega na memória o histograma da imagem passada como argumento
        snprintf(img_LBP_full_path, MAX_PATH_LEN, "%s/%s",
                dir.dir_name, img_LBP_name);
        LBP_read_histogram(hist_from_img_arg, img_LBP_full_path);

        min_dist = find_most_similar_image(&dir, img_path, hist_from_img_arg, &index);
        printf("Imagem mais similar: %s %.6f\n", dir.docs[index], min_dist);
    }

    return 0;
}
