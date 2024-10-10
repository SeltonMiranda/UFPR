#ifndef __DIR_MANIPULATION__
#define __DIR_MANIPULATION__

#include <sys/types.h>

#define MAX_FILES 1024 // Quantidade máxima de arquivos na estrutura Directory
#define MAX_LEN 1024

typedef struct Directory {
    char docs[MAX_FILES][MAX_LEN]; // Armazena os nomes dos arquivos presentes no diretório
    char dir_name[MAX_LEN];        // Nome do diretório
    size_t d_count;                // Contador para a quantidade de arquivos no diretório
} Directory;

/**
 * Busca arquivos em um diretório específico com a extensão fornecida.
 * @param dir: Ponteiro para a estrutura Directory onde os arquivos serão armazenados.
 * @param dirName: Nome do diretório a ser lido.
 * @param ext: Extensão dos arquivos a serem buscados.
 * @return Retorna 1 em caso de sucesso e 0 em caso de falha.
 */
int dir_get_files_by_ext(Directory* dir, const char* dirName, const char* ext);

/**
 * Troca a extensão de um arquivo pelo novo formato especificado.
 * @param filename: Nome do arquivo original.
 * @param new_ext: Nova extensão a ser aplicada ao arquivo.
 */
void replace_extension(const char* filename, const char* new_ext);

/**
 * Verifica se um arquivo de características LBP específico está presente em um diretório.
 * @param dir_name: Nome do diretório onde a verificação será realizada.
 * @param lbp_name: Nome do arquivo LBP a ser procurado.
 * @return Retorna 1 se o arquivo LBP existir no diretório e 0 caso contrário.
 */
int is_lbp_in_dir(const char* dir_name, const char* lbp_name);

#endif // __DIR_MANIPULATION__
