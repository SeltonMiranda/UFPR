#ifndef __COLISION__
#define __COLISION__

#include "../boss.h"
#include "../enemies.h"
#include "../level.h"
#include "../player.h"

void check_all_collisions(Player *player, Level *l);

void check_player_shots(Gun *gun, Enemy *enemies1, int spawned1,
                        Enemy *enemies2, int spawned2, Explosion *explosion);

void check_special_item_collision(Player *player);

void check_enemy_shots(Enemy *enemies1, int spawned1, Enemy *enemies2,
                       int spawned2, Player *player, Explosion *explosion);

void check_player_enemy_collision(Player *player, Enemy *enemies1,
                                  int spawned_enemies1, Enemy *enemies2,
                                  int spawned_enemies2, Explosion *explosion);

void check_player_special_shots(Special *sp, Enemy *enemies1, int spawned1,
                                Enemy *enemies2, int spawned2,
                                Explosion *explosion);

void check_boss_collision(Player *player, Boss *boss, Explosion *explosion);
void check_player_special_shots_to_boss(Player *player, Boss *boss,
                                        Explosion *explosion);

#endif  // __COLISION__