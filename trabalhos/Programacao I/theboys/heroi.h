#ifndef HEROI_H
#define HEROI_H

#include "conjunto.h"

struct Heroi {
        int id;
        struct conjunto *habilidades;
        int paciencia;
        int vel;
        int exp;
        int base;
};

#endif 
