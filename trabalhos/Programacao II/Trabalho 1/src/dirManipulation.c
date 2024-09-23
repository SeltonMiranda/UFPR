#include "../includes/dirManipulation.h"

#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int dir_get_files_by_ext(Directory* dir, const char* dir_path,
        const char* ext)
{
    DIR* _dir;
    struct dirent* entry;

    _dir = opendir(dir_path);
    if (_dir == NULL) return 0;

    dir->d_count = -1;
    entry = readdir(_dir);
    while (entry != NULL) {
        if (strstr(entry->d_name, ext)) {
            if (dir->d_count >= MAX_FILES) break;
            char full_path[MAX_NAME_LENGTH + 1];

            snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);
            dir->d_count++;
            strncpy(dir->docs[dir->d_count], full_path, MAX_NAME_LENGTH);
            dir->docs[dir->d_count][MAX_NAME_LENGTH - 1] = '\0';
        }
        entry = readdir(_dir);
    }
    closedir(_dir);
    if (dir->d_count < 0) return 0;
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
