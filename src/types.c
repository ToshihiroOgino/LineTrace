#include "types.h"

void count_up(LoopTick *tick) {
	*tick = (*tick + 1) & MAX_LOOP_TICK;
}
