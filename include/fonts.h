#ifndef _FONTS_H
#define _FONTS_H

#include <stdint.h>

typedef struct {
    const uint8_t FontWidth;   
    uint8_t FontHeight;        
    const uint16_t *data;      
} FontDef;

extern FontDef Font_7x10;
extern FontDef Font_11x18;
extern FontDef Font_16x26;

#endif  // _FONTS_H