#ifndef REGISTER_UTIL_H_
#define REGISTER_UTIL_H_

#include "linetrace.h"
#include "types.h"

void init_ports(void);
void reset_ports(void);
void fetch_ports(PortInfo_t *port_info);
void dispatch_motor_state(unsigned char motor_state);

#endif /* REGISTER_UTIL_H_ */
