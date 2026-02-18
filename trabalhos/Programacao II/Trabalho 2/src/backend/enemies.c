#include "../../includes/backend/enemies.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../includes/config/config.h"
#include "../../includes/utils/utils.h"

Enemy *create_enemy(ENEMY_TYPE type, int quantity) {
  Enemy *enemy_vector = (Enemy *)malloc(sizeof(Enemy) * quantity);
  must_init(enemy_vector, "Enemy vector");

  for (int i = 0; i < quantity; i++) {
    enemy_vector[i]._type = type;
    enemy_vector[i].isAlive = ALIVE;
    enemy_vector[i]._gun = create_gun(ENEMY);
    enemy_vector[i]._gun->timer = rand_between(MIN_TIME, MAX_TIME);

    switch (type) {
      case ENEMY_1:
        enemy_vector[i].life = ENEMY_ONE_LIFE;
        enemy_vector[i].x = SCREEN_WIDTH + ENEMY_WIDTH + i * ENEMY_PADDING;
        enemy_vector[i].y = (SCREEN_HEIGHT - ENEMY_HEIGHT) / 2 - ENEMY_PADDING;
        break;

      case ENEMY_2:
        enemy_vector[i].life = ENEMY_TWO_LIFE;
        enemy_vector[i].x = SCREEN_WIDTH + ENEMY_WIDTH;
        if (enemy_vector[i].y > 500)
          enemy_vector[i].y = 0;
        enemy_vector[i].y = ENEMY_PADDING / 2 +
                            (ENEMY_HEIGHT + ENEMY_PADDING / 2) * (i % BATCH);
        break;

      case ENEMY_3:
        enemy_vector[i].life = ENEMY_THREE_LIFE;
        enemy_vector[i].x = SCREEN_WIDTH + i * (ENEMY_WIDTH + ENEMY_PADDING);
        enemy_vector[i].y =
            rand_between(0, SCREEN_HEIGHT - ENEMY_HEIGHT * 2 - 100);
        break;

      case ENEMY_4:
        enemy_vector[i].life = ENEMY_FOUR_LIFE;
        enemy_vector[i].x = SCREEN_WIDTH + i * (ENEMY_WIDTH + ENEMY_PADDING);
        enemy_vector[i].y = 0;
        break;
    }
  }

  return enemy_vector;
}

static void update_enemy_position(Enemy *enemy) {
  enemy->x -= 1.0f;
  if (enemy->x >= SCREEN_WIDTH)
    return;

  switch (enemy->_type) {
    case ENEMY_1:
      enemy->y = ((SCREEN_HEIGHT - ENEMY_HEIGHT) / 2 - ENEMY_PADDING) +
                 sin(enemy->x / 50) * 200;
      break;

    case ENEMY_2:
      return;

    case ENEMY_3:
      if ((int)(enemy->x / 50) % 2 == 0) {
        enemy->y += 1.0f;
      } else {
        enemy->y -= 1.0f;
      }
      break;

    case ENEMY_4:
      enemy->y += 0.5f;
      break;
  }

  if (enemy->y < 0)
    enemy->y = 0;
  if (enemy->y > SCREEN_HEIGHT - ENEMY_HEIGHT - 150)
    enemy->y = SCREEN_HEIGHT - ENEMY_HEIGHT - 150;
}

void update_enemies(Enemy *enemies, int spawned) {
  for (int i = 0; i < spawned; i++) {
    if (enemies[i].isAlive) {
      update_enemy_position(&enemies[i]);

      if (enemies[i]._gun->timer == 0 && enemies[i].x < SCREEN_WIDTH) {
        gun_shot(enemies[i]._gun, enemies[i].x,
                 enemies[i].y + ENEMY_HEIGHT / 2 - 1);
        enemies[i]._gun->timer = rand_between(MIN_TIME, MAX_TIME);
      }

      if (enemies[i]._gun->timer > 0)
        enemies[i]._gun->timer--;

      if (enemies[i].x < -ENEMY_WIDTH)
        enemies[i].isAlive = DEAD;
    }
    update_gun(enemies[i]._gun, 0);
  }
}

void destroy_enemy(Enemy *enemy_vector, int size) {
  for (int i = 0; i < size; i++) {
    destroy_gun(enemy_vector[i]._gun);
  }
  free(enemy_vector);
}