#ifndef __BOSS__
#define __BOSS__

#include <time.h>

#include "shot.h"

typedef enum BOSS_TYPE { LEVEL_ONE_BOSS = 0, LEVEL_TWO_BOSS } BOSS_TYPE;

typedef enum BOSS_STATE {
  BOSS_STATE_NOT_SPAWNED = 0,
  BOSS_STATE_SPAWNED,
  BOSS_STATE_DEAD
} BOSS_STATE;

typedef enum WEAPON_TYPE {
  WEAPON_TYPE_ONE = 0,
  WEAPON_TYPE_TWO,
  WEAPON_TYPE_THREE,
  WEAPON_TYPE_FOUR,
} WEAPON_TYPE;

typedef struct Weapon {
  Shot shots[MAX_SHOTS];
  WEAPON_TYPE type;
  int timer;
  int damage;

  int width;
  int height;
} Weapon;

typedef struct Boss {
  float x, y;
  BOSS_TYPE type;
  BOSS_STATE state;
  Weapon *weapon;

  time_t timer;
  int life;
  int current_frame;
  int direction;  // 1 para cima e -1 para baixo
  int spawned;
} Boss;

Boss *create_boss(BOSS_TYPE type);

Weapon *create_weapon();

int boss_should_spawn(Boss *boss);

void spawn_boss(Boss *boss);

void update_boss(Boss *boss);

void boss_shot(Weapon *w, float x, float y);

void update_boss_shot(Weapon *w);

void destroy_boss(Boss *boss);

#endif  // __BOSS__