#ifndef HEROI_H
#define HEROI_H

#include "conjunto.h"
struct Heroi {
        int id;
        struct conjunto *hab;
        int paciencia;
        int vel;
        int exp;
        int base;
};
#endif 
