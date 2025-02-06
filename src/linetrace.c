#include "linetrace.h"

Move select_move(const PortInfo_t *port_info) {
	unsigned int line = port_info->line_sensors;

#if LINE == 0
	line = ~line & 0b11111;
#endif

	Move move = MOVE_STOP;

	if (line == 0b11111) {
		move = MOVE_STOP;
	} else if (line == 0b00100 || line == 0b01110) {
		move = MOVE_STRAIGHT;
	} else if ((line & 0b00001) != 0) {
		move = MOVE_RIGHT;
	} else if (line == 0b00110 || line == 0b00010) {
		move = MOVE_SMALL_RIGHT;
	} else if ((line & 0b10000) != 0) {
		move = MOVE_LEFT;
	} else if (line == 0b01100 || line == 0b01000) {
		move = MOVE_SMALL_LEFT;
	}

	return move;
}
