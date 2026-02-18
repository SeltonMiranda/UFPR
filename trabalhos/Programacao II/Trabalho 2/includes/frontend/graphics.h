#ifndef __GRAPHICS__
#define __GRAPHICS__

#include "../backend/boss.h"
#include "../backend/enemies.h"
#include "../backend/explosion.h"
#include "../backend/gameState.h"
#include "../backend/gun.h"
#include "../backend/player.h"
#include "../backend/resourcesManager.h"
#include "../backend/special.h"

void render_background(Resources_Manager *r, GAME_STATE state);

void render_victory_screen(Resources_Manager *r, GAME_STATE state);

void render_menu(Resources_Manager *r, GAME_STATE state);

void render_gameover(Resources_Manager *r, GAME_STATE state);

void render_prephase(Resources_Manager *r, GAME_STATE state);

void draw_player(Player *_player, Resources_Manager *_resources);

void draw_enemies(Enemy *enemies, int spawned, Resources_Manager *r);

void draw_enemies_shots(Enemy *enemies, int spawned, Resources_Manager *r);

void draw_special_shots(Special *sp, Resources_Manager *r);

void draw_shots(Gun *_gun, int isPlayer, Resources_Manager *r);

void draw_boss_shot(Boss *boss, Resources_Manager *r);

void draw_boss(Boss *boss, Resources_Manager *r, GAME_STATE state);

void draw_special_item(Special *sp, Resources_Manager *r);

void draw_explosions(Explosion *explosions, Resources_Manager *r);

#endif  // __GRAPHICS__