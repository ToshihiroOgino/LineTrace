#ifndef LINETRACE_H_
#define LINETRACE_H_

#include "register_util.h"
#include "types.h"

// If corse was inverted, flip bit this value.
#define LINE 1

Move select_move(const PortInfo_t *port_info);
unsigned char generate_motor_state(Move move, LoopTick tick);

#endif /* LINETRACE_H_ */
