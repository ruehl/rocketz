#include <ncurses.h>
#include <time.h>

#include "game_loop.h"
#include "game_state.h"
#include "rigid_object.h"

// target fps set to 60hz (in nanoseconds)
#define TARGET_FPS 30
#define TARGET_FRAME_TIME (1000000000 / TARGET_FPS)

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

    // calculate frame time
    struct timespec frame_time;
    frame_time.tv_sec = frame_end.tv_sec - frame_start.tv_sec;
    frame_time.tv_nsec = frame_end.tv_nsec - frame_start.tv_nsec;

    // calculate remaining time left in current frame
    struct timespec remaining_time;
    remaining_time.tv_sec = -frame_time.tv_sec;
    remaining_time.tv_nsec = TARGET_FRAME_TIME - frame_time.tv_nsec;

    // wait for short time to maintain target fps
    if (remaining_time.tv_sec >= 0 && remaining_time.tv_nsec > 0) {
      nanosleep(&remaining_time, NULL);
    }
  }

  // cleanup ncurses (terminal renderer)
  endwin();

  return 0;
}
