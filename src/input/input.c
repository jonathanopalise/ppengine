#include "input/input.h"
#include "input/keyboard_queue.h"
#include "input/keyboard_handler.h"
#include "scene/osg/scene.h"
#include "ppengine/engine.h"
#include <osgViewer/ViewerEventHandlers>

static int16_t steering_wheel_rotation_change=0;

void input_initialise() {
	osg_scene_register_event_handler(new myKeyboardEventHandler());
}

void update_engine_state_from_input() {
	struct keyboardevent keyboard_event;

	while (keyboard_event_queue_populated()) {
		keyboard_event=keyboard_event_queue_get();
		switch (keyboard_event.type) {
			case osgGA::GUIEventAdapter::KEYDOWN:
				switch(keyboard_event.key) {
					case osgGA::GUIEventAdapter::KEY_Left:
						steering_wheel_rotation_change=-1;
						break;
					case osgGA::GUIEventAdapter::KEY_Right:
						steering_wheel_rotation_change=1;
						break;
					case osgGA::GUIEventAdapter::KEY_Up:
						internal_accel_pedal=7;
						break;
					case osgGA::GUIEventAdapter::KEY_Down:
						internal_brake_pedal=7;
						break;
					case osgGA::GUIEventAdapter::KEY_1:
						credits_remaining++;
						break;
					case osgGA::GUIEventAdapter::KEY_Space:
						if (gear_binary==0) {
							gear_binary=1;
						} else {
							gear_binary=0;
						}
						break;
				}			
			break;
			case osgGA::GUIEventAdapter::KEYUP:
				switch(keyboard_event.key) {
					case osgGA::GUIEventAdapter::KEY_Left:
						steering_wheel_rotation_change=0;
						break;
					case osgGA::GUIEventAdapter::KEY_Right:
						steering_wheel_rotation_change=0;
						break;
					case osgGA::GUIEventAdapter::KEY_Up:
						internal_accel_pedal=0;
						break;
					case osgGA::GUIEventAdapter::KEY_Down:
						internal_brake_pedal=0;
						break;
				}
			break;
		}
		keyboard_event=keyboard_event_queue_get();
	}
	steering_wheel_rotation+=steering_wheel_rotation_change;
}


