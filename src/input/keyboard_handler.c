#include "input/keyboard_handler.h"
#include "input/keyboard_queue.h"

bool myKeyboardEventHandler::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa) {
	struct keyboardevent keyboard_event;

	switch(ea.getEventType()) {
		case(osgGA::GUIEventAdapter::KEYDOWN):
		case(osgGA::GUIEventAdapter::KEYUP):
			keyboard_event.type=ea.getEventType();
			keyboard_event.key=ea.getKey();
			keyboard_event_queue_put(keyboard_event);
			return false;
		default:
			return false;
	}
}
