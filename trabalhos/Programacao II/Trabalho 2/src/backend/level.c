#include "../../includes/backend/level.h"

#include "../../includes/config/config.h"
#include "../../includes/utils/utils.h"

Level *loadLevel(LEVEL_PHASE phase) {
  Level *l = (Level *)malloc(sizeof(Level));
  must_init(l, "Level");

  l->explosion = init_explosions();
  l->phase = phase;
  switch (l->phase) {
    case LEVEL_PHASE_ONE:
      l->boss = create_boss(LEVEL_ONE_BOSS);
      l->sp1 = create_spawn_control(ENEMY_1, TOTAL_ENEMIES);
      l->sp2 = create_spawn_control(ENEMY_2, TOTAL_ENEMIES);
      break;

    case LEVEL_PHASE_TWO:
      l->boss = create_boss(LEVEL_TWO_BOSS);
      l->sp1 = create_spawn_control(ENEMY_3, TOTAL_ENEMIES);
      l->sp2 = create_spawn_control(ENEMY_4, TOTAL_ENEMIES);
      break;
  }

  return l;
}

void update_level(Level *l) {
  update_spawn_control(l->sp1);
  update_spawn_control(l->sp2);

  update_enemies(l->sp1->enemies, l->sp1->spawned);
  update_enemies(l->sp2->enemies, l->sp2->spawned);
  update_boss(l->boss);

  if (boss_should_spawn(l->boss))
    spawn_boss(l->boss);

  update_explosions(l->explosion);
}

void destroy_level(Level *l) {
  if (!l)
    return;
  destroy_boss(l->boss);
  destroy_explosions(l->explosion);
  destroy_spawn_control(l->sp1);
  destroy_spawn_control(l->sp2);
  free(l);
}