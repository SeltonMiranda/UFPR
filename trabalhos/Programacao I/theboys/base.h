#ifndef BASE_H
#define BASE_H

#include "conjunto.h"
#include "fila.h"

struct Base {
        int id;
        int pos_x;
        int pos_y;
        int nHerois;
        struct fila *fHerois;
        struct conjunto *hPresentes;
};

#endif
