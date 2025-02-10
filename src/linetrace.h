#ifndef LINETRACE_H_
#define LINETRACE_H_

#include "register_util.h"
#include "types.h"

Move select_move(const PortInfo_t *port_info, LoopTick tick);
unsigned char generate_motor_state(Move move, LoopTick tick);

#endif /* LINETRACE_H_ */
