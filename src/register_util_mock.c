#ifndef __XC8
#include "register_util.h"

#include <stdio.h>

void init_ports() { fprintf(stderr, "init_ports\n"); }
void reset_ports() { fprintf(stderr, "reset_ports\n"); }

void fetch_ports(PortInfo_t *port_info) {
	fprintf(stderr, "fetch_ports\n");
	port_info->line_sensors = ~(1 << 2);
}

void dispatch_motor_state(unsigned char motor_state) {
	fprintf(stderr, "dispatch_motor_state\n");
}

#endif
