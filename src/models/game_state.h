#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "rigid_object.h"
#include <time.h>

typedef struct {
  RigidObject objects[1024];
  unsigned int nr_rigid_objects;

  // time this state was updated last
  struct timespec update_time;

  // frame counter
  unsigned long int frame_counter;
} GameState;

#endif // GAME_STATE_H