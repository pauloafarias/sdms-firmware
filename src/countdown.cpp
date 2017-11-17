#include <stdbool.h>

#include "../lib/countdown.h"

#include <Arduino.h>
#include "../lib/nbtasks.h"

bool countdown_flag_break;
bool countdown_flag_complete;

unsigned long countdown_tick;
unsigned long countdown_millis;
unsigned long countdown_timeout;

nbtask countdown = { "COUNTDOWN", countdown_act };
nbtask * countdown_callback;

void countdown_setup(unsigned long timeout, nbtask * callback) {

	countdown_timeout = timeout;
	countdown_tick = 0;
	countdown_millis = millis();
	countdown_flag_break = false;
	countdown_flag_complete = false;

	if (callback != NULL) countdown_callback = callback;

	task_cbuff_insert(countdown);

}

void countdown_break(nbtask * callback) {

	if (!countdown_flag_complete) countdown_flag_break = true;

	task_cbuff_insert(*callback);

}

void countdown_act(void) {

	if (!countdown_flag_break && !countdown_flag_complete ) {

		if (countdown_millis + 1000 < millis()) {
			countdown_millis = millis();
			countdown_tick++;
			// Serial.println(countdown_tick);
		}

		if (countdown_tick < countdown_timeout) {
			task_cbuff_insert(countdown);
		} else {
			countdown_flag_complete = true;
			task_cbuff_insert(*countdown_callback);
		}

	}

}
