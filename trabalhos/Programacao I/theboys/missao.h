#ifndef MISSAO_H
#define MISSAO_H

#include "conjunto.h"

struct Missao {
        int id;
        int pos_x;
        int pos_y;
        int cumprida;
        int tentativa;
        struct conjunto *hab_requeridas;
};

#endif
