#include "ppengine/sub2/queuedfunctions/24d8.h"
#include "ppengine/lib/hud.h"

void queued_function_24d8() {
	// base is 0x9880
	write_hud_message(35,(char *)"TOP",5);
	write_hud_message(46,(char *)"TIME",3);
	write_hud_message(97,(char *)"SCORE",2);
	write_hud_message(54,(char *)"LAP   \"",4);
	write_hud_message(116,(char *)"SPEED    km",1);
}
