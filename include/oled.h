#ifndef OLED_H
#define OLED_H

#include <stm32f103xe.h>
#include <pinmap.h>
#include <stdint.h>
#include <delay.h>
#include <fonts.h>
#include <gpio.h>
#include <i2c.h>
#include <string.h>

#define OLED_ADDRESS     (0x3C << 1) 
#define OLED_WIDTH       128
#define OLED_HEIGHT      64

typedef struct {
    uint16_t CurrentX;
    uint16_t CurrentY;
    uint8_t Inverted;
} OLED_t;

typedef enum {
    Black = 0x00, 
    White = 0x01  
} OLED_COLOR;

void OLED_Command(uint8_t cmd);
void OLED_Data(uint8_t data);
void OLED_Fill(OLED_COLOR color);
void OLED_UpdateScreen(void);
void OLED_Clear(void);
void OLED_Init(void);
void OLED_SetCursor(uint8_t x, uint8_t y);
void OLED_DrawPixel(uint8_t x, uint8_t y, OLED_COLOR color);
void OLED_WriteChar(char c, FontDef font, OLED_COLOR color);
void OLED_WriteString(const char* str, FontDef font, OLED_COLOR color);
void OLED_DrawFilledRectangle(
    uint8_t x, uint8_t y, 
    uint8_t width, uint8_t height, 
    OLED_COLOR color
);

#endif // OLED_H

