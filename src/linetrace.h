#ifndef LINETRACE_H_
#define LINETRACE_H_

#include "register_util.h"

/* If corse was inverted, flip bit this value. */
#define LINE 0

typedef enum {
	MOVE_STOP,
	MOVE_STRAIGHT,
	MOVE_LEFT,
	MOVE_RIGHT,
} Move;
Move select_move(const PortInfo_t *port_info);

#endif /* LINETRACE_H_ */
