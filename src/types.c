#include "types.h"

void countup(LoopTick *tick) { *tick = (*tick + 1) & MAX_LOOP_TICK_MASK; }
