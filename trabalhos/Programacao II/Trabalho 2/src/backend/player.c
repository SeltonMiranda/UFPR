#include "../../includes/backend/player.h"

#include <stdio.h>
#include <stdlib.h>

#include "../../includes/config/config.h"
#include "../../includes/utils/utils.h"

Player *create_player() {
  Player *_player = (Player *)malloc(sizeof(Player));
  must_init(_player, "Player");

  _player->health = 9;
  _player->invincible_timer = 120;
  _player->respawn_timer = 0;
  _player->x = PLAYER_PADDING;
  _player->y = (SCREEN_HEIGHT - PLAYER_HEIGHT) / 2;
  _player->current_frame = 0;
  _player->_state = IDLE;
  _player->_joystick = create_joystick();
  _player->_gun = create_gun(PLAYER);
  _player->special_attack = init_special();

  return _player;
}

void update_joystick(Joystick *j, ALLEGRO_EVENT *event) {
  switch (event->keyboard.keycode) {
    case ALLEGRO_KEY_DOWN:
      update_joystick_down(j);
      break;

    case ALLEGRO_KEY_UP:
      update_joystick_up(j);
      break;

    case ALLEGRO_KEY_LEFT:
      update_joystick_left(j);
      break;

    case ALLEGRO_KEY_RIGHT:
      update_joystick_right(j);
      break;

    case ALLEGRO_KEY_Z:
      update_joystick_fire(j);
      break;

    case ALLEGRO_KEY_X:
      update_joystick_special(j);
      break;
  }
}

void update_player(Player *player) {
  update_gun(player->_gun, 1);
  update_gun(player->special_attack->gun, 1);

  if (player->health <= 0)
    return;

  if (player->respawn_timer) {
    player->respawn_timer--;
    return;
  }

  player->_state = IDLE;
  if (player->_joystick->down) {
    player->_state = MOVEMENT;
    player->y += PLAYER_SPEED;
    if (player->y >= 500 - PLAYER_HEIGHT - PLAYER_PADDING)
      player->y = 500 - PLAYER_HEIGHT - PLAYER_PADDING;
  }

  if (player->_joystick->up) {
    player->_state = MOVEMENT;
    player->y -= PLAYER_SPEED;
    if (player->y <= -PLAYER_PADDING)
      player->y = -PLAYER_PADDING;
  }

  if (player->_joystick->left) {
    player->_state = MOVEMENT;
    player->x -= PLAYER_SPEED;
    if (player->x <= 0) {
      player->x = 0;
    }
  }

  if (player->_joystick->right) {
    player->_state = MOVEMENT;
    player->x += PLAYER_SPEED;
    if (player->x >= 1200 - PLAYER_WIDTH)
      player->x = 1200 - PLAYER_WIDTH;
  }

  if (player->_joystick->fire) {
    if (player->_gun->timer == 0) {
      gun_shot(player->_gun, player->x + PLAYER_WIDTH - SHOT_WIDTH / 2,
               player->y + PLAYER_HEIGHT / 2 - SHOT_HEIGHT / 2);
      player->_gun->timer = SHOT_COOLDOWN;
    }

    if (player->_gun->timer > 0)
      player->_gun->timer--;
  }

  if (player->_joystick->special && player->special_attack->is_active) {
    if (player->special_attack->gun->timer == 0) {
      int width, height;
      if (player->special_attack->type == SPECIAL_GUN_ONE) {
        width = 64;
        height = 32;
      } else {
        width = 104;
        height = 22;
      }

      gun_shot(player->special_attack->gun,
               player->x + (PLAYER_WIDTH - width) / 2,
               player->y + (PLAYER_HEIGHT - height) / 2);
      player->special_attack->gun->timer = SHOT_COOLDOWN;
    }

    if (player->special_attack->gun->timer) {
      player->special_attack->gun->timer--;
    }
  }

  if (player->_state == MOVEMENT)
    player->current_frame++;
}

void destroy_player(Player *player) {
  if (!player)
    return;
  destroy_special_attack(player->special_attack);
  destroy_gun(player->_gun);
  destroy_joystick(player->_joystick);
  free(player);
}
