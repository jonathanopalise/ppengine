#ifndef __INPUT_KEYBOARD_QUEUE_H
#define __INPUT_KEYBOARD_QUEUE_H

struct keyboardevent {
	int type;
	int key;
};

int keyboard_event_queue_populated();
void keyboard_event_queue_put(struct keyboardevent keyboard_event);
struct keyboardevent keyboard_event_queue_get();

#endif

