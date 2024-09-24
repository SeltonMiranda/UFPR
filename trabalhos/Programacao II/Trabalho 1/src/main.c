#include "../includes/localBinaryPatterns.h"
#include "../includes/dirManipulation.h"

#include <getopt.h>
#include <string.h>
#include <float.h>

#define PGM_EXT ".pgm"
#define LBP_EXT ".lbp"

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
        if (!dir_get_files_by_ext(&dir, dir_path, LBP_EXT)) {
            dir_get_files_by_ext(&dir, dir_path, PGM_EXT);
            for (ssize_t i = 0; i <= dir.d_count; i++) {
                Image current_img;
                Image current_LBP_img;
                float histogram[MAX_PATTERNS];

                image_read(dir.docs[i], &current_img);
                LBP_apply(&current_LBP_img, &current_img);
                LBP_histogram(histogram, &current_LBP_img);
                LBP_normalize(histogram);
                replace_extension(dir.docs[i], LBP_EXT);
                LBP_write_histogram(histogram, dir.docs[i]);
                image_destroy(&current_img);
                image_destroy(&current_LBP_img);
            }
        }

        float hist[MAX_PATTERNS];
        float dist[dir.d_count];
        replace_extension(img_path, LBP_EXT);
        LBP_read_histogram(hist, img_path);

        for (ssize_t i = 0; i <= dir.d_count; i++) {
            float hist_2_compare[MAX_PATTERNS];
            float calculated_dist;

            if (strcmp(img_path, dir.docs[i]) == 0) {
                dist[i] = FLT_MAX;
            } else {
                LBP_read_histogram(hist_2_compare, dir.docs[i]);
                calculated_dist = LBP_dist(hist, hist_2_compare);
                dist[i] = calculated_dist;
            }

        } 

        float min = dist[0];
        ssize_t min_idx = 0;
        for (ssize_t i = 1; i < dir.d_count; i++) {
            if (min > dist[i]) {
                min = dist[i];
                min_idx = i;
            }
        }
        replace_extension(dir.docs[min_idx], PGM_EXT);
        printf("Imagem mais similar: %s %.6f\n", dir.docs[min_idx], min);
    }
    return EXIT_SUCCESS;
}
