#ifndef EMULATE_H_
#define EMULATE_H_

#include "linetrace.h"
#include "types.h"

void init_ports();
void reset_ports();
void fetch_ports(PortInfo_t *port_info);
void dispatch_move(Move move, LoopTick tick);

#endif /* EMULATE_H_ */
