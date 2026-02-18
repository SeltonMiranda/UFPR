#ifndef __GAME__
#define __GAME__

#include <allegro5/allegro5.h>

#include "../frontend/graphics.h"
#include "explosion.h"
#include "gameState.h"
#include "level.h"
#include "player.h"
#include "resourcesManager.h"

typedef struct Game {
  GAME_STATE state;
  Explosion explosion[MAX_EXPLOSIONS];
  Level *level;
  Player *player;
  Resources_Manager *rm;
  int is_running;

  ALLEGRO_BITMAP *background;
  ALLEGRO_TIMER *game_timer;
  ALLEGRO_EVENT_QUEUE *queue;
  ALLEGRO_DISPLAY *display;

} Game;

void init_allegro();

void init_game(Game *game);

void game_loop(Game *game);

void game_run(Game *game);

void handleKeyPress(Game *game, ALLEGRO_EVENT *ev);

void update_game_level(Game *game);

void update_transition(Game *game);

void update_game_state(Game *game);

#endif  // __GAME__