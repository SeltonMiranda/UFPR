#ifndef __GUN__
#define __GUN__

#include "../../includes/config/config.h"
#include "shot.h"

typedef enum {
  PLAYER,
  ENEMY,
} Gun_Source;

typedef struct Gun {
  int timer;
  Shot shots[MAX_SHOTS];
  Gun_Source _source;
} Gun;

Gun *create_gun(Gun_Source source);

void gun_shot(Gun *_gun, float x, float y);

void update_gun(Gun *_gun, int isPlayer);

void destroy_gun(Gun *gun);
#endif  // __GUN__