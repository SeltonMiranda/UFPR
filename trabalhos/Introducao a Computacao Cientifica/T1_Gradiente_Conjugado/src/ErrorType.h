#ifndef __ERROR_TYPE__
#define __ERROR_TYPE__

#define COLOR_YELLOW "\x1b[33m"
#define COLOR_RESET  "\x1b[0m"

typedef enum {
  OK                             = 0,
  ERROR_MEMORY_ALLOCATION_FAILED = 1,
  ERROR_INVALID_MATRIX_SIZE      = 2,
  ERROR_ARRAY_OUT_OF_BOUNDS      = 3,
  ERROR_INVALID_DIMENSION        = 4,
  ERROR_INVALID_K                = 5
} ErrorType;

static inline char* getErrorMessage(ErrorType code) {
    switch (code) {
        case ERROR_MEMORY_ALLOCATION_FAILED:
            return "Falha na alocação de memória.";
        case ERROR_INVALID_MATRIX_SIZE:
            return "Tamanho de k ou n deve ser maior que zero.";
        case ERROR_ARRAY_OUT_OF_BOUNDS:
            return "Erro: indíce está fora dos limites";
        case ERROR_INVALID_DIMENSION:
            return "Dimensão do sistema linear inválida, deve ser maior que 10";
        case ERROR_INVALID_K:
            return "Número de diagonais inválido, deve ser maior que 1 e ímpar";
        default:
            return "Erro desconhecido.";
    }
}

#define HANDLE_ERROR(code) do { \
    fprintf(stderr, COLOR_YELLOW "ERRO em %s:%d\n", __FILE__, __LINE__); \
    fprintf(stderr, "-> Mensagem: %s" COLOR_RESET "\n", getErrorMessage(code)); \
} while (0)



#endif // __ERROR_TYPE__