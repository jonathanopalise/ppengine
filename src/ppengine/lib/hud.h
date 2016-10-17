#ifndef __LIB_HUD_H
#define __LIB_HUD_H

#include <inttypes.h>

void write_hud_message(int offset,char *message,uint8_t attribute);
void write_hud_bcd_16(int offset,uint16_t bcd,uint8_t attribute);
void clear_hud_characters(int offset,int count);

#endif
