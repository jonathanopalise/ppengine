#include "ppengine/sub/common/bc8.h"
#include "ppengine/sub/common/1a0a.h"
#include "ppengine/sub/common/1a26.h"
#include "ppengine/sub/common/17da.h"

void common_bc8() {
	common_1a0a(); // update seconds remaining hud value
	common_1a26(); // update laptime hud value in top right (flash on/off if required)
	common_17da(); // update speed hud value in top right
}


