#include "../../includes/backend/special.h"

#include <stdlib.h>

#include "../../includes/config/config.h"
#include "../../includes/utils/utils.h"

Special *init_special() {
  Special *special = (Special *)malloc(sizeof(Special));
  must_init(special, "Special Attack");
  special->gun = create_gun(PLAYER);
  special->is_active = 0;
  special->on_map = 0;
  special->spawn_time = time(NULL);
  special->type = SPECIAL_GUN_TWO;
  return special;
}

void spawn_special_attack(Special *sp) {
  if (sp->on_map)  // se já está no mapa, não faz nada
    return;

  // verifica se já passou SPECIAL_SPAWN_TIMER segundos desde o último spawn
  if (difftime(time(NULL), sp->spawn_time) >= SPECIAL_SPAWN_TIMER) {
    sp->on_map = 1;
    sp->x = SCREEN_WIDTH + 100;
    sp->y = rand_between(30, 400);
    sp->burst_time = time(NULL);

    // alterna tipo e dano
    if (sp->type == SPECIAL_GUN_ONE) {
      sp->type = SPECIAL_GUN_TWO;
      sp->damage = 8;
    } else {
      sp->type = SPECIAL_GUN_ONE;
      sp->damage = 4;
    }

    // atualiza o tempo do último spawn
    sp->spawn_time = time(NULL);
  }
}

void update_special_attack(Special *sp) {
  if (sp->is_active && difftime(time(NULL), sp->burst_time) >= 10) {
    sp->is_active = 0;
    return;
  }

  if (!sp->on_map)
    return;

  sp->x -= SPECIAL_ITEM_SPEED;
  if (sp->x <= 0) {
    sp->on_map = 0;  // Remove o especial do mapa
    return;
  }
}

void destroy_special_attack(Special *sp) {
  free(sp->gun);
  free(sp);
}