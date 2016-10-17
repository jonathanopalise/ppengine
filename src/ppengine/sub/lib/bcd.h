#ifndef __SUB_LIB_BCD_H
#define __SUB_LIB_BCD_H

#include <inttypes.h>

uint32_t bcd_to_native(uint32_t bcd);
uint32_t native_to_bcd(uint32_t native);

#endif
