#include "linetrace.h"

#define MASK 0x1f

Move select_move(const PortInfo_t *port_info) {
	unsigned int line = port_info->line_sensors;

	if (LINE == 0) {
		line = ~line & MASK;
	}

	if (line == 0b00100) {
	}

	return MOVE_STOP;
}
