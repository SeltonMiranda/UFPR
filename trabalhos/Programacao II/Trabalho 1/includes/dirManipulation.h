#ifndef __DIR_MANIPULATION__
#define __DIR_MANIPULATION__

#define MAX_NAME_LENGTH 256 // Tamanho máximo do nome de um arquivo
#define MAX_FILES 100 // Quantidade máxima de arquivos numa struct Directory
#define IMAGE_DIR "./imagens/" // Diretório contendo imagens

#include <sys/types.h>

typedef struct Directory {
    char docs[MAX_FILES][MAX_NAME_LENGTH + 1]; // Nomes dos arquivos presentes no diretório
    ssize_t d_count; // Quantidade de arquivos
} Directory;

// Busca por todos os arquivos que terminam com a extensão passada por parâmetro
int dir_get_files_by_ext(Directory* dir, const char* dir_path,
                         const char* ext);

// Troca a extensão de um arquivo
void replace_extension(const char* filename, const char* new_ext);
#endif // __DIR_MANIPULATION__
