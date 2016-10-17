#include <stdio.h>
#include "ppengine/sub2/functionqueue.h"
#include "ppengine/sub2/queuedfunctions/1e6.h"
#include "ppengine/sub2/queuedfunctions/40c.h"
#include "ppengine/sub2/queuedfunctions/476.h"
#include "ppengine/sub2/queuedfunctions/554.h"
#include "ppengine/sub2/queuedfunctions/59e.h"
#include "ppengine/sub2/queuedfunctions/24d8.h"

#define NUM_QUEUE_ENTRIES 32

int tail_index;
int head_index;
uint16_t queue_entries[NUM_QUEUE_ENTRIES];

void dispatch_sub2_function(uint16_t function_number);

void init_sub2_function_queue() {
	tail_index=0;
	head_index=0;
}

void queue_sub2_function(uint16_t function_number) {
	queue_entries[head_index]=function_number;
	head_index++;
	if (head_index==NUM_QUEUE_ENTRIES) {
		head_index=0;
	}
}

void execute_next_sub2_queued_function() {
	if (head_index!=tail_index) {
		dispatch_sub2_function(queue_entries[tail_index]);
		tail_index++;
		if (tail_index==NUM_QUEUE_ENTRIES) {
			tail_index=0;
		}
	}
}

void dispatch_sub2_function(uint16_t function_number) {
	switch(function_number) {
		case 0x0:
			queued_function_1e6();
			break;
		case 0x1:
			queued_function_476();
			break;
		case 0x2:
		case 0x4:
			queued_function_554();
			break;
		case 0x3:
			queued_function_59e();
			break;
		case 0x6:
		case 0x7:
			queued_function_24d8();
			break;
		case 0x18:
			queued_function_40c();
			break;
	}
}

