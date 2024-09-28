#ifndef __DIR_MANIPULATION__
#define __DIR_MANIPULATION__

#define MAX_NAME_LENGTH 256 // Tamanho máximo do nome de um arquivo
#define MAX_FILES 100 // Quantidade máxima de arquivos numa struct Directory

#include <sys/types.h>

// Nos ambientes GNU/linux o tamanho máximo de um caminho é 1024,
// porém nesse trabalho não passará disso, portanto usarei metade
#define MAX_PATH_LEN 512
// Nos ambientes GNU/Linux o tamanho máximo de nome de um arquivo é 256
#define MAX_NAME_LEN 256

typedef struct Directory {
    char docs[MAX_FILES][MAX_NAME_LENGTH]; // Nomes dos arquivos presentes no diretório
    size_t d_count; // Quantidade de arquivos
    char dir_name[MAX_NAME_LENGTH]; // Nome do diretório 
} Directory;

// Busca por todos os arquivos que terminam com a extensão passada por parâmetro
int dir_get_files_by_ext(Directory* dir, const char* dir_path,
                         const char* ext);

// Troca a extensão de um arquivo
void replace_extension(const char* filename, const char* new_ext);
#endif // __DIR_MANIPULATION__
