/*
 * File:   lcd.c
 * Author: Trion Projects
 *
 * LCD Library for 16x2 LCDs.
 * 
 */

#include "config.h"

// ---
void LCDInitialize() {
    // Set TRIS as output and clear PORT
    *LCD_TRIS = 0;
    *LCD_PORT = 0;
    
    /*******************************************
     If needed clear analog pins which LCD uses
    *******************************************/
    
    // Wait for initialize
    __delay_ms(40);
    
    // Return home
    LCDSendNibble(0x03);
    __delay_us(4500);
    LCDSendNibble(0x03);
    __delay_us(4500);
    LCDSendNibble(0x03);
    __delay_us(150);
    
    
    LCDSendNibble(ReturnHome);
    // Function Set
    // DL: 4-bit, N: 2-line, F: 5x8 dots
    LCDSendByte(0, 0x28);
    // Display ON/OFF control
    // D: Display ON, C: Cursor OFF, B: Cursor Blink OFF
    LCDSendByte(0, lcdDisplayControl);
    LCDSendByte(0, ClearDisplay);
    // Entry Mode Set
    // I/D: Cursor/blink moves to right and DDRAM address is increased by 1
    // SH: Shifting entire display is performed
    LCDSendByte(0, lcdEntryMode);
}

// Clear display
void LCDClearDisplay(void) {
    LCDSendByte(0, ClearDisplay);
    __delay_ms(2);
}

// Return cursor to home
void LCDReturnHome(void) {
    LCDSendByte(0, ReturnHome);
    __delay_ms(2);
}

// Toggle display
/* 1 < time < 256
 * 1 < n < 256
 */
void LCDDisplayToggle(uint8_t time, uint8_t n) {
    // Blink LCD n times
    for(n; n > 0; n--) {
        LCDDisplayOff();
        for(uint8_t i = time; i > 0; i--) {
            __delay_ms(100);
        }
        LCDDisplayOn();
        for(uint8_t i = time; i > 0; i--) {
            __delay_ms(100);
        }
    }
}

// Display lcd on
void LCDDisplayOn(void) {
    lcdDisplayControl |= DisplayOn;
    LCDSendByte(0, lcdDisplayControl);
}

// Display lcd off
void LCDDisplayOff(void) {
    lcdDisplayControl &= ~DisplayOff;
    LCDSendByte(0, lcdDisplayControl);
}

// Cursor on
void LCDCursorOn(void) {
    lcdDisplayControl |= CursorOn;
    LCDSendByte(0, lcdDisplayControl);
}

// Cursor off
void LCDCursorOff(void) {
    lcdDisplayControl &= ~CursorOff;
    LCDSendByte(0, lcdDisplayControl);
}

// Cursor blink on
void LCDCursorBlinkOn(void) {
    lcdDisplayControl |= CursorBlinkOn;
    LCDSendByte(0, lcdDisplayControl);
}

// Cursor blink off
void LCDCursorBlinkOff(void) {
    lcdDisplayControl &= ~CursorBlinkOff;
    LCDSendByte(0, lcdDisplayControl);
}

// Shift display right
void LCDShiftDisplayRight(void) {
    lcdCursorDisplayShift |= ShiftDisplay;
    lcdCursorDisplayShift |= ShiftToRight;
    LCDSendByte(0, lcdCursorDisplayShift);
}

// Shift display left
void LCDShiftDisplayLeft(void) {
    lcdCursorDisplayShift |= ShiftDisplay;
    lcdCursorDisplayShift &= ~ShiftToLeft;
    LCDSendByte(0, lcdCursorDisplayShift);
}

// Shift cursor right
void LCDShiftCursorRight(void) {
    lcdCursorDisplayShift &= ~ShiftCursor;
    lcdCursorDisplayShift |= ShiftToRight;
    LCDSendByte(0, lcdCursorDisplayShift);
}

// Shift cursor left
void LCDShiftCursorLeft(void) {
    lcdCursorDisplayShift &= ~ShiftCursor;
    lcdCursorDisplayShift &= ~ShiftToLeft;
    LCDSendByte(0, lcdCursorDisplayShift);
}

// Send nibble to lcd
void LCDSendNibble(uint8_t nibble) {
    // Check nibbles bits and set PORT.
    *LCD_PORT = (unsigned)((nibble & 0b00000001) >> 0) ? (*LCD_PORT | (1 << LCD_D4)) : (*LCD_PORT & ~(1 << LCD_D4));
    *LCD_PORT = (unsigned)((nibble & 0b00000010) >> 1) ? (*LCD_PORT | (1 << LCD_D5)) : (*LCD_PORT & ~(1 << LCD_D5));
    *LCD_PORT = (unsigned)((nibble & 0b00000100) >> 2) ? (*LCD_PORT | (1 << LCD_D6)) : (*LCD_PORT & ~(1 << LCD_D6));
    *LCD_PORT = (unsigned)((nibble & 0b00001000) >> 3) ? (*LCD_PORT | (1 << LCD_D7)) : (*LCD_PORT & ~(1 << LCD_D7));
    
    // Send nibble to LCD.
    *LCD_PORT |= 1 << LCD_EN;  // E pin - LCD Enable
    __delay_us(1);
    *LCD_PORT &= ~(1 << LCD_EN);  // E pin - LCD Disable
    __delay_us(50); // min. 37us
}

// Send byte to lcd
void LCDSendByte(uint8_t reg, uint8_t byte) {
    *LCD_PORT = reg ? (*LCD_PORT | (1 << LCD_RS)) : (*LCD_PORT & ~(1 << LCD_RS));  // RS pin - Register Select
    
    *LCD_PORT &= ~(1 << LCD_RW);  // RW pin to write mode
    
    LCDSendNibble(byte >> 4);
    LCDSendNibble(byte & 0x0f);
}

/*
************* Display Position ***************
1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16
-----------------------------------------------
00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
40 41 42 43 44 45 46 47 48 49 4A 4B 4C 4D 4E 4F
*/

// Set position
void LCDSetPos(uint8_t x, uint8_t y) {
    uint8_t addr;
    
    if(y == 2)
        addr = 0x40;
    else
        addr = 0;
    
    addr += x-1;
    
    LCDSendByte(0, 0x80 | addr);
}

// Print one character to lcd
void LCDPrintChar(uint8_t ch, uint8_t y, uint8_t x) {
    LCDSetPos(x, y);
    LCDSendByte(1, byte);
}

// Print string to lcd
void LCDPrintString(uint8_t *string, uint8_t y, uint8_t x) {
    // Set position
    LCDSetPos(x, y);
    // Write each char
    for(uint8_t i = 0; i < 17; i++) {
        if(string[i] == '\0') break;
        LCDSendByte(1, string[i]);
    }
}

