#include "../../../includes/backend/collision/collision.h"

#include <stdio.h>

static int collide(float ax1, float ay1, float ax2, float ay2, float bx1,
                   float by1, float bx2, float by2) {
  if (ax1 > bx2)
    return 0;
  if (ax2 < bx1)
    return 0;
  if (ay1 > by2)
    return 0;
  if (ay2 < by1)
    return 0;

  return 1;
}

static void acquireSpecial(Player *player) {
  player->special_attack->is_active = 1;
  player->special_attack->on_map = 0;
  player->special_attack->burst_time = time(NULL);
}

void check_special_item_collision(Player *player) {
  float top_x = player->x + PLAYER_WIDTH / 4;
  float top_y = player->y + PLAYER_HEIGHT / 4;
  float bottom_x = (player->x + PLAYER_WIDTH) - PLAYER_WIDTH / 4;
  float bottom_y = (player->y + PLAYER_HEIGHT) - PLAYER_HEIGHT / 4;

  float top_sp_x = player->special_attack->x + SPECIAL_WIDTH / 2;
  float top_sp_y = player->special_attack->y + SPECIAL_HEIGHT / 2;
  float bottom_sp_x =
      (player->special_attack->x + SPECIAL_WIDTH) - SPECIAL_WIDTH / 2;
  float bottom_sp_y =
      (player->special_attack->y + SPECIAL_HEIGHT) - SPECIAL_HEIGHT / 2;

  if (collide(top_x, top_y, bottom_x, bottom_y, top_sp_x, top_sp_y, bottom_sp_x,
              bottom_sp_y) &&
      player->special_attack->on_map) {
    acquireSpecial(player);
  }
}

static void handleShotToEnemyCollision(Shot *shot, Enemy *enemy) {
  enemy->life--;
  shot->is_fired = 0;
  if (enemy->life <= 0)
    enemy->isAlive = DEAD;
}

static void check(Gun *gun, Enemy *enemies, int spawned, Explosion *explosion) {
  for (int i = 0; i < MAX_SHOTS; i++) {
    if (!gun->shots[i].is_fired)
      continue;

    float shot_top_x = gun->shots[i].x;
    float shot_top_y = gun->shots[i].y;
    float shot_bottom_x = (gun->shots[i].x + SHOT_WIDTH);
    float shot_bottom_y = (gun->shots[i].y + SHOT_HEIGHT);

    for (int j = 0; j < spawned; j++) {
      if (!enemies[j].isAlive)
        continue;

      float enemy_top_x = enemies[j].x;
      float enemy_top_y = enemies[j].y;
      float enemy_bottom_x = (enemies[j].x + ENEMY_WIDTH);
      float enemy_bottom_y = (enemies[j].y + ENEMY_HEIGHT);

      if (collide(shot_top_x, shot_top_y, shot_bottom_x, shot_bottom_y,
                  enemy_top_x, enemy_top_y, enemy_bottom_x, enemy_bottom_y)) {
        handleShotToEnemyCollision(&gun->shots[i], &enemies[j]);
        spawn_explosion(explosion, enemies[j].x, enemies[j].y);
      }
    }
  }
}

void check_player_shots(Gun *gun, Enemy *enemies1, int spawned1,
                        Enemy *enemies2, int spawned2, Explosion *explosion) {
  check(gun, enemies1, spawned1, explosion);
  check(gun, enemies2, spawned2, explosion);
}

/*********************************************************************** */

static void handleSpecialShotToEnemyCollision(Shot *shot, Enemy *enemy,
                                              SPECIAL_TYPE type) {
  if (type == SPECIAL_GUN_ONE) {
    enemy->life -= 4;
  } else {
    enemy->life -= 8;
  }
  shot->is_fired = 0;
  if (enemy->life <= 0)
    enemy->isAlive = DEAD;
}

static void check_special(Special *sp, Enemy *enemies, int spawned,
                          Explosion *explosion) {
  for (int i = 0; i < MAX_SHOTS; i++) {
    if (!sp->gun->shots[i].is_fired)
      continue;

    float shot_top_x = sp->gun->shots[i].x;
    float shot_top_y = sp->gun->shots[i].y;
    float shot_bottom_x = (sp->gun->shots[i].x + SHOT_WIDTH / 2);
    float shot_bottom_y = (sp->gun->shots[i].y + SHOT_WIDTH / 2);

    for (int j = 0; j < spawned; j++) {
      if (!enemies[j].isAlive)
        continue;

      float enemy_top_x = enemies[j].x;
      float enemy_top_y = enemies[j].y;
      float enemy_bottom_x = (enemies[j].x + ENEMY_WIDTH);
      float enemy_bottom_y = (enemies[j].y + ENEMY_HEIGHT);

      if (collide(shot_top_x, shot_top_y, shot_bottom_x, shot_bottom_y,
                  enemy_top_x, enemy_top_y, enemy_bottom_x, enemy_bottom_y)) {
        handleSpecialShotToEnemyCollision(&sp->gun->shots[i], &enemies[j],
                                          sp->type);
        spawn_explosion(explosion, enemies[j].x, enemies[j].y);
      }
    }
  }
}

void check_player_special_shots(Special *sp, Enemy *enemies1, int spawned1,
                                Enemy *enemies2, int spawned2,
                                Explosion *explosion) {
  check_special(sp, enemies1, spawned1, explosion);
  check_special(sp, enemies2, spawned2, explosion);
}

/*********************************************************************** */

static void handleShotToPlayerCollision(Shot *shot, Player *player) {
  player->health--;
  player->invincible_timer = 180;
  player->respawn_timer = 90;
  shot->is_fired = 0;
}

static void checkPlayerCollisionWithEnemyShots(Player *player, Enemy *enemies,
                                               int spawned,
                                               Explosion *explosion) {
  for (int i = 0; i < spawned; i++) {
    for (int j = 0; j < MAX_SHOTS; j++) {
      if (!enemies[i]._gun->shots[j].is_fired)
        continue;

      float shot_top_x = enemies[i]._gun->shots[j].x;
      float shot_top_y = enemies[i]._gun->shots[j].y;
      float shot_bottom_x = shot_top_x + ENEMY_SHOT_WIDTH / 4;
      float shot_bottom_y = shot_top_y + ENEMY_SHOT_HEIGHT / 4;

      float player_top_x = player->x + PLAYER_WIDTH / 4;
      float player_top_y = player->y + PLAYER_HEIGHT / 4;
      float player_bottom_x = (player->x + PLAYER_WIDTH) - PLAYER_WIDTH / 4;
      float player_bottom_y = (player->y + PLAYER_HEIGHT) - PLAYER_HEIGHT / 4;

      if (collide(player_top_x, player_top_y, player_bottom_x, player_bottom_y,
                  shot_top_x, shot_top_y, shot_bottom_x, shot_bottom_y)) {
        handleShotToPlayerCollision(&enemies[i]._gun->shots[j], player);
        spawn_explosion(explosion, player->x, player->y + PLAYER_WIDTH / 4);
      }
    }
  }
}

void check_enemy_shots(Enemy *enemies1, int spawned1, Enemy *enemies2,
                       int spawned2, Player *player, Explosion *explosion) {
  checkPlayerCollisionWithEnemyShots(player, enemies1, spawned1, explosion);
  checkPlayerCollisionWithEnemyShots(player, enemies2, spawned2, explosion);
}

static int checkCollisionWithEnemies(Player *player, Enemy *enemies,
                                     int spawned, Explosion *explosion) {
  for (int i = 0; i < spawned; i++) {
    if (enemies[i].isAlive) {
      float player_top_x = player->x + PLAYER_WIDTH / 4;
      float player_top_y = player->y + PLAYER_HEIGHT / 4;
      float player_bottom_x = (player->x + PLAYER_WIDTH) - PLAYER_WIDTH / 4;
      float player_bottom_y = (player->y + PLAYER_HEIGHT) - PLAYER_HEIGHT / 4;

      float enemy_top_x = enemies[i].x + ENEMY_WIDTH / 2;
      float enemy_top_y = enemies[i].y + ENEMY_HEIGHT / 2;
      float enemy_bottom_x = (enemies[i].x + ENEMY_WIDTH) - ENEMY_WIDTH / 2;
      float enemy_bottom_y = (enemies[i].y + ENEMY_HEIGHT) - ENEMY_HEIGHT / 2;

      if (collide(player_top_x, player_top_y, player_bottom_x, player_bottom_y,
                  enemy_top_x, enemy_top_y, enemy_bottom_x, enemy_bottom_y)) {
        spawn_explosion(explosion, player->x, player->y + PLAYER_HEIGHT / 2);
        spawn_explosion(explosion, enemies[i].x, enemies[i].y);
        enemies[i].life--;
        if (enemies[i].life == 0)
          enemies[i].isAlive = DEAD;
        return 1;  // Retorna 1 ao detectar colisão
      }
    }
  }
  return 0;  // Retorna 0 se não houver colisão
}

void check_player_enemy_collision(Player *player, Enemy *enemies1,
                                  int spawned_enemies1, Enemy *enemies2,
                                  int spawned_enemies2, Explosion *explosion) {
  int damaged = 0;  // Evita múltiplas colisões

  // Verifica colisão com o primeiro grupo de inimigos
  damaged =
      checkCollisionWithEnemies(player, enemies1, spawned_enemies1, explosion);

  // Se nenhuma colisão foi detectada, verifica com o segundo grupo
  if (!damaged) {
    damaged = checkCollisionWithEnemies(player, enemies2, spawned_enemies2,
                                        explosion);
  }

  if (damaged) {
    player->health--;
    player->respawn_timer = 90;
    player->invincible_timer = 180;
  }
}

/************************************************************** */

static int checkPlayerBossCollision(Player *player, Boss *boss,
                                    Explosion *explosion) {
  if (!boss->spawned)
    return 0;

  float player_top_x = player->x + PLAYER_WIDTH / 4;
  float player_top_y = player->y + PLAYER_HEIGHT / 4;
  float player_bottom_x = (player->x + PLAYER_WIDTH) - PLAYER_WIDTH / 4;
  float player_bottom_y = (player->y + PLAYER_HEIGHT) - PLAYER_HEIGHT / 4;

  float boss_top_x = boss->x + BOSS_WIDTH / 4;
  float boss_top_y = boss->y + BOSS_HEIGHT / 4;
  float boss_bottom_x = (boss->x + BOSS_WIDTH) - BOSS_WIDTH / 4;
  float boss_bottom_y = (boss->y + BOSS_HEIGHT) - BOSS_HEIGHT / 4;

  if (collide(player_top_x, player_top_y, player_bottom_x, player_bottom_y,
              boss_top_x, boss_top_y, boss_bottom_x, boss_bottom_y)) {
    player->health = 0;
    spawn_explosion(explosion, player->x, player->y + PLAYER_HEIGHT / 2);
    spawn_explosion(explosion, boss->x, boss->y + BOSS_HEIGHT / 4);
    return 1;
  }

  return 0;
}

static void checkPlayerShotsCollisionWithBoss(Player *player, Boss *boss,
                                              Explosion *explosion) {
  Gun *gun = player->_gun;
  for (int i = 0; i < MAX_SHOTS; i++) {
    if (!gun->shots[i].is_fired)
      continue;

    float shot_top_x = gun->shots[i].x;
    float shot_top_y = gun->shots[i].y;
    float shot_bottom_x = (gun->shots[i].x + SHOT_WIDTH);
    float shot_bottom_y = (gun->shots[i].y + SHOT_HEIGHT);

    float boss_top_x = boss->x + BOSS_WIDTH / 2;
    float boss_top_y = boss->y + BOSS_HEIGHT / 2;
    float boss_bottom_x = (boss->x + BOSS_WIDTH) - BOSS_WIDTH / 2;
    float boss_bottom_y = (boss->y + BOSS_HEIGHT) - BOSS_HEIGHT / 2;

    if (collide(shot_top_x, shot_top_y, shot_bottom_x, shot_bottom_y,
                boss_top_x, boss_top_y, boss_bottom_x, boss_bottom_y)) {
      spawn_explosion(explosion, boss->x, boss->y + BOSS_HEIGHT / 4);
      boss->life--;
      gun->shots[i].is_fired = 0;
      if (boss->life <= 0)
        boss->state = BOSS_STATE_DEAD;
    }
  }
}

static int checkBossShotsCollisionWithPlayer(Player *player, Boss *boss,
                                             Explosion *explosion) {
  Weapon *weapon = boss->weapon;
  for (int i = 0; i < MAX_SHOTS; i++) {
    if (!weapon->shots[i].is_fired)
      continue;

    float shot_top_x = weapon->shots[i].x;
    float shot_top_y = weapon->shots[i].y;
    float shot_bottom_x = (weapon->shots[i].x + weapon->width);
    float shot_bottom_y = (weapon->shots[i].y + weapon->height);

    float player_top_x = player->x + PLAYER_WIDTH / 4;
    float player_top_y = player->y + PLAYER_HEIGHT / 4;
    float player_bottom_x = (player->x + PLAYER_WIDTH) - PLAYER_WIDTH / 4;
    float player_bottom_y = (player->y + PLAYER_HEIGHT) - PLAYER_HEIGHT / 4;

    if (collide(shot_top_x, shot_top_y, shot_bottom_x, shot_bottom_y,
                player_top_x, player_top_y, player_bottom_x, player_bottom_y)) {
      spawn_explosion(explosion, player->x, player->y + PLAYER_WIDTH / 4);
      return 1;
    }
  }

  return 0;
}

void check_boss_collision(Player *player, Boss *boss, Explosion *explosion) {
  if (checkPlayerBossCollision(player, boss, explosion))
    return;  // O jogador morreu na colisão direta com o boss

  if (checkBossShotsCollisionWithPlayer(player, boss, explosion)) {
    player->health -= boss->weapon->damage;
    player->respawn_timer = 90;
    player->invincible_timer = 180;
  }
}

/*********************************************************************** */

void check_player_special_shots_to_boss(Player *player, Boss *boss,
                                        Explosion *explosion) {
  Gun *sg = player->special_attack->gun;
  for (int i = 0; i < MAX_SHOTS; i++) {
    if (!sg->shots[i].is_fired)
      continue;

    float shot_left_x = sg->shots[i].x;
    float shot_top_y = sg->shots[i].y;
    float shot_right_x = sg->shots[i].x + 40;
    float shot_bottom_y = sg->shots[i].y + 40;

    float boss_left_x = boss->x;
    float boss_top_y = boss->y;
    float boss_right_x = boss->x + BOSS_WIDTH;
    float boss_bottom_y = boss->y + BOSS_HEIGHT;

    if (collide(shot_left_x, shot_top_y, shot_right_x, shot_bottom_y,
                boss_left_x, boss_top_y, boss_right_x, boss_bottom_y)) {
      spawn_explosion(explosion, boss->x, boss->y);
      boss->life -= player->special_attack->damage;
      sg->shots[i].is_fired = 0;
      if (boss->life <= 0)
        boss->state = BOSS_STATE_DEAD;
    }
  }
}

/*********************************************************************** */

void check_all_collisions(Player *player, Level *l) {
  if (player->invincible_timer > 0) {
    player->invincible_timer--;
  }
#ifdef MORTAL
  else {
    // colisao direta
    check_player_enemy_collision(player, l->sp1->enemies, l->sp1->spawned,
                                 l->sp2->enemies, l->sp2->spawned,
                                 l->explosion);

    // colisao com o boss
    check_boss_collision(player, l->boss, l->explosion);

    // disparos dos inimigos no jogador
    check_enemy_shots(l->sp1->enemies, l->sp1->spawned, l->sp2->enemies,
                      l->sp2->spawned, player, l->explosion);
  }
#endif

  check_special_item_collision(player);

  // disparos do jogador no inimigo
  check_player_shots(player->_gun, l->sp1->enemies, l->sp1->spawned,
                     l->sp2->enemies, l->sp2->spawned, l->explosion);
  checkPlayerShotsCollisionWithBoss(player, l->boss, l->explosion);

  // disparo especial
  check_player_special_shots(player->special_attack, l->sp1->enemies,
                             l->sp1->spawned, l->sp2->enemies, l->sp2->spawned,
                             l->explosion);
  check_player_special_shots_to_boss(player, l->boss, l->explosion);
}