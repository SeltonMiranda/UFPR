#include "../../includes/backend/explosion.h"

#include <stdlib.h>

#include "../../includes/utils/utils.h"

Explosion *init_explosions() {
  Explosion *exp = (Explosion *)malloc(sizeof(Explosion) * MAX_EXPLOSIONS);
  must_init(exp, "Explosion");

  for (int i = 0; i < MAX_EXPLOSIONS; i++) {
    exp[i].is_active = 0;
    exp[i].frame = 0;
  }

  return exp;
}

void spawn_explosion(Explosion *e, float x, float y) {
  for (int i = 0; i < MAX_EXPLOSIONS; i++) {
    if (e[i].is_active)
      continue;

    e[i].x = x;
    e[i].y = y;
    e[i].is_active = 1;
    e[i].timer = 10;
  }
}

void update_explosions(Explosion *explosions) {
  for (int i = 0; i < MAX_EXPLOSIONS; i++) {
    if (!explosions[i].is_active)
      continue;

    explosions[i].timer--;
    if (explosions[i].timer <= 0) {
      explosions[i].is_active = 0;
    }
  }
}

void destroy_explosions(Explosion *explosion) {
  if (!explosion)
    return;

  free(explosion);
}