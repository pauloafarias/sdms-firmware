#include "../lib/keypad.h"

#include <stdlib.h>
#include <Arduino.h>
#include "../lib/nbtasks.h"
#include "../lib/lcdmenu.h"

extern uint8_t keypad_colarray[KEYPAD_N_COLS];
extern uint8_t keypad_rowarray[KEYPAD_N_ROWS];

typedef enum keypad_key_status_enum {
	KEYPAD_KEY_RELEASED = 0,
	KEYPAD_KEY_PRESSED = 1
} keypad_key_status_t;

typedef struct keypad_key_struct {
	uint8_t col, row, colidx, rowidx;
	keypad_key_status_t status;
} keypad_key_t;

uint8_t keypad_colarray[KEYPAD_N_COLS] = KEYPAD_COLS;
uint8_t keypad_rowarray[KEYPAD_N_ROWS] = KEYPAD_ROWS;

keypad_key_t keypad_keypressed;

nbtask keypad_scan;
nbtask keytask[KEYPAD_N_COLS][KEYPAD_N_ROWS];

void keytask_1_act (void);
void keytask_2_act (void);
void keytask_3_act (void);
void keytask_4_act (void);
void keytask_5_act (void);
void keytask_6_act (void);
void keytask_7_act (void);
void keytask_8_act (void);
void keytask_9_act (void);
void keytask_0_act (void);
void keytask_asterisk_act (void);
void keytask_sharp_act (void);

void keypad_detect_keypress(void);
void keypad_detect_keyrelease(void);

void keypad_scan_act();


/**
 * Setup keypad row and col pins.
 */
void keypad_setup() {

	int i;

	for (i=0;i<KEYPAD_N_COLS;i++)
			pinMode(keypad_colarray[i], OUTPUT);

	for (i=0;i<KEYPAD_N_ROWS;i++)
			pinMode(keypad_rowarray[i], INPUT);

	keypad_keypressed.status = KEYPAD_KEY_RELEASED;

	keytask[0][0].act = keytask_1_act;
	keytask[0][0].name = "KEYPAD_KEYTASK_1";

	keytask[1][0].act = keytask_2_act;
	keytask[1][0].name = "KEYPAD_KEYTASK_2";

	keytask[2][0].act = keytask_3_act;
	keytask[2][0].name = "KEYPAD_KEYTASK_3";

	keytask[0][1].act = keytask_4_act;
	keytask[0][1].name = "KEYPAD_KEYTASK_4";

	keytask[1][1].act = keytask_5_act;
	keytask[1][1].name = "KEYPAD_KEYTASK_5";

	keytask[2][1].act = keytask_6_act;
	keytask[2][1].name = "KEYPAD_KEYTASK_6";

	keytask[0][2].act = keytask_7_act;
	keytask[0][2].name = "KEYPAD_KEYTASK_7";

	keytask[1][2].act = keytask_8_act;
	keytask[1][2].name = "KEYPAD_KEYTASK_8";

	keytask[2][2].act = keytask_9_act;
	keytask[2][2].name = "KEYPAD_KEYTASK_9";

	keytask[0][3].act = keytask_asterisk_act;
	keytask[0][3].name = "KEYPAD_KEYTASK_ASTERISK";

	keytask[1][3].act = keytask_0_act;
	keytask[1][3].name = "KEYPAD_KEYTASK_0";

	keytask[2][3].act = keytask_sharp_act;
	keytask[2][3].name = "KEYPAD_KEYTASK_SHARP";

	keypad_scan.act = keypad_scan_act;
	keypad_scan.name = "KEYPAD_SCAN";

	task_cbuff_insert(keypad_scan);

}

void keypad_scan_act() {

	if (keypad_keypressed.status == KEYPAD_KEY_RELEASED) {
		keypad_detect_keypress();

	} else if (keypad_keypressed.status == KEYPAD_KEY_PRESSED) {
		keypad_detect_keyrelease();

	}

}

void keypad_detect_keypress() {

	for (keypad_keypressed.colidx = 0; keypad_keypressed.colidx < KEYPAD_N_COLS; keypad_keypressed.colidx++) {

		digitalWrite(keypad_colarray[keypad_keypressed.colidx], HIGH);

		for (keypad_keypressed.rowidx = 0; keypad_keypressed.rowidx < KEYPAD_N_ROWS; keypad_keypressed.rowidx++) {

			if (digitalRead(keypad_rowarray[keypad_keypressed.rowidx]) == HIGH) {

				keypad_keypressed.status = KEYPAD_KEY_PRESSED;
				keypad_keypressed.row = keypad_rowarray[keypad_keypressed.rowidx];
				keypad_keypressed.col = keypad_colarray[keypad_keypressed.colidx];
				digitalWrite(keypad_colarray[keypad_keypressed.colidx], LOW);
				task_cbuff_insert(keypad_scan);
				return;

			}

		}

		digitalWrite(keypad_colarray[keypad_keypressed.colidx], LOW);

	}

	task_cbuff_insert(keypad_scan);

}

void keypad_detect_keyrelease(void) {

	digitalWrite(keypad_keypressed.col, HIGH);

	if (digitalRead(keypad_keypressed.row) == LOW) {
		keypad_keypressed.status = KEYPAD_KEY_RELEASED;
		task_cbuff_insert(keytask[keypad_keypressed.colidx][keypad_keypressed.rowidx]);
		task_cbuff_insert(lcdmenu_draw);
	}

	task_cbuff_insert(keypad_scan);

}

char keypad_tempvalue[10];
char * keypad_tempvalue_charbuffer;

int  keypad_tempvalue_lastidx;

void keytask_1_act (void) {


	if (mn_current->editing && mn_flag_editing_lock == false) {

		keypad_tempvalue[keypad_tempvalue_lastidx] = '1'; keypad_tempvalue_lastidx++;


		if (mn_current->type == MENU_NODE_VALUE_TYPE_DOUBLE) {

			mn_current->value._double = atof( keypad_tempvalue );
			if (mn_current->value._double > mn_current->valueLimMax._double ) mn_current->value = mn_current->valueLimMax;
			if (mn_current->value._double < mn_current->valueLimMin._double ) mn_current->value = mn_current->valueLimMin;
		}

		else if (mn_current->type == MENU_NODE_VALUE_TYPE_INTEGER) {

			mn_current->value._int = atoi( keypad_tempvalue );
			if (mn_current->value._int > mn_current->valueLimMax._int ) mn_current->value = mn_current->valueLimMax;
			if (mn_current->value._int < mn_current->valueLimMin._int ) mn_current->value = mn_current->valueLimMin;



		}

	}

};

void keytask_2_act (void) {

	if (mn_current->editing && mn_flag_editing_lock == false) {

		keypad_tempvalue[keypad_tempvalue_lastidx] = '2'; keypad_tempvalue_lastidx++;


		if (mn_current->type == MENU_NODE_VALUE_TYPE_DOUBLE) {

			mn_current->value._double = atof( keypad_tempvalue );
			if (mn_current->value._double > mn_current->valueLimMax._double ) mn_current->value = mn_current->valueLimMax;
			if (mn_current->value._double < mn_current->valueLimMin._double ) mn_current->value = mn_current->valueLimMin;
		}

		else if (mn_current->type == MENU_NODE_VALUE_TYPE_INTEGER) {

			mn_current->value._int = atoi( keypad_tempvalue );
			if (mn_current->value._int > mn_current->valueLimMax._int ) mn_current->value = mn_current->valueLimMax;
			if (mn_current->value._int < mn_current->valueLimMin._int ) mn_current->value = mn_current->valueLimMin;

		}

	} else if (mn_current->prev != NULL && mn_flag_scroll_lock == false) {
		mn_current = mn_current->prev;
	}

};

void keytask_3_act (void) {

	if (mn_current->editing && mn_flag_editing_lock == false) {

		keypad_tempvalue[keypad_tempvalue_lastidx] = '3'; keypad_tempvalue_lastidx++;


		if (mn_current->type == MENU_NODE_VALUE_TYPE_DOUBLE) {

			mn_current->value._double = atof( keypad_tempvalue );
			if (mn_current->value._double > mn_current->valueLimMax._double ) mn_current->value = mn_current->valueLimMax;
			if (mn_current->value._double < mn_current->valueLimMin._double ) mn_current->value = mn_current->valueLimMin;
		}

		else if (mn_current->type == MENU_NODE_VALUE_TYPE_INTEGER) {

			mn_current->value._int = atoi( keypad_tempvalue );
			if (mn_current->value._int > mn_current->valueLimMax._int ) mn_current->value = mn_current->valueLimMax;
			if (mn_current->value._int < mn_current->valueLimMin._int ) mn_current->value = mn_current->valueLimMin;

		}

	}

};
void keytask_4_act (void) {

	if (mn_current->editing && mn_flag_editing_lock == false) {

		keypad_tempvalue[keypad_tempvalue_lastidx] = '4'; keypad_tempvalue_lastidx++;


		if (mn_current->type == MENU_NODE_VALUE_TYPE_DOUBLE) {

			mn_current->value._double = atof( keypad_tempvalue );
			if (mn_current->value._double > mn_current->valueLimMax._double ) mn_current->value = mn_current->valueLimMax;
			if (mn_current->value._double < mn_current->valueLimMin._double ) mn_current->value = mn_current->valueLimMin;
		}

		else if (mn_current->type == MENU_NODE_VALUE_TYPE_INTEGER) {

			mn_current->value._int = atoi( keypad_tempvalue );
			if (mn_current->value._int > mn_current->valueLimMax._int ) mn_current->value = mn_current->valueLimMax;
			if (mn_current->value._int < mn_current->valueLimMin._int ) mn_current->value = mn_current->valueLimMin;

		}

	}

};
void keytask_5_act (void) {

	if (mn_current->editing && mn_flag_editing_lock == false) {

		keypad_tempvalue[keypad_tempvalue_lastidx] = '5'; keypad_tempvalue_lastidx++;


		if (mn_current->type == MENU_NODE_VALUE_TYPE_DOUBLE) {

			mn_current->value._double = atof( keypad_tempvalue );
			if (mn_current->value._double > mn_current->valueLimMax._double ) mn_current->value = mn_current->valueLimMax;
			if (mn_current->value._double < mn_current->valueLimMin._double ) mn_current->value = mn_current->valueLimMin;
		}

		else if (mn_current->type == MENU_NODE_VALUE_TYPE_INTEGER) {

			mn_current->value._int = atoi( keypad_tempvalue );
			if (mn_current->value._int > mn_current->valueLimMax._int ) mn_current->value = mn_current->valueLimMax;
			if (mn_current->value._int < mn_current->valueLimMin._int ) mn_current->value = mn_current->valueLimMin;

		}

	}

	if (mn_current->task.act != NULL && mn_current->task.name != NULL)
		task_cbuff_insert(mn_current->task);

};
void keytask_6_act (void) {

	if (mn_current->editing && mn_flag_editing_lock == false) {

		keypad_tempvalue[keypad_tempvalue_lastidx] = '6'; keypad_tempvalue_lastidx++;


		if (mn_current->type == MENU_NODE_VALUE_TYPE_DOUBLE) {

			mn_current->value._double = atof( keypad_tempvalue );
			if (mn_current->value._double > mn_current->valueLimMax._double ) mn_current->value = mn_current->valueLimMax;
			if (mn_current->value._double < mn_current->valueLimMin._double ) mn_current->value = mn_current->valueLimMin;
		}

		else if (mn_current->type == MENU_NODE_VALUE_TYPE_INTEGER) {

			mn_current->value._int = atoi( keypad_tempvalue );
			if (mn_current->value._int > mn_current->valueLimMax._int ) mn_current->value = mn_current->valueLimMax;
			if (mn_current->value._int < mn_current->valueLimMin._int ) mn_current->value = mn_current->valueLimMin;

		}

	}

};
void keytask_7_act (void) {

	if (mn_current->editing && mn_flag_editing_lock == false) {

		keypad_tempvalue[keypad_tempvalue_lastidx] = '7'; keypad_tempvalue_lastidx++;

		if (mn_current->type == MENU_NODE_VALUE_TYPE_DOUBLE) {

			mn_current->value._double = atof( keypad_tempvalue );
			if (mn_current->value._double > mn_current->valueLimMax._double ) mn_current->value = mn_current->valueLimMax;
			if (mn_current->value._double < mn_current->valueLimMin._double ) mn_current->value = mn_current->valueLimMin;
		}

		else if (mn_current->type == MENU_NODE_VALUE_TYPE_INTEGER) {

			mn_current->value._int = atoi( keypad_tempvalue );
			if (mn_current->value._int > mn_current->valueLimMax._int ) mn_current->value = mn_current->valueLimMax;
			if (mn_current->value._int < mn_current->valueLimMin._int ) mn_current->value = mn_current->valueLimMin;
		}

	}

};
void keytask_8_act (void) {

	if (mn_current->editing && mn_flag_editing_lock == false) {

		keypad_tempvalue[keypad_tempvalue_lastidx] = '8'; keypad_tempvalue_lastidx++;

		if (mn_current->type == MENU_NODE_VALUE_TYPE_DOUBLE) {

			mn_current->value._double = atof( keypad_tempvalue );
			if (mn_current->value._double > mn_current->valueLimMax._double ) mn_current->value = mn_current->valueLimMax;
			if (mn_current->value._double < mn_current->valueLimMin._double ) mn_current->value = mn_current->valueLimMin;
		}

		else if (mn_current->type == MENU_NODE_VALUE_TYPE_INTEGER) {

			mn_current->value._int = atoi( keypad_tempvalue );
			if (mn_current->value._int > mn_current->valueLimMax._int ) mn_current->value = mn_current->valueLimMax;
			if (mn_current->value._int < mn_current->valueLimMin._int ) mn_current->value = mn_current->valueLimMin;

		}

	} else if (mn_current->next != NULL && mn_flag_scroll_lock == false) {
		mn_current = mn_current->next;
	}
};
void keytask_9_act (void) {

	if (mn_current->editing && mn_flag_editing_lock == false) {

		keypad_tempvalue[keypad_tempvalue_lastidx] = '9'; keypad_tempvalue_lastidx++;

		if (mn_current->type == MENU_NODE_VALUE_TYPE_DOUBLE) {

			mn_current->value._double = atof( keypad_tempvalue );
			if (mn_current->value._double > mn_current->valueLimMax._double ) mn_current->value = mn_current->valueLimMax;
			if (mn_current->value._double < mn_current->valueLimMin._double ) mn_current->value = mn_current->valueLimMin;
		}

		else if (mn_current->type == MENU_NODE_VALUE_TYPE_INTEGER) {

			mn_current->value._int = atoi( keypad_tempvalue );
			if (mn_current->value._int > mn_current->valueLimMax._int ) mn_current->value = mn_current->valueLimMax;
			if (mn_current->value._int < mn_current->valueLimMin._int ) mn_current->value = mn_current->valueLimMin;

		}

	}
};
void keytask_0_act (void) {

	if (mn_current->editing && mn_flag_editing_lock == false) {

		keypad_tempvalue[keypad_tempvalue_lastidx] = '0'; keypad_tempvalue_lastidx++;

		if (mn_current->type == MENU_NODE_VALUE_TYPE_DOUBLE) {

			mn_current->value._double = atof( keypad_tempvalue );
			if (mn_current->value._double > mn_current->valueLimMax._double ) mn_current->value = mn_current->valueLimMax;
			if (mn_current->value._double < mn_current->valueLimMin._double ) mn_current->value = mn_current->valueLimMin;
		}

		else if (mn_current->type == MENU_NODE_VALUE_TYPE_INTEGER) {

			mn_current->value._int = atoi( keypad_tempvalue );
			if (mn_current->value._int > mn_current->valueLimMax._int ) mn_current->value = mn_current->valueLimMax;
			if (mn_current->value._int < mn_current->valueLimMin._int ) mn_current->value = mn_current->valueLimMin;

		}

	}
};
void keytask_asterisk_act (void) {

	if (mn_current->editing == true) {

		mn_current->editing = false;
	}

	if (mn_current->up != NULL)

		mn_current = mn_current->up;

};

void keytask_sharp_act (void) {
	if (mn_current->editing) {

		keypad_tempvalue[keypad_tempvalue_lastidx] = '.'; keypad_tempvalue_lastidx++;


		if (mn_current->type == MENU_NODE_VALUE_TYPE_DOUBLE) {

			mn_current->value._double = atof( keypad_tempvalue );
			if (mn_current->value._double > mn_current->valueLimMax._double ) mn_current->value = mn_current->valueLimMax;
			if (mn_current->value._double < mn_current->valueLimMin._double ) mn_current->value = mn_current->valueLimMin;

		}

		} else {

			switch(mn_current->type) {
			case MENU_NODE_VALUE_TYPE_MIXED:
				if (mn_current->down != NULL) {
					mn_current = mn_current->down;
				}
				break;
			case MENU_NODE_VALUE_TYPE_BOOLEAN:
				mn_current->value._bool = !mn_current->value._bool;
				break;
			default:
				keypad_tempvalue_lastidx = 0;
				for (int i=0; i < 10; i++) keypad_tempvalue[i] = '\0';
				mn_current->editing = true;
				break;
			}

			task_cbuff_insert(mn_current->task);

		}

};
