#include "register_util.h"
#include "linetrace.h"

#define LOOP_TICK_MAX 31

int main() {
	init_ports();
	PortInfo_t port_info;

	int loop_tick = 0;
	for (loop_tick = 0;; loop_tick = (loop_tick + 1) & LOOP_TICK_MAX) {
		reset_ports();
		fetch_ports(&port_info);
		select_move(&port_info);
		break;
	}


	return 0;
}
