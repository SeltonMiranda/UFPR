#include "../../includes/backend/joystick.h"

#include <stdlib.h>

#include "../../includes/utils/utils.h"

Joystick* create_joystick() {
  Joystick* j = (Joystick*)malloc(sizeof(Joystick));
  must_init(j, "Joystick");
  j->up = 0;
  j->down = 0;
  j->right = 0;
  j->left = 0;
  j->fire = 0;
  j->special = 0;

  return j;
}

void destroy_joystick(Joystick* j) {
  free(j);
}

void update_joystick_right(Joystick* j) {
  j->right = j->right ^ 1;
}

void update_joystick_left(Joystick* j) {
  j->left = j->left ^ 1;
}

void update_joystick_up(Joystick* j) {
  j->up = j->up ^ 1;
}

void update_joystick_down(Joystick* j) {
  j->down = j->down ^ 1;
}

void update_joystick_fire(Joystick* j) {
  j->fire = j->fire ^ 1;
}

void update_joystick_special(Joystick* j) {
  j->special = j->special ^ 1;
}