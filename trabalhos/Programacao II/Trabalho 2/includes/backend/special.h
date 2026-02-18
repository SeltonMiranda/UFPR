#ifndef __SPECIAL_ATTACK__
#define __SPECIAL_ATTACK__

#include <time.h>

#include "gun.h"

typedef enum SPECIAL_TYPE { SPECIAL_GUN_ONE = 0, SPECIAL_GUN_TWO } SPECIAL_TYPE;

typedef struct Special {
  int is_active;
  float x, y;
  time_t spawn_time;
  int on_map;

  int damage;
  SPECIAL_TYPE type;
  time_t burst_time;
  Gun *gun;
} Special;

Special *init_special();

void spawn_special_attack(Special *sp);

void update_special_attack(Special *sp);

void destroy_special_attack(Special *sp);

#endif  // __SPECIAL_ATTACK__