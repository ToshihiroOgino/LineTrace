#ifndef TYPES_H_
#define TYPES_H_

// MAX_LOOP_TICK: 32
#define MAX_LOOP_TICK (1 << 5)
#define MAX_LOOP_TICK_MASK (MAX_LOOP_TICK - 1)

typedef unsigned int LoopTick;
void countup(LoopTick *tick);

#define LINE_SENSOR_BITS 5
typedef struct {
	/** line sensor values(5bit)
	 * 0b0000x: RB0 Right
	 * 0b000x0: RB1
	 * 0b00x00: RB2 Center
	 * 0b0x000: RB3
	 * 0bx0000: RB4 Left
	 */
	unsigned line_sensors : LINE_SENSOR_BITS;
} PortInfo_t;

typedef enum {
	MOVE_STOP,
	MOVE_STRAIGHT,
	MOVE_STRAIGHT_SLOW,
	MOVE_RIGHT,
	MOVE_SMALL_RIGHT,
	MOVE_RIGHT_BIG,
	MOVE_LEFT,
	MOVE_LEFT_SMALL,
	MOVE_LEFT_BIG,
} Move;

#endif /* TYPES_H_ */
