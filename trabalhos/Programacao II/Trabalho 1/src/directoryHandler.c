#include "../includes/directoryHandler.h"

#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

int dir_get_files(Directory* dir, const char* name)
{
    DIR* _dir;
    struct dirent* file;

    _dir = opendir(name);
    if (_dir == NULL) {
        fprintf(stderr, "ERROR: Couldn't open directory %s: %s\n",
                name, strerror(errno));
        return 0;
    }
    strncpy(dir->dir_name, name, MAX_NAME_LENGTH);
    dir->d_count = 0;
    file = readdir(_dir);
    while (file != NULL) {
        if (dir->d_count >= MAX_FILES)
            break;

        strncpy(dir->docs[dir->d_count], file->d_name, MAX_NAME_LENGTH);
        dir->d_count++;
        file = readdir(_dir);
    }
    closedir(_dir);
    if (dir->d_count == 0) {
        fprintf(stderr, "Directory %s is empty\n", name);
        return 0;
    }
    return 1;
}

int dir_get_files_by_ext(Directory* dir, const char* dirName, const char* ext)
{
    DIR* _dir;
    struct dirent* file;

    _dir = opendir(dirName);
    if (_dir == NULL) {
        fprintf(stderr, "ERROR: Could not open directory %s: %s\n",
                dirName, strerror(errno));
        return 0;
    }

    strncpy(dir->dir_name, dirName, MAX_NAME_LENGTH);
    dir->d_count = 0;
    file = readdir(_dir);
    while (file != NULL) {
        // Verifica se o nome do arquivo possui a extensão do parâmetro
        if (strstr(file->d_name, ext)) {
            if (dir->d_count >= MAX_FILES) // Verifica se atingiu a qntd máxima de arquivos na struct
                break;

            strncpy(dir->docs[dir->d_count], file->d_name, MAX_NAME_LENGTH);
            dir->d_count++;
        }
        file = readdir(_dir);
    }
    closedir(_dir);
    if (dir->d_count == 0) {
        return 0;
    }

    return 1;
}

/* Sabendo que a extensão da imagem ".pgm" tem o mesmo tamanho da nova
   extensão ".lbp" especificado no trabalho, fiz de maneira que não
   alocasse memória para uma nova string (senão teria que ficar lidando
   com free() para cada nome diferente de imagem :((().
   Apesar de ser mais inflexível, há possibilidade de mudar a qualquer momento. */
void replace_extension(const char* filename, const char* new_ext)
{
    char *ext = strrchr(filename, '.'); // Encontra o último ponto
    if (ext == NULL) {
        fprintf(stderr, "File without extension\n");
    } else {
        strcpy(ext, new_ext);
    }
}

int image_exists(Directory* dir, const char* img_name)
{
    for (size_t i = 0; i < dir->d_count; i++) {
        if (strcmp(img_name, dir->docs[i]) == 0)
            return 1;
    }

    fprintf(stderr, "ERROR: Image %s does not exists in %s\n",
            img_name, dir->dir_name);
    return 0;
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
    closedir(_dir);
    return 0;
}
