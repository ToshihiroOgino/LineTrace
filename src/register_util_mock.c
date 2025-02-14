#ifndef __XC8
#include "register_util.h"

#include <stdio.h>
#include <stdlib.h>

int count = 0;
int sensor_data[3 * MAX_LOOP_TICK];

void init_ports() {
	// fprintf(stderr, "init_ports\n");
	count = 0;
	for (int i = 0; i < MAX_LOOP_TICK; i++) {
		sensor_data[i] = 0b00000;
	}
	for (int i = 0; i < 2 * MAX_LOOP_TICK; i++) {
		sensor_data[i + MAX_LOOP_TICK] = 0b00110;
	}
}
void reset_ports() {
	// fprintf(stderr, "reset_ports\n");
}

void fetch_ports(PortInfo_t *port_info) {
	fprintf(stderr, "fetch_ports\n");
	port_info->line_sensors = sensor_data[count];
	count++;
	if (count >= 3 * MAX_LOOP_TICK) {
		count = 0;
		exit(0);
	}
}

void dispatch_motor_state(unsigned char motor_state) {
	// fprintf(stderr, "dispatch_motor_state\n");
}

#endif
