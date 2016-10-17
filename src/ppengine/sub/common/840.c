#include "ppengine/sub/common/840.h"
#include "ppengine/engine.h"

void common_840() {
	engine_sound_active=0;
	if (!waiting_for_coin) {
		engine_sound_active=1;
	}
}
