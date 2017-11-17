#include "../lib/lcdmenu.h"

#include <Arduino.h>
#include "../lib/keypad.h"
#include "../lib/nbtasks.h"

MenuNode * mn_current, * mn_draw;

void lcdmenu_draw_act(void);
void lcdmenu_draw_boolean_act(void);
void lcdmenu_draw_double_act(void);
void lcdmenu_draw_integer_act(void);
void lcdmenu_draw_mixed_act(void);

void lcdmenu_backtoflow_act(void);

nbtask lcdmenu_draw_tasklist[4];
nbtask lcdmenu_draw;

bool mn_flag_editing_lock;
bool mn_flag_scroll_lock;

void lcdmenu_setup (void) {

	_display.begin(16,2);

	mn_current = &root;
	mn_flag_editing_lock = false;
	mn_flag_scroll_lock = false;

	lcdmenu_draw_tasklist[MENU_NODE_VALUE_TYPE_BOOLEAN].act = lcdmenu_draw_boolean_act;
	lcdmenu_draw_tasklist[MENU_NODE_VALUE_TYPE_BOOLEAN].name = "LCDMENU_DRAW_BOOLEAN";

	lcdmenu_draw_tasklist[MENU_NODE_VALUE_TYPE_DOUBLE].act = lcdmenu_draw_double_act;
	lcdmenu_draw_tasklist[MENU_NODE_VALUE_TYPE_DOUBLE].name = "LCDMENU_DRAW_DOUBLE";

	lcdmenu_draw_tasklist[MENU_NODE_VALUE_TYPE_INTEGER].act = lcdmenu_draw_integer_act;
	lcdmenu_draw_tasklist[MENU_NODE_VALUE_TYPE_INTEGER].name = "LCDMENU_DRAW_INTEGER";

	lcdmenu_draw_tasklist[MENU_NODE_VALUE_TYPE_MIXED].act = lcdmenu_draw_mixed_act;
	lcdmenu_draw_tasklist[MENU_NODE_VALUE_TYPE_MIXED].name = "LCDMENU_DRAW_MIXED";

	lcdmenu_draw.act = lcdmenu_draw_act;
	lcdmenu_draw.name = "LCDMENU_DRAW";

	task_cbuff_insert(lcdmenu_draw);

}

void lcdmenu_draw_act (void) {

	_display.clear();
	_display.setCursor(0,0);

	if (mn_current->editing == true) _display.print("#");
	else _display.print("*");

	mn_draw = mn_current;
	lcdmenu_draw_tasklist[mn_draw->type].act();

	if ( mn_current->next != NULL ) {
		_display.setCursor(0,1);
		_display.print(" ");
		mn_draw = mn_current->next;
		lcdmenu_draw_tasklist[mn_draw->type].act();
	}

}

void lcdmenu_draw_boolean_act (void) {

	if (mn_draw->value._bool == false) _display.print(mn_draw->displayText);
	else _display.print(mn_draw->displayTextAlternate);


}

void lcdmenu_draw_double_act (void) {

	_display.print(mn_draw->displayText);
	_display.print(" ");
	_display.print(mn_draw->value._double);
	_display.print(" ");
	_display.print(mn_draw->unit);

}

void lcdmenu_draw_integer_act (void) {

	_display.print(mn_draw->displayText);
	_display.print(" ");
	_display.print(mn_draw->value._int);
	_display.print(" ");
	_display.print(mn_draw->unit);

}

void lcdmenu_draw_mixed_act (void) {

	_display.print(mn_draw->displayText);
}

void lcdmenu_backtoflow_act (void) {

}
