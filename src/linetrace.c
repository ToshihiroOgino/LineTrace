#include "linetrace.h"

int num_inverted = 0;
int sensor_bit_count_log[MAX_LOOP_TICK];

#define SIDE_NONE 0
#define SIDE_LEFT 1
#define SIDE_RIGHT 2
int prev_side = SIDE_NONE;

/**
 * @brief Count the bits of the sensor data to see if the majority is 1 or 0
 *
 * @param n sensor data
 * @return 1 if the sensor data is inverted, 0 otherwise
 */
int _is_inverted(int bit_count) { return bit_count >= 4; }

void _store_sensor_log(unsigned int line_sensors, LoopTick tick) {
	// Remove the previous loop tick's data from the count
	num_inverted -= _is_inverted(sensor_bit_count_log[tick]);

	int bit_count = 0;
	for (int i = 0; i < LINE_SENSOR_BITS; i++) {
		bit_count += ((line_sensors & (1 << i)) != 0);
	}
	sensor_bit_count_log[tick] = bit_count;
	num_inverted += _is_inverted(sensor_bit_count_log[tick]);
}

Move select_move(const PortInfo_t *port_info, LoopTick tick) {
	unsigned int line = port_info->line_sensors;
	_store_sensor_log(line, tick);

	if (num_inverted > (MAX_LOOP_TICK / 2)) {
		// When the sensor data is inverted for more than a majority of ticks,
		// treat 0 of the sensor data as a line detected.
		line = ~line & 0b11111;
	}

	Move move = MOVE_STRAIGHT;
	if (line == 0b00100 || line == 0b11011) {
		move = MOVE_STRAIGHT;
		prev_side = SIDE_NONE;
	} else if (line == 0b01110 || line == 0b10001) {
		move = MOVE_STRAIGHT_SLOW;
		prev_side = SIDE_NONE;
	} else if (line == 0b00001 || line == 0b00011 || line == 0b00111) {
		move = MOVE_RIGHT;
		prev_side = SIDE_RIGHT;
	} else if (line == 0b00010 || line == 0b00110) {
		move = MOVE_SMALL_RIGHT;
		prev_side = SIDE_RIGHT;
	} else if (line == 0b10000 || line == 0b11000 || line == 0b11100) {
		move = MOVE_LEFT;
		prev_side = SIDE_LEFT;
	} else if (line == 0b01100 || line == 0b01000) {
		move = MOVE_LEFT_SMALL;
		prev_side = SIDE_LEFT;
	} else if (line == 0b00000 || line == 0b11111) {
		// In case of no line detected, keep the previous side
		if (prev_side == SIDE_LEFT) {
			move = MOVE_LEFT_BIG;
			prev_side = SIDE_LEFT;
		} else if (prev_side == SIDE_RIGHT) {
			move = MOVE_RIGHT_BIG;
			prev_side = SIDE_RIGHT;
		} else {
			move = MOVE_STRAIGHT;
		}
	}

	return move;
}

#define MOTOR_OFF 0b00
#define MOTOR_RIGHT_ON 0b01
#define MOTOR_LEFT_ON 0b10
#define MOTOR_BOTH_ON 0b11

// If the tick is exceeds these values, stop the motors
const int straight_tick = 18;
const int straight_slow_tick = 12;

const int turn_tick = 10;
const int small_turn_tick = 8;
const int big_turn_tick = 15;

unsigned char generate_motor_state(Move move, LoopTick tick) {
	unsigned char motor = MOTOR_OFF;

	switch (move) {
	case MOVE_RIGHT:
	case MOVE_SMALL_RIGHT:
	case MOVE_RIGHT_BIG:
		motor = MOTOR_RIGHT_ON;
		break;

	case MOVE_LEFT:
	case MOVE_LEFT_SMALL:
	case MOVE_LEFT_BIG:
		motor = MOTOR_LEFT_ON;
		break;

	case MOVE_STRAIGHT:
		if (tick <= straight_tick) {
			motor = MOTOR_BOTH_ON;
		} else {
			motor = MOTOR_OFF;
		}
		return motor;

	case MOVE_STOP:
	default:
		motor = MOTOR_OFF;
		return motor;
	}

	if (move == MOVE_LEFT_SMALL || move == MOVE_SMALL_RIGHT) {
		if (tick > small_turn_tick) {
			motor = MOTOR_OFF;
		}
	} else if (move == MOVE_LEFT || move == MOVE_RIGHT) {
		if (tick > turn_tick) {
			motor = MOTOR_OFF;
		}
	} else if (move == MOVE_LEFT_BIG || move == MOVE_RIGHT_BIG) {
		if (tick > big_turn_tick) {
			motor = MOTOR_OFF;
		}
	}

	return motor;
}
