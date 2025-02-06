#ifdef __XC8
#include "register_util.h"

#include "types.h"
#include <xc.h>

#include <pic18f25k50.h>

void init_ports() {
	// setting digital ports
	ADCON1 = 0x0F;

	// Input: B
	// Output: A, C
	TRISA = 0x00;
	TRISB = 0xFF;
	TRISC = 0x00;

	PORTA = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
}

void reset_ports() {
	PORTA &= 0xe0;
	PORTA |= (PORTB & 0x1f);
}

void fetch_ports(PortInfo_t *port_info) {
	port_info->line_sensors = PORTBbits.RB0 | (PORTBbits.RB1 << 1) |
	                          (PORTBbits.RB2 << 2) | (PORTBbits.RB3 << 3) |
	                          (PORTBbits.RB4 << 4);
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

void dispatch_move(Move move, LoopTick tick) {
	unsigned char motor = MOTOR_OFF;

	switch (move) {
	case MOVE_STOP:
	default:
		LATC = MOTOR_OFF;
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

	LATC = motor;
}

#endif
