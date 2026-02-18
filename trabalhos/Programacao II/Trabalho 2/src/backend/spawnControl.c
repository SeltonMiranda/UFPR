#include "../../includes/backend/spawnControl.h"

#include "../../includes/config/config.h"
#include "../../includes/utils/utils.h"

SpawnControl *create_spawn_control(ENEMY_TYPE type, int quantity) {
  SpawnControl *_SpawnControl = (SpawnControl *)malloc(sizeof(SpawnControl));
  must_init(_SpawnControl, "SpawnControl");

  _SpawnControl->enemies = create_enemy(type, quantity);
  _SpawnControl->total = quantity;
  _SpawnControl->spawned = 0;
  _SpawnControl->batch_size = BATCH;
  _SpawnControl->last_spawn_time = time(NULL);

  switch (type) {
    case ENEMY_1:
      _SpawnControl->interval = ENEMY_ONE_SPAWN_INTERVAL;
      break;

    case ENEMY_2:
      _SpawnControl->interval = ENEMY_TWO_SPAWN_INTERVAL;
      break;

    case ENEMY_3:
      _SpawnControl->interval = ENEMY_THREE_SPAWN_INTERVAL;
      break;

    case ENEMY_4:
      _SpawnControl->interval = ENEMY_FOUR_SPAWN_INTERVAL;
      break;
  }

  return _SpawnControl;
}

void update_spawn_control(SpawnControl *_SpawnControl) {
  time_t current_time = time(NULL);
  if (difftime(current_time, _SpawnControl->last_spawn_time) >=
      _SpawnControl->interval) {
    int to_spawn = (_SpawnControl->spawned + _SpawnControl->batch_size >
                    _SpawnControl->total)
                       ? _SpawnControl->total - _SpawnControl->spawned
                       : _SpawnControl->batch_size;

    _SpawnControl->spawned += to_spawn;
    _SpawnControl->last_spawn_time = current_time;
  }
}

void destroy_spawn_control(SpawnControl *control) {
  destroy_enemy(control->enemies, control->total);
  free(control);
}