#include "game_state.h"
#include <ncurses.h>

void update(GameState *state, struct timespec current_time) {
  // calculate delta time from state and current time
  // double dt = (current_time.tv_sec - state->update_time.tv_sec) * 1000 +
  //             (current_time.tv_nsec - state->update_time.tv_nsec) / 1000000;

  // remember the current update time in state
  state->update_time = current_time;

  // increase frame counter
  state->frame_counter++;
}

void render(GameState *state) {
  clear();
  printw("%lu / %lu", state->update_time.tv_sec, state->frame_counter);
  refresh();
}
