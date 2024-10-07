#include "../includes/localBinaryPatterns.h"

#include <getopt.h>

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

        // Verifica se a imagem passada como argumento existe
        if (!image_exists(&dir, img_path))
            return EXIT_FAILURE;

        size_t index;
        float min_dist;
        float hist_from_img_arg[MAX_PATTERNS];

        load_img_lbp_from_arg(img_path, dir.dir_name, hist_from_img_arg);
        min_dist = find_most_similar_image(&dir, img_path, hist_from_img_arg, &index);
        printf("Imagem mais similar: %s %.6f\n", dir.docs[index], min_dist);
    } else {
        printHelp();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
