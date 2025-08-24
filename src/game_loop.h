#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "game_state.h"

void update(GameState *state, struct timespec current_time);
void render(GameState *state);

#endif // GAME_LOOP_H