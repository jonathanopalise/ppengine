#include <stdio.h>
#include <inttypes.h>
#include "ppengine/sub/framehandlerdispatch.h"
#include "ppengine/sub/framehandler/unimplemented.h"
#include "ppengine/sub/framehandler/316.h"
#include "ppengine/sub/framehandler/3a8.h"
#include "ppengine/sub/framehandler/3d0.h"
#include "ppengine/sub/framehandler/42a.h"
#include "ppengine/sub/framehandler/456.h"
#include "ppengine/sub/framehandler/46c.h"
#include "ppengine/sub/framehandler/4d6.h"
#include "ppengine/sub/framehandler/4ec.h"
#include "ppengine/sub/framehandler/602.h"
#include "ppengine/sub/framehandler/66a.h"
#include "ppengine/sub/framehandler/72a.h"
#include "ppengine/sub/framehandler/808.h"
#include "ppengine/sub/framehandler/852.h"
#include "ppengine/sub/framehandler/8cc.h"
#include "ppengine/sub/framehandler/9e0.h"
#include "ppengine/sub/framehandler/a2e.h"
#include "ppengine/sub/framehandler/aba.h"
#include "ppengine/sub/framehandler/b2c.h"
#include "ppengine/sub/framehandler/bd0.h"
#include "ppengine/sub/framehandler/c34.h"
#include "ppengine/sub/framehandler/c68.h"
#include "ppengine/sub/framehandler/c86.h"
#include "ppengine/engine.h"

#define JUMP_TABLE_OFFSET_NONE 0xffff

uint32_t frame_number;
uint16_t jump_table_offset;
uint16_t last_jump_table_offset;

void sub_frame_handler_init() {
	frame_number=1;
	last_jump_table_offset=JUMP_TABLE_OFFSET_NONE;
}

void sub_frame_handler_dispatch() {
	static int start_indices[] = {0,3,12,14,30};

	static void (*const function_pointers[])(void) = {
                                      // offset  func/subfunc  address  description
        frame_handler_316,            //      0           0/0      316  one off power up initialisation? need to check
        frame_handler_3a8,            //      1           0/1      3a8  does nothing - looks like just a delay loop in current form
        frame_handler_3d0,            //      2           0/2      3d0
        frame_handler_unimplemented,  //      3           1/0      406  looks to be just a delay loop
        frame_handler_42a,            //      4           1/1      42a  display title screen and initialise some ingame variables
        frame_handler_456,            //      5           1/2      456  animate colours on title screen
        frame_handler_46c,            //      6           1/3      46c  initialise some demo variables and display demo ingame screen
        frame_handler_4d6,            //      7           1/4      4d6  demo lights sequence
        frame_handler_4ec,            //      8           1/5      4ec  demo main loop
        frame_handler_unimplemented,  //      9           1/6      52e  unused
        frame_handler_unimplemented,  //     10           1/7      542  unused
        frame_handler_unimplemented,  //     11           1/8      59a  unused
        frame_handler_602,            //     12           2/0      602  just skips to next subfunction number
        frame_handler_unimplemented,  //     13           2/1      63c
        frame_handler_66a,            //     14           3/0      66a  initialise qualifying variables following coin insert
        frame_handler_72a,            //     15           3/1      72a  animate title screen following coin insert
        frame_handler_808,            //     16           3/2      808
        frame_handler_852,            //     17           3/3      852  qualifying lights sequence
        frame_handler_8cc,            //     18           3/4      8cc  qualifying main loop
        frame_handler_9e0,            //     19           3/5      9e0  qualifying results/bonus sequence
        frame_handler_a2e,            //     20           3/6      a2e  race initialisation
        frame_handler_aba,            //     21           3/7      aba  race lights sequence
        frame_handler_b2c,            //     22           3/8      b2c  race main loop
        frame_handler_bd0,            //     23           3/9      bd0  car slowdown after completing full race distance (need to double check this)
        frame_handler_c34,            //     24          3/10      c34  
        frame_handler_c68,            //     25          3/11      c68  end race passing bonus/time bonus display
        frame_handler_c86,            //     26          3/12      c86  end race passing bonus/time bonus countdown
        frame_handler_316,            //     27          3/13      316
        frame_handler_316,            //     28          3/14      316
        frame_handler_316,            //     29          3/15      316
        frame_handler_unimplemented,  //     30           4/0      ca0
        frame_handler_unimplemented,  //     31           4/1      d4e
        frame_handler_unimplemented,  //     32           4/2      e5c
        frame_handler_unimplemented,  //     33           4/3      f32
        frame_handler_unimplemented,  //     34           4/4      f5c
        frame_handler_unimplemented,  //     35           4/5      f32
        frame_handler_unimplemented,  //     36           4/6      fda
        frame_handler_unimplemented,  //     37           4/7      f32
        frame_handler_unimplemented,  //     38           4/8     1086
        frame_handler_unimplemented,  //     39           4/9     10a8
        frame_handler_unimplemented,  //     40          4/10     111a
        frame_handler_unimplemented,  //     41          4/11     11aa
        frame_handler_unimplemented   //     42          4/12     11bc
	};

	jump_table_offset=start_indices[jump_table_function_number&7]+(jump_table_subfunction_number&31);
	frame_number++;

	function_pointers[jump_table_offset]();
}
