#ifndef __PLAYER__
#define __PLAYER__

#include <allegro5/allegro5.h>

#include "joystick.h"
#include "special.h"

typedef enum PLAYER_STATE { IDLE, MOVEMENT } PLAYER_STATE;

typedef struct Player {
  float x, y;
  int health;
  int current_frame;
  int invincible_timer;
  int respawn_timer;

  Joystick *_joystick;
  Gun *_gun;
  Special *special_attack;
  PLAYER_STATE _state;

} Player;

Player *create_player();

void update_joystick(Joystick *j, ALLEGRO_EVENT *event);

void update_player(Player *player);

void destroy_player(Player *player);

#endif  // __PLAYER__