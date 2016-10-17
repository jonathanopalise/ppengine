#ifndef __SUB2_FUNCTIONQUEUE_H
#define __SUB2_FUNCTIONQUEUE_H

#include <inttypes.h>

void init_sub2_function_queue();
void queue_sub2_function(uint16_t function_number);
void execute_next_sub2_queued_function();

#endif
