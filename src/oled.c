#include "oled.h"

static uint8_t OLED_Buffer[OLED_WIDTH * OLED_HEIGHT / 8];
static OLED_t OLED;

void OLED_Command(uint8_t cmd) {
    uint8_t data[2] = {0x00, cmd}; 
    I2C1_Master_Transmit(OLED_ADDRESS, data, 2); 
}

void OLED_Data(uint8_t data) {
    uint8_t data_buf[2] = {0x40, data}; 
    I2C1_Master_Transmit(OLED_ADDRESS, data_buf, 2); 
}

void OLED_Fill(OLED_COLOR color) {
    uint32_t i;
    for(i = 0; i < sizeof(OLED_Buffer); i++) {
        OLED_Buffer[i] = (color == Black) ? 0x00 : 0xFF;
    }
}

void OLED_UpdateScreen(void) {
    for (uint8_t i = 0; i < (OLED_HEIGHT / 8); i++) {
        OLED_Command(0xB0 + i);      // Set page address
        OLED_Command(0x00);          // Set lower column address
        OLED_Command(0x10);          // Set higher column address

        uint8_t data[OLED_WIDTH + 1];
        data[0] = 0x40; // Control byte for data
        memcpy(&data[1], &OLED_Buffer[OLED_WIDTH * i], OLED_WIDTH);

        I2C1_Master_Transmit(OLED_ADDRESS, data, OLED_WIDTH + 1);
    }
}

void OLED_Clear(void) {
    OLED_Fill(Black);
    OLED_UpdateScreen();
    OLED.CurrentX = 0;
    OLED.CurrentY = 0;
}

void OLED_Init(void) {
    // Reset OLED
    GPIO_WritePin(OLED_SCL_PORT, OLED_SCL_PIN, 0);
    GPIO_WritePin(OLED_SDA_PORT, OLED_SDA_PIN, 0);
    delay_ms(100);
    GPIO_WritePin(OLED_SCL_PORT, OLED_SCL_PIN, 1);
    GPIO_WritePin(OLED_SDA_PORT, OLED_SDA_PIN, 1);
    delay_ms(100);

    OLED_Command(0xAE); // Display OFF
    OLED_Command(0x20); OLED_Command(0x00); // Set Memory Addressing Mode to Horizontal
    OLED_Command(0xB0); // Set Page Start Address for Page Addressing Mode, 0-7
    OLED_Command(0xC8); // Set COM Output Scan Direction
    OLED_Command(0x00); // Set low column address
    OLED_Command(0x10); // Set high column address
    OLED_Command(0x40); // Set start line address
    OLED_Command(0x81); OLED_Command(0x7F); // Set contrast control register
    OLED_Command(0xA1); // Set segment re-map 0 to 127
    OLED_Command(0xA6); // Set normal display
    OLED_Command(0xA8); OLED_Command(0x3F); // Set multiplex ratio(1 to 64)
    OLED_Command(0xA4); // Output follows RAM content
    OLED_Command(0xD3); OLED_Command(0x00); // Set display offset
    OLED_Command(0xD5); OLED_Command(0x80); // Set display clock divide ratio/oscillator frequency
    OLED_Command(0xD9); OLED_Command(0xF1); // Set pre-charge period
    OLED_Command(0xDA); OLED_Command(0x12); // Set com pins hardware configuration
    OLED_Command(0xDB); OLED_Command(0x40); // Set vcomh
    OLED_Command(0x8D); OLED_Command(0x14); // Enable charge pump
    OLED_Command(0xAF); // Display ON

    OLED_Clear();
    OLED.Inverted = 1; // Normal display
}

void OLED_SetCursor(uint8_t x, uint8_t y) {
    OLED.CurrentX = x;
    OLED.CurrentY = y;

    uint8_t page = y / 8;
    OLED_Command(0xB0 + page);
    OLED_Command(0x00 + (x & 0x0F));
    OLED_Command(0x10 + ((x >> 4) & 0x0F));
}

void OLED_InvertColors(void) {
    OLED.Inverted = !OLED.Inverted;
}

void OLED_DrawPixel(uint8_t x, uint8_t y, OLED_COLOR color) {
    if (x >= OLED_WIDTH || y >= OLED_HEIGHT) {
        return;
    }

    if (OLED.Inverted) {
        color = (OLED_COLOR)!color;
    }
    
    if (color == White) {
        OLED_Buffer[x + (y / 8) * OLED_WIDTH] |= 1 << (y % 8);
    } else {
        OLED_Buffer[x + (y / 8) * OLED_WIDTH] &= ~(1 << (y % 8));
    }
}

void OLED_WriteChar(char c, FontDef font, OLED_COLOR color) {
    uint32_t i, b, j;

    if (OLED_WIDTH <= (OLED.CurrentX + font.FontWidth) || OLED_HEIGHT <= (OLED.CurrentY + font.FontHeight)) {
        return;
    }

    for (i = 0; i < font.FontHeight; i++) {
        b = font.data[(c - 32) * font.FontHeight + i];
        for (j = 0; j < font.FontWidth; j++) {
            if ((b << j) & 0x8000) {
                OLED_DrawPixel(OLED.CurrentX + j, (OLED.CurrentY + i), (OLED_COLOR) color);
            }
            else {
                OLED_DrawPixel(OLED.CurrentX + j, (OLED.CurrentY + i), (OLED_COLOR)!color);
            }
        }
    }

    OLED.CurrentX += font.FontWidth;
}

void OLED_WriteString(const char* str, FontDef font, OLED_COLOR color) {
    while (*str) {
        while (*str == ' ') str++;

        int word_len = 0;
        const char* p = str;
        while (p[word_len] && p[word_len] != ' ') word_len++;

        if (OLED.CurrentX + word_len * font.FontWidth > OLED_WIDTH) {
            OLED.CurrentX = 0;
            OLED.CurrentY += font.FontHeight;
            if (OLED.CurrentY + font.FontHeight > OLED_HEIGHT) break;
        }

        for (int i = 0; i < word_len && str[i]; i++) {
            OLED_WriteChar(str[i], font, color);
        }
        str += word_len;

        if (*str == ' ') {
            if (OLED.CurrentX + font.FontWidth > OLED_WIDTH) {
                OLED.CurrentX = 0;
                OLED.CurrentY += font.FontHeight;
                if (OLED.CurrentY + font.FontHeight > OLED_HEIGHT) break;
            } else {
                OLED_WriteChar(' ', font, color);
            }
            str++;
        }
    }
}

void OLED_DrawFilledRectangle(
    uint8_t x, uint8_t y, 
    uint8_t width, uint8_t height, 
    OLED_COLOR color
) {
    for (uint8_t j = 0; j < height; j++) {
        for (uint8_t i = 0; i < width; i++) {
            OLED_DrawPixel(x + i, y + j, color);
        }
    }
}
