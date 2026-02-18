#ifndef __JOYSTICK__
#define __JOYSTICK__

typedef struct Joystick {
  unsigned char up;
  unsigned char down;
  unsigned char left;
  unsigned char right;
  unsigned char fire;
  unsigned char special;
} Joystick;

Joystick* create_joystick();

void destroy_joystick(Joystick* j);

void update_joystick_right(Joystick* j);

void update_joystick_left(Joystick* j);

void update_joystick_up(Joystick* j);

void update_joystick_down(Joystick* j);

void update_joystick_fire(Joystick* j);

void update_joystick_special(Joystick* j);

#endif  // __JOYSTICK__