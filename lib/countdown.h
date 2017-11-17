#ifndef COUNTDOWN_H_
#define COUNTDOWN_H_

#include "nbtasks.h"

void countdown_setup(unsigned long timeout, nbtask * callback);
void countdown_break(nbtask *);
void countdown_act(void);

#endif
