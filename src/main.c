#include <ncurses.h>
#include <time.h>
#include <unistd.h>

#include "models/game_state.h"
#include "models/rigid_object.h"

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

// target fps set to 60hz (in microseconds)
#define TARGET_FPS 30
#define TARGET_FRAME_TIME (1000000 / TARGET_FPS)

int main() {
  GameState game_state;

  // initialize game state
  clock_gettime(CLOCK_MONOTONIC, &game_state.update_time);

  RigidObject obj;
  obj.altitude = 1000.0f;
  obj.velocity = 50.0f;
  obj.mass = 75.0f;
  obj.gravity = -9.81f;

  game_state.frame_counter = 0;
  game_state.objects[0] = obj;
  game_state.nr_rigid_objects = 1;

  // initialize ncurses (terminal renderer)
  initscr();

  // enter game loop
  while (true) {
    struct timespec frame_start;
    clock_gettime(CLOCK_MONOTONIC, &frame_start);

    // update game state for current time
    update(&game_state, frame_start);

    // render the current game state
    render(&game_state);

    struct timespec frame_end;
    clock_gettime(CLOCK_MONOTONIC, &frame_end);

    // calculate frame time (in microseconds)
    time_t frame_time = (frame_end.tv_sec - frame_start.tv_sec) * 1000.0 +
                        (frame_end.tv_nsec - frame_start.tv_nsec) / 1000.0;

    // wait for short time to maintain target fps
    if (frame_time < TARGET_FRAME_TIME)
      usleep(TARGET_FRAME_TIME - frame_time);
  }

  // cleanup ncurses (terminal renderer)
  endwin();

  return 0;
}
