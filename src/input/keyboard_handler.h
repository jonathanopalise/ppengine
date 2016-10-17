#ifndef __INPUT_KEYBOARD_HANDLER_H
#define __INPUT_KEYBOARD_HANDLER_H

#include <osgGA/GUIEventHandler>

class myKeyboardEventHandler : public osgGA::GUIEventHandler {
	public:
		virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&);
		virtual void accept(osgGA::GUIEventHandlerVisitor& v)   { v.visit(*this); };
};

#endif

