#ifdef __arm__
#include "register_util.h"

#include "types.h"
#include <pigpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define INPUT_PINS                                                             \
	{ 17, 27, 22, 23, 24 }
#define OUTPUT_PINS                                                            \
	{ 5, 6 }

void init_ports() {
	int input_pins[] = INPUT_PINS;
	int output_pins[] = OUTPUT_PINS;

	if (gpioInitialise() < 0) {
		fprintf(stderr, "failed to initialize gpio\n");
		exit(1);
	}

	for (i = 0; i < 5; i++) {
		gpioSetMode(input_pins[i], PI_INPUT);
		gpioSetPullUpDown(input_pins[i], PI_PUD_DOWN);
	}

	for (i = 0; i < 2; i++) {
		gpioSetMode(output_pins[i], PI_OUTPUT);
		gpioWrite(output_pins[i], 0);
	}
}

void reset_ports() {
	// pass
}

void fetch_ports(PortInfo_t *port_info) {
	port_info->line_sensors = 0;
	for (int i = 0; i < 5; i++) {
		port_info->line_sensors |= gpioRead(INPUT_PINS[i]) << i;
	}
}

void dispatch_motor_state(unsigned char motor_state) {
	for (int i = 0; i < 2; i++) {
		gpioWrite(OUTPUT_PINS[i], (motor_state >> i) & 1);
	}
}

#endif
