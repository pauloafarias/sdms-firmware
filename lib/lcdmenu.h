#ifndef LCDMENU_H_
#define LCDMENU_H_

#include <LiquidCrystal.h>
#include "nbtasks.h"

typedef void ( *MenuNodeFunction ) (void) ;

#define LCD_MENU_N_TYPES (4);

typedef enum MenuNodeValueType_enum {
	MENU_NODE_VALUE_TYPE_MIXED = 0,
	MENU_NODE_VALUE_TYPE_BOOLEAN = 1,
	MENU_NODE_VALUE_TYPE_INTEGER = 2,
	MENU_NODE_VALUE_TYPE_DOUBLE = 3
} MenuNodeValueType;

typedef union MenuNodeValue_union {
	double _double;
	int _int;
	bool _bool;
	void * _voidptr;
} MenuNodeValue;

typedef struct MenuNode_struct {

	char * displayText;
	char * displayTextAlternate;

	struct MenuNode_struct * prev, * next, * up, * down;

	MenuNodeValue value;
	MenuNodeValue valueLimMax;
	MenuNodeValue valueLimMin;
	MenuNodeValueType type;
	char * unit;

	nbtask task;

	bool editing;

} MenuNode;

extern MenuNode root, * mn_current, * mn_draw;
extern bool mn_flag_editing_lock;
extern bool mn_flag_scroll_lock;

extern LiquidCrystal _display;

void lcdmenu_setup(void);
extern nbtask lcdmenu_draw;

#endif
