#ifndef BASE_H
#define BASE_H

#include "conjunto.h"
#include "fila.h"

struct Base {
        int id;
        int pos_x;
        int pos_y;
        int max_herois;
        struct fila *fila_espera_herois;
        struct conjunto *herois_presentes;
};

#endif
