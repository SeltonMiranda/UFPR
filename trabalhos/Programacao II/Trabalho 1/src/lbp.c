#include "../includes/localBinaryPatterns.h"

#include <getopt.h>
#include <string.h>

void printHelp()
{
    fprintf(stderr, "Not enough arguments\n\
USAGE: ./LBP -d <directory> -i <image>\n\
OR: ./LBP -i <input_image> -o <output_image>\n");
}

int main(int argc, char** argv)
{
    int i_flag = 0, d_flag = 0;
    int opt;
    Image image; 
    Directory dir;
    char *dir_path = NULL;
    char *img_path = NULL;

    while ((opt = getopt(argc, argv, "d:i:o:")) != -1) {
        switch(opt) {
            case 'i':
                img_path = optarg;
                i_flag = 1;
                break;

            case 'd':
                dir_path = optarg;
                d_flag = 1;
                break;

            case 'o':
                if (!i_flag) {
                    printHelp();
                    return EXIT_FAILURE;
                }

                char *new_img_path = optarg;
                Image LBP;

                image_read(img_path, &image);
                LBP_apply(&LBP, &image);
                image_write(new_img_path, &LBP);

                image_destroy(&LBP);
                image_destroy(&image);
                return 0;

            default:
                printHelp();
                return EXIT_FAILURE;
        }
    }

    if (i_flag && d_flag) {
        if (!dir_get_files_by_ext(&dir, dir_path, ".pgm"))
            return EXIT_FAILURE;

        size_t index;
        float min_dist;
        float hist_from_arg[MAX_PATTERNS];
        char lbp_path[MAX_NAME_LEN];

        strncpy(lbp_path, img_path, MAX_NAME_LEN);
        replace_extension(lbp_path, ".lbp");
        // Tenta ler o histograma primeiro
        if (!LBP_read_histogram(hist_from_arg, lbp_path)) {
            // Se falhou, cria o histograma
            if (!process_image(img_path))
                return EXIT_FAILURE;
            LBP_read_histogram(hist_from_arg, lbp_path);
        }

        // Encontra a imagem mais similar
        min_dist = find_similar_image(&dir, img_path, hist_from_arg, &index);
        printf("Imagem mais similar: %s %.6f\n", dir.docs[index], min_dist);
    } else {
        printHelp();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
