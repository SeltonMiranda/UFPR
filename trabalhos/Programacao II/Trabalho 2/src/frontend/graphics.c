#include "../../includes/frontend/graphics.h"

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "../../includes/backend/boss.h"
#include "../../includes/config/config.h"

void render_background(Resources_Manager *r, GAME_STATE state) {
  al_clear_to_color(al_map_rgb(0, 0, 0));
  switch (state) {
    case GAME_STATE_MENU:
    case GAME_STATE_GAME_OVER:
    case GAME_STATE_VICTORY:
    case GAME_STATE_TRANSITION:
      al_draw_bitmap(r->background.bg_common, 0, 0, 0);
      break;

    case GAME_STATE_LEVEL_ONE:
      al_draw_bitmap(r->background.bg_one, r->background.x, 0, 0);
      al_draw_bitmap(r->background.bg_one, r->background.x + SCREEN_WIDTH, 0,
                     0);
      break;

    case GAME_STATE_LEVEL_TWO:
      al_draw_bitmap(r->background.bg_two, r->background.x, 0, 0);
      al_draw_bitmap(r->background.bg_two, r->background.x + SCREEN_WIDTH, 0,
                     0);
      break;
  }
}

void render_victory_screen(Resources_Manager *r, GAME_STATE state) {
  render_background(r, state);
  ALLEGRO_FONT *font = al_create_builtin_font();
  char *text = "Voce Venceu! Aperte R para voltar ao menu.";
  if (font) {
    al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2,
                 SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, text);
    al_destroy_font(font);
  }
  al_flip_display();
}

void render_menu(Resources_Manager *r, GAME_STATE state) {
  render_background(r, state);

  ALLEGRO_FONT *font = al_create_builtin_font();
  char *text = "Pressione Enter para começar o jogo ou Q para sair";
  if (font) {
    al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2,
                 SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, text);
    al_destroy_font(font);
  }

  al_flip_display();
}

void render_gameover(Resources_Manager *r, GAME_STATE state) {
  render_background(r, state);
  ALLEGRO_FONT *font = al_create_builtin_font();
  char *text =
      "GAME OVER   Pressione Enter para recomeçcar o jogo ou Q para sair";
  if (font) {
    al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2,
                 SCREEN_HEIGHT / 2 - 20, ALLEGRO_ALIGN_CENTRE, text);
  }

  al_flip_display();
}

void render_prephase(Resources_Manager *r, GAME_STATE state) {
  render_background(r, state);
  ALLEGRO_FONT *font = al_create_builtin_font();
  char *text = "Voce venceu! Pressione N para continuar";
  if (font) {
    al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2,
                 SCREEN_HEIGHT / 2 - 20, ALLEGRO_ALIGN_CENTRE, text);
  }

  al_flip_display();
}

void draw_player(Player *_player, Resources_Manager *_resources) {
  if (_player->respawn_timer)
    return;

  if (((_player->invincible_timer / 2) % 3) == 1)
    return;

  if (_player->_state == MOVEMENT) {
    int frame = (_player->current_frame / 15) % 12 + 1;
    al_draw_bitmap(_resources->player.sprites[frame], _player->x, _player->y,
                   0);
  }

  al_draw_bitmap(_resources->player.sprites[0], _player->x, _player->y, 0);
}

void draw_enemies(Enemy *enemies, int spawned, Resources_Manager *r) {
  ALLEGRO_BITMAP *sprite;
  switch (enemies[0]._type) {
    case ENEMY_1:
      sprite = r->enemy.enemy_one;
      break;
    case ENEMY_2:
      sprite = r->enemy.enemy_two;
      break;
    case ENEMY_3:
      sprite = r->enemy.enemy_three;
      break;
    case ENEMY_4:
      sprite = r->enemy.enemy_four;
      break;
  }

  for (int i = 0; i < spawned; i++) {
    if (enemies[i].isAlive)
      al_draw_bitmap(sprite, enemies[i].x, enemies[i].y, 0);
  }
}

void draw_shots(Gun *_gun, int isPlayer, Resources_Manager *r) {
  for (int i = 0; i < MAX_SHOTS; i++) {
    if (!_gun->shots[i].is_fired)
      continue;

    int frame = (_gun->shots[i].current_frame / 15) % 3;
    float x = _gun->shots[i].x;
    float y = _gun->shots[i].y;
    if (isPlayer)
      al_draw_bitmap(r->shots.normal_shot[frame], x, y, 0);
    else
      al_draw_bitmap(r->shots.enemy_shot[frame], x, y, 0);
  }
}

void draw_special_shots(Special *sp, Resources_Manager *r) {
  for (int i = 0; i < MAX_SHOTS; i++) {
    if (!sp->gun->shots[i].is_fired)
      continue;

    float x = sp->gun->shots[i].x;
    float y = sp->gun->shots[i].y;
    int frame;
    if (sp->type == SPECIAL_GUN_ONE) {
      frame = (sp->gun->shots[i].current_frame / 15) % 5;
      al_draw_bitmap(r->special.shot_one[frame], x, y, 0);
    } else if (sp->type == SPECIAL_GUN_TWO) {
      frame = (sp->gun->shots[i].current_frame / 5) % 13;
      al_draw_bitmap(r->special.shot_two[frame], x, y, 0);
    }
  }
}

void draw_special_item(Special *sp, Resources_Manager *r) {
  if (!sp->on_map)
    return;

  switch (sp->type) {
    case SPECIAL_GUN_ONE:
      al_draw_bitmap(r->special.item[0], sp->x, sp->y, 0);

      break;

    case SPECIAL_GUN_TWO:
      al_draw_bitmap(r->special.item[1], sp->x, sp->y, 0);
      break;
  }
}

void draw_enemies_shots(Enemy *enemies, int spawned, Resources_Manager *r) {
  for (int i = 0; i < spawned; i++) {
    draw_shots(enemies[i]._gun, ISENEMY, r);
  }
}

void draw_boss_shot(Boss *boss, Resources_Manager *r) {
  for (int i = 0; i < MAX_SHOTS; i++) {
    if (boss->weapon->shots[i].is_fired) {
      if (boss->type == LEVEL_ONE_BOSS) {
        int frame = (boss->weapon->shots[i].current_frame / 15) % 5;
        switch (boss->weapon->type) {
          case WEAPON_TYPE_ONE:
            al_draw_bitmap(r->shots.boss_one_first_shot,
                           boss->weapon->shots[i].x, boss->weapon->shots[i].y,
                           0);
            break;

          case WEAPON_TYPE_TWO:
            al_draw_bitmap(r->shots.boss_one_second_shot[frame],
                           boss->weapon->shots[i].x, boss->weapon->shots[i].y,
                           0);
            break;

          case WEAPON_TYPE_THREE:
          case WEAPON_TYPE_FOUR:
            return;
        }
      } else {
        int frame = (boss->weapon->shots[i].current_frame / 15) % 4;
        switch (boss->weapon->type) {
          case WEAPON_TYPE_THREE:
            al_draw_bitmap(r->shots.boss_two_first_shot[frame],
                           boss->weapon->shots[i].x, boss->weapon->shots[i].y,
                           0);
            break;
          case WEAPON_TYPE_FOUR:
            al_draw_bitmap(r->shots.boss_two_second_shot[frame],
                           boss->weapon->shots[i].x, boss->weapon->shots[i].y,
                           0);
            break;
          case WEAPON_TYPE_ONE:
          case WEAPON_TYPE_TWO:
            return;
        }
      }
    }
  }
}

void draw_boss(Boss *boss, Resources_Manager *r, GAME_STATE state) {
  if (boss->state == BOSS_STATE_NOT_SPAWNED || boss->state == BOSS_STATE_DEAD)
    return;

  if (state == GAME_STATE_LEVEL_ONE)
    al_draw_bitmap(r->boss.boss_one, boss->x, boss->y, 0);
  else if (state == GAME_STATE_LEVEL_TWO)
    al_draw_bitmap(r->boss.boss_two, boss->x, boss->y, 0);
}

void draw_explosions(Explosion *explosions, Resources_Manager *r) {
  for (int i = 0; i < MAX_EXPLOSIONS; i++) {
    if (!explosions[i].is_active)
      continue;

    explosions[i].frame++;
    if (explosions[i].frame >= 9)
      explosions[i].frame = 0;

    al_draw_bitmap(r->explosion.explosion[explosions[i].frame], explosions[i].x,
                   explosions[i].y, 0);
  }
}