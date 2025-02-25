#include "linetrace.h"
#include "register_util.h"
#include "types.h"

#ifndef __XC8
#include <stdio.h>
#endif

int main() {
	init_ports();
	PortInfo_t port_info;

	for (LoopTick tick = 0;; countup(&tick)) {
		reset_ports();
		fetch_ports(&port_info);
		Move move = select_move(&port_info, tick);
		unsigned char motor_state = generate_motor_state(move, tick);
		dispatch_motor_state(motor_state);
	}

	return 0;
}
