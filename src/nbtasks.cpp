#include "../lib/nbtasks.h"

const bool debugging = false;

nbtask task_cbuff[TASK_CBUFF_DEFAULT_SIZE];
uint16_t task_cbuff_head;
uint16_t task_cbuff_tail;

void task_cbuff_setup() {
	task_cbuff_head = 0;
	task_cbuff_tail = 0;
}

void task_cbuff_play() {

	delay(10);

	if(task_cbuff_tail != task_cbuff_head) {

		if (debugging) {

			Serial.print("PLAYING: ");

			//Serial.print("Current Head: ");
			//Serial.println(task_cbuff_head);

			//Serial.print("Current Tail: ");
			//Serial.println(task_cbuff_tail);

			if (task_cbuff[task_cbuff_tail].name != NULL)
				Serial.println(task_cbuff[task_cbuff_tail].name);

		}

		if (task_cbuff[task_cbuff_tail].act != NULL)
			task_cbuff[task_cbuff_tail].act();

		// Increment tail of tasks circular buffer
		if ( (task_cbuff_tail + 1) < TASK_CBUFF_DEFAULT_SIZE ) {
			task_cbuff_tail ++;
		} else task_cbuff_tail = 0;

		if (debugging) {

			Serial.println("PLAYED!");

			//Serial.print("Current Head: ");
			//Serial.println(task_cbuff_head);

			//Serial.print("Current Tail: ");
			//Serial.println(task_cbuff_tail);

		}

	}

}

void task_cbuff_insert(nbtask tsk) {

	if (debugging) {

		Serial.print("INSERTING: ");

		if (tsk.name != NULL)
			Serial.println(tsk.name);

	}

	if (tsk.act != NULL) {

		task_cbuff[task_cbuff_head] = tsk;

		if ( (task_cbuff_head + 1) < TASK_CBUFF_DEFAULT_SIZE ) task_cbuff_head ++;
		else task_cbuff_head = 0;

	}


}
