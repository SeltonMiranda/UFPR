#ifndef __LEVEL__
#define __LEVEL__

#include "boss.h"
#include "explosion.h"
#include "spawnControl.h"

typedef enum LEVEL_PHASE { LEVEL_PHASE_ONE = 0, LEVEL_PHASE_TWO } LEVEL_PHASE;

typedef struct Level {
  SpawnControl *sp1;
  SpawnControl *sp2;
  LEVEL_PHASE phase;
  Explosion *explosion;
  Boss *boss;
} Level;

Level *loadLevel(LEVEL_PHASE phase);

void update_level(Level *l);

void destroy_level(Level *l);

#endif  // __LEVEL__