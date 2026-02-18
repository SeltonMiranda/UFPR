#ifndef __EXPLOSION__
#define __EXPLOSION__

#define MAX_EXPLOSIONS 512

typedef struct Explosion {
  float x, y;
  int is_active;
  int timer;
  int frame;

} Explosion;

Explosion *init_explosions();

void spawn_explosion(Explosion *e, float x, float y);

void update_explosions(Explosion *explosions);

void destroy_explosions(Explosion *explosion);
#endif  // __EXPLOSION__