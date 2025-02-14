#ifdef __XC8
#include "register_util.h"

#include "types.h"
#include <xc.h>

#include <pic18f2550.h>

// #include <pic18f25k50.h>

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
	port_info->line_sensors =
	    (unsigned char)((PORTBbits.RB0) | (PORTBbits.RB1 << 1) |
	                    (PORTBbits.RB2 << 2) | (PORTBbits.RB3 << 3) |
	                    (PORTBbits.RB4 << 4));
}

void dispatch_motor_state(unsigned char motor_state) {
	LATC = (unsigned char)((LATC & ~0b11) | (motor_state & 0b11));
}

#endif
