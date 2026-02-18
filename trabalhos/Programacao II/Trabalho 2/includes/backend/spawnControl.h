#ifndef __SPAWN_CONTROL__
#define __SPAWN_CONTROL__

#include <time.h>

#include "enemies.h"

typedef struct {
  time_t last_spawn_time;  // tempo do ultimo spawn
  int total;               // total de inimigos
  int interval;            // intervalo de spawn
  int spawned;             // contador de inimigos já spawnados
  int batch_size;          // quantidade por spawn
  Enemy *enemies;
} SpawnControl;

SpawnControl *create_spawn_control(ENEMY_TYPE type, int quantity);

void update_spawn_control(SpawnControl *_SpawnControl);

void destroy_spawn_control(SpawnControl *control);

#endif  // __SPAWN_CONTROL__