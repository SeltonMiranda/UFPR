
#include "../../includes/backend/game.h"

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "../../includes/backend/collision/collision.h"
#include "../../includes/config/config.h"

void init_allegro() {
  al_init();
  al_install_keyboard();
  al_init_primitives_addon();
  al_init_image_addon();
  al_init_font_addon();
}

void init_game(Game *game) {
  game->game_timer = al_create_timer(1.0 / 60.0);
  game->display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
  game->queue = al_create_event_queue();

  al_register_event_source(game->queue, al_get_keyboard_event_source());
  al_register_event_source(game->queue,
                           al_get_display_event_source(game->display));
  al_register_event_source(game->queue,
                           al_get_timer_event_source(game->game_timer));

  al_start_timer(game->game_timer);
  game->is_running = 1;
  game->level = NULL;
  game->player = NULL;
  game->state = GAME_STATE_MENU;
  game->rm = create_resources();
  load_all_sprites(game->rm);
}

void deinit_game(Game *game) {
  destroy_level(game->level);
  destroy_player(game->player);
  destroy_resources(game->rm);
  al_destroy_display(game->display);
  al_destroy_timer(game->game_timer);
  al_destroy_event_queue(game->queue);
}

static void reset_level_one(Game *game) {
  game->state = GAME_STATE_LEVEL_ONE;
  destroy_level(game->level);
  destroy_player(game->player);
  game->level = loadLevel(LEVEL_PHASE_ONE);
  game->player = create_player();
  game->rm->background.x = 0;
  al_flush_event_queue(game->queue);
}

static void update_background(Game *game) {
  game->rm->background.x -= BACKGROUND_SPEED;
  if (game->rm->background.x <= -SCREEN_WIDTH)
    game->rm->background.x = 0;
}

void handleKeyPress(Game *game, ALLEGRO_EVENT *ev) {
  if (ev->keyboard.keycode == ALLEGRO_KEY_Q) {
    game->is_running = 0;
    return;
  }

  switch (game->state) {
    case GAME_STATE_MENU:
      if (ev->keyboard.keycode == ALLEGRO_KEY_ENTER) {
        game->state = GAME_STATE_LEVEL_ONE;

        if (game->player != NULL)
          destroy_player(game->player);

        game->player = create_player();
        game->level = loadLevel(LEVEL_PHASE_ONE);
        al_flush_event_queue(game->queue);
      }
      break;

    case GAME_STATE_LEVEL_ONE:
    case GAME_STATE_LEVEL_TWO:
      update_joystick(game->player->_joystick, ev);
      break;
      ;

    case GAME_STATE_TRANSITION:
      if (ev->keyboard.keycode == ALLEGRO_KEY_N)
        game->state = GAME_STATE_LEVEL_TWO;
      break;

    case GAME_STATE_VICTORY:
      if (ev->keyboard.keycode == ALLEGRO_KEY_R)
        game->state = GAME_STATE_MENU;
      break;

    case GAME_STATE_GAME_OVER:
      if (ev->keyboard.keycode == ALLEGRO_KEY_ENTER)
        reset_level_one(game);
      break;
  }
}

void check_game_victory(Game *game) {
  if (game->level->boss->state == BOSS_STATE_DEAD) {
    if (game->state == GAME_STATE_LEVEL_ONE) {
      destroy_player(game->player);
      destroy_level(game->level);
      game->state = GAME_STATE_TRANSITION;
      game->level = loadLevel(LEVEL_PHASE_TWO);
      game->player = create_player();
    } else if (game->state == GAME_STATE_LEVEL_TWO) {
      game->state = GAME_STATE_VICTORY;
    }

    al_flush_event_queue(game->queue);
  };
}

static void render_game(Game *game) {
  if (al_is_event_queue_empty(game->queue)) {
    render_background(game->rm, game->state);

    draw_enemies(game->level->sp1->enemies, game->level->sp1->spawned,
                 game->rm);
    draw_enemies(game->level->sp2->enemies, game->level->sp2->spawned,
                 game->rm);
    draw_enemies_shots(game->level->sp1->enemies, game->level->sp1->spawned,
                       game->rm);
    draw_enemies_shots(game->level->sp2->enemies, game->level->sp2->spawned,
                       game->rm);

    if (game->level->boss->spawned)
      draw_boss_shot(game->level->boss, game->rm);

    draw_shots(game->player->_gun, ISPLAYER, game->rm);
    draw_boss(game->level->boss, game->rm, game->state);

    if (game->player->special_attack->on_map)
      draw_special_item(game->player->special_attack, game->rm);

    draw_special_shots(game->player->special_attack, game->rm);

    draw_player(game->player, game->rm);
    draw_explosions(game->level->explosion, game->rm);
    al_flip_display();
  }
}

void update_game_level(Game *game) {
  update_background(game);
  update_level(game->level);
  spawn_special_attack(game->player->special_attack);

  update_special_attack(game->player->special_attack);
  update_player(game->player);
  check_all_collisions(game->player, game->level);
  check_game_victory(game);

  if (game->player->health <= 0)
    game->state = GAME_STATE_GAME_OVER;

  render_game(game);
}

void update_transition(Game *game) {
  render_prephase(game->rm, game->state);
}

void update_game_state(Game *game) {
  switch (game->state) {
    case GAME_STATE_GAME_OVER:
      render_gameover(game->rm, game->state);
      break;

    case GAME_STATE_MENU:
      render_menu(game->rm, game->state);
      break;

    case GAME_STATE_LEVEL_ONE:
    case GAME_STATE_LEVEL_TWO:
      update_game_level(game);
      break;

    case GAME_STATE_TRANSITION:
      update_transition(game);
      break;

    case GAME_STATE_VICTORY:
      render_victory_screen(game->rm, game->state);
      break;
  }
}

void game_loop(Game *game) {
  ALLEGRO_EVENT event;
  while (game->is_running) {
    al_wait_for_event(game->queue, &event);

    switch (event.type) {
      case ALLEGRO_EVENT_TIMER:
        update_game_state(game);
        break;

      case ALLEGRO_EVENT_KEY_DOWN:
      case ALLEGRO_EVENT_KEY_UP:
        handleKeyPress(game, &event);
        break;

      case ALLEGRO_EVENT_DISPLAY_CLOSE:
        game->is_running = 0;
        break;
    }
  }
}

void game_run(Game *game) {
  srand(time(NULL));
  init_allegro();
  init_game(game);
  game_loop(game);
  deinit_game(game);
}