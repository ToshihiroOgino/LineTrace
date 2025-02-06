#include "linetrace.h"
#include "register_util.h"
#include "types.h"

int main() {
	init_ports();
	PortInfo_t port_info;

	for (LoopTick tick = 0;; count_up(&tick)) {
		reset_ports();
		fetch_ports(&port_info);
		Move move = select_move(&port_info);
		dispatch_move(move, tick);
	}

	return 0;
}
