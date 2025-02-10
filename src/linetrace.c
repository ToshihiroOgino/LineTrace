#include "linetrace.h"

int num_inverted = 0;
int sensor_bit_count_log[MAX_LOOP_TICK];

/**
 * @brief Count the bits of the sensor data to see if the majority is 1 or 0
 *
 * @param n sensor data
 * @return 1 if the sensor data is inverted, 0 otherwise
 */
int _is_inverted(int bit_count) { return bit_count > (LINE_SENSOR_BITS / 2); }

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

	Move move = MOVE_STOP;

	if (line == 0b00100 || line == 0b01110 || line == 0b10001 ||
	    line == 0b11011 || line == 0b00000 || line == 0b11111) {
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
