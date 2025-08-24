#include <ncurses.h>
#include <time.h>
#include <unistd.h>

#include "models/rigid_object.h"

void update(unsigned int dt) {
	
}

int main() {
	RigidObject obj;
	obj.altitude = 1000.0f;
	obj.velocity = 50.0f;
	obj.mass = 75.0f;
	obj.gravity = 9.81f;

	struct timespec last_time;
	clock_gettime(CLOCK_MONOTONIC, &last_time);

	initscr();

	while(true) {
		// update delta time
		struct timespec current_time;
		clock_gettime(CLOCK_MONOTONIC, &current_time);
		unsigned int dt = (current_time.tv_sec - last_time.tv_sec) * 1000 + (current_time.tv_nsec - last_time.tv_nsec) / 1000000;

		// update game state for given dt
		update(dt);
		last_time = current_time;

		clear();
		printw("%d", dt);
		refresh();

		// wait for short time to achieve a fps of 60hz
		usleep(16667);
	}
    
	endwin();

	return 0;
}
