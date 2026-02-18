#include "../../includes/backend/boss.h"

#include <stdio.h>
#include <time.h>

#include "../../includes/config/config.h"
#include "../../includes/utils/utils.h"

Boss *create_boss(BOSS_TYPE type) {
  Boss *boss = (Boss *)malloc(sizeof(Boss));
  must_init(boss, "Boss");

  boss->weapon = create_weapon();
  boss->type = type;
  if (boss->type == LEVEL_ONE_BOSS) {
    boss->weapon->type = WEAPON_TYPE_ONE;
    boss->weapon->damage = 3;
    boss->weapon->width = 64;
    boss->weapon->height = 128;
  } else {
    boss->weapon->type = WEAPON_TYPE_THREE;
    boss->weapon->damage = 5;
    boss->weapon->width = 63;
    boss->weapon->height = 32;
  }

  boss->life = BOSS_LIFE;
  boss->spawned = 0;
  boss->timer = time(NULL);
  boss->state = BOSS_STATE_NOT_SPAWNED;
  boss->x = SCREEN_WIDTH - 150;
  boss->y = -BOSS_HEIGHT;
  boss->direction = DOWN;

  return boss;
}

Weapon *create_weapon() {
  Weapon *w = (Weapon *)malloc(sizeof(Weapon));
  must_init(w, "Weapon");

  w->timer = 0;
  for (int i = 0; i < MAX_SHOTS; i++) {
    w->shots[i].is_fired = 0;
    w->shots[i].current_frame = 0;
  }

  return w;
}

int boss_should_spawn(Boss *boss) {
  if (boss->spawned)
    return 0;
  if (difftime(time(NULL), boss->timer) >= BOSS_TIME_SPAWN)
    return 1;
  return 0;
}

void spawn_boss(Boss *boss) {
  boss->state = BOSS_STATE_SPAWNED;
  boss->spawned = 1;
}

void boss_shot(Weapon *w, float x, float y) {
  for (int i = 0; i < MAX_SHOTS; i++) {
    if (w->shots[i].is_fired == 0) {
      w->shots[i].is_fired = 1;
      w->shots[i].x = x;
      w->shots[i].y = y;
    }
  }
}

void update_boss_shot(Weapon *w) {
  for (int i = 0; i < MAX_SHOTS; i++) {
    if (w->shots[i].is_fired) {
      w->shots[i].x -= SHOT_SPEED;
      w->shots[i].current_frame++;
      if (w->shots[i].x <= 0) {
        w->shots[i].is_fired = 0;
        w->shots[i].current_frame = 0;
      }
    }
  }
}

void update_boss(Boss *boss) {
  update_boss_shot(boss->weapon);

  if (boss->life == BOSS_LIFE / 2) {
    switch (boss->type) {
      case LEVEL_ONE_BOSS:
        boss->weapon->type = WEAPON_TYPE_TWO;
        boss->weapon->damage = 6;
        boss->weapon->width = 64;
        boss->weapon->height = 64;
        break;

      case LEVEL_TWO_BOSS:
        boss->weapon->type = WEAPON_TYPE_FOUR;
        boss->weapon->damage = 10;
        boss->weapon->width = 63;
        boss->weapon->height = 32;
        break;
    }
  }

  if (boss->state == BOSS_STATE_DEAD)
    return;

  if (boss->state == BOSS_STATE_NOT_SPAWNED)
    return;

  boss->y += (boss->direction * BOSS_SPEED);
  if (boss->y <= 0) {
    boss->y = 0;
    boss->direction = DOWN;
  }

  if (boss->y >= SCREEN_HEIGHT - BOSS_HEIGHT - 100) {
    boss->y = SCREEN_HEIGHT - BOSS_HEIGHT - 100;
    boss->direction = UP;
  }

  if (boss->weapon->timer == 0) {
    boss_shot(boss->weapon, boss->x, boss->y + 128 / 2);
    boss->weapon->timer = 20;
  } else {
    boss->weapon->timer--;
  }
}

void destroy_boss(Boss *boss) {
  free(boss);
}