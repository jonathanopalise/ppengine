#include "input/keyboard_queue.h"

#define NUM_QUEUE_ENTRIES 32

static int tail_index=0;
static int head_index=0;
static struct keyboardevent queue_entries[NUM_QUEUE_ENTRIES];

int keyboard_event_queue_populated() {
	return(head_index!=tail_index);
}

void keyboard_event_queue_put(struct keyboardevent keyboard_event) {
	queue_entries[head_index]=keyboard_event;
	head_index++;
	if (head_index==NUM_QUEUE_ENTRIES) {
		head_index=0;
	}
}

struct keyboardevent keyboard_event_queue_get() {
	struct keyboardevent keyboard_event;
	if (head_index!=tail_index) {
		keyboard_event=queue_entries[tail_index];
		tail_index++;
		if (tail_index==NUM_QUEUE_ENTRIES) {
			tail_index=0;
		}
	} else {
		keyboard_event.type=0;
		keyboard_event.key=0;
	}
	return keyboard_event;
}

