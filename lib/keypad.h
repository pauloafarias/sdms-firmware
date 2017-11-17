#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <stdlib.h>
#include <stdbool.h>

#include "nbtasks.h"

#define KEYPAD_N_COLS (4)
#define KEYPAD_N_ROWS (4)
#define KEYPAD_ROWS {33, 34, 35, 36}
#define KEYPAD_COLS {37, 38, 39, 40}


/**
 * Setup keypad row and col pins.
 */
void keypad_setup();

extern nbtask keypad_scan;

#endif
