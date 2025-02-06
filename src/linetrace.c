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

#define MOTOR_OFF 0b00
#define MOTOR_RIGHT_ON 0b01
#define MOTOR_LEFT_ON 0b10
#define MOTOR_BOTH_ON 0b11

// If the tick is exceeds straight_tick, stop the motors
const int straight_tick = MAX_LOOP_TICK / 2;

// If the tick is exceeds turn_tick or small_turn_tick, go straight
const int turn_tick = straight_tick / 2;
const int small_turn_tick = straight_tick / 4;

unsigned char generate_motor_state(Move move, LoopTick tick) {
	unsigned char motor = MOTOR_OFF;

	switch (move) {
	case MOVE_STOP:
	default:
		motor = MOTOR_OFF;
		break;

	case MOVE_RIGHT:
	case MOVE_SMALL_RIGHT:
		motor = MOTOR_RIGHT_ON;
		break;

	case MOVE_LEFT:
	case MOVE_SMALL_LEFT:
		motor = MOTOR_LEFT_ON;
		break;

	case MOVE_STRAIGHT:
		motor = MOTOR_BOTH_ON;
		break;
	}

	if (
	    // In case small turn, if tick exceeds small_turn_tick
	    ((move == MOVE_SMALL_LEFT || move == MOVE_SMALL_RIGHT) &&
	     tick > small_turn_tick) ||
	    // In case normal turn, if tick exceeds turn_tick
	    ((move == MOVE_LEFT || move == MOVE_RIGHT) && tick > turn_tick)) {
		// Just go straight
		motor = MOTOR_BOTH_ON;
	}

	if (tick > straight_tick) {
		// Stop motors if the tick exceeds the limit (half of MAX_LOOP_TICK)
		// This is performed to slow down the speed
		motor = MOTOR_OFF;
	}

	return motor;
}
