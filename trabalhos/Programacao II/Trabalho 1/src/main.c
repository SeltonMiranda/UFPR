#include "../includes/localBinaryPatterns.h"
#include "../includes/dirManipulation.h"

#include <getopt.h>
#include <string.h>
#include <float.h>
#include <dirent.h>

void create_histogram_from_image(const char* filepath)
{
    Image current_img;
    Image current_LBP_img;
    float histogram[MAX_PATTERNS];

    printf("aqui");
    image_read(filepath, &current_img);
    LBP_apply(&current_LBP_img, &current_img);
    LBP_histogram(histogram, &current_LBP_img);
    LBP_normalize(histogram);

    replace_extension(filepath, ".lbp");
    LBP_write_histogram(histogram, filepath);
    image_destroy(&current_img);
    image_destroy(&current_LBP_img);
}

int is_lbp_in_dir(const char* dir_name, const char* lbp_name)
{
    DIR* _dir;
    struct dirent* file;

    _dir = opendir(dir_name);
    file = readdir(_dir);
    while (file != NULL) {
        if (strstr(file->d_name, ".lbp")) {
            if (strcmp(lbp_name, file->d_name) == 0)
                return 1;
        }
        file = readdir(_dir);
    }
    return 0;
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

        size_t index;
        float min_dist = FLT_MAX;
        for (size_t i = 0; i < dir.d_count; i++) {

            if (strcmp(dir.docs[i], img_path) == 0) 
                continue;

            char img_LBP_name[MAX_NAME_LEN];
            char img_LBP_full_path[MAX_PATH_LEN];

            strncpy(img_LBP_name, img_path, MAX_NAME_LEN);
            replace_extension(img_LBP_name, ".lbp"); // input.pgm ---> input.lbp

            // Verifica se o .lbp está presente no diretório, se não estiver cria-o
            if (!is_lbp_in_dir(dir_path, img_LBP_name)) {
                char img_full_path[MAX_PATH_LEN];
                snprintf(img_full_path, MAX_PATH_LEN, "%s/%s", dir.dir_name, img_path);
                create_histogram_from_image(img_full_path);
            } 

            char img_dir_LBP_name[MAX_NAME_LEN];
            char img_dir_LBP_full_path[MAX_PATH_LEN];

            float hist_from_img_arg[MAX_PATTERNS];
            float hist_from_dir[MAX_PATTERNS];
            float dist;

            // Carrega na memória o histograma da imagem passada como argumento
            snprintf(img_LBP_full_path, MAX_PATH_LEN, "%s/%s", dir.dir_name, img_LBP_name);
            LBP_read_histogram(hist_from_img_arg, img_LBP_full_path);

            // Pega a imagem dentro do diretório e renomeia-a como .lbp
            strncpy(img_dir_LBP_name, dir.docs[i], MAX_NAME_LEN);
            replace_extension(img_dir_LBP_name, ".lbp");

            // Verifica se o .lbp da imagem está presente no diretório,
            // caso contrário, cria-o
            if (!is_lbp_in_dir(dir_path, img_dir_LBP_name)) {
                char img_full_path[MAX_PATH_LEN];
                snprintf(img_full_path, MAX_PATH_LEN, "%s/%s", dir.dir_name, dir.docs[i]);
                create_histogram_from_image(img_full_path);
            } 

            snprintf(img_dir_LBP_full_path, MAX_PATH_LEN, "%s/%s", dir.dir_name, img_dir_LBP_name);
            LBP_read_histogram(hist_from_dir, img_dir_LBP_full_path);

            dist = LBP_dist(hist_from_img_arg, hist_from_dir);
            if (dist < min_dist) {
                min_dist = dist;
                index = i;
            }
        }
        printf("Imagem mais similar: %s %.6f\n", dir.docs[index], min_dist);
    }

    return 0;
}
