#ifndef NBTASKS_H_
#define NBTASKS_H_

#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

#include <Arduino.h>

//#include "../cbuff/CircularBuffer.h.na"


typedef void (* nbtask_action) (void);

typedef struct nbtask_struct {
	String name;
	nbtask_action act;
} nbtask;

#define TASK_CBUFF_DEFAULT_SIZE 32

extern nbtask task_cbuff[TASK_CBUFF_DEFAULT_SIZE];

extern uint16_t task_cbuff_head;
extern uint16_t task_cbuff_tail;

void task_cbuff_setup(void);
void task_cbuff_insert(nbtask);
void task_cbuff_play(void);

#endif
