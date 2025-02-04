#ifndef EMULATE_H_
#define EMULATE_H_

void init_ports();
void reset_ports();

typedef struct {
	/** line sensor values(5bit)
	 * 0b0000x: RB0 Right
	 * 0b000x0: RB1
	 * 0b00x00: RB2 Center
	 * 0b0x000: RB3
	 * 0bx0000: RB4 Left
	 */
	unsigned line_sensors : 5;
} PortInfo_t;
void fetch_ports(PortInfo_t *port_info);

#endif /* EMULATE_H_ */
