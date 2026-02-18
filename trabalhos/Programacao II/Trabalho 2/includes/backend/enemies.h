#ifndef __ENEMIES__
#define __ENEMIES__

#include "gun.h"
#include "time.h"

typedef enum { ENEMY_1 = 0, ENEMY_2, ENEMY_3, ENEMY_4 } ENEMY_TYPE;

typedef struct {
  ENEMY_TYPE _type;
  float x, y;
  int life;
  int isAlive;
  Gun *_gun;
} Enemy;

Enemy *create_enemy(ENEMY_TYPE type, int quantity);

void update_enemies(Enemy *enemies, int spawned);

void destroy_enemy(Enemy *enemy_vector, int size);

#endif  // __ENEMIES__