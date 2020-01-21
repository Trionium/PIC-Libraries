/* 
 * File:   lcd.h
 * Author: Trion Projects
 * Comments:
 * Revision history: v1.0
 */

#ifndef LCD_H
#define LCD_H

// *****************************************************************************
// ************************** Edit Befor Use Library ***************************
// Write which PORT and TRIS is LCD uses.
volatile unsigned *LCD_PORT = &PORTB;
volatile unsigned *LCD_TRIS = &TRISB;

// Adjust pins in define section.
#define LCD_RW  6     // The RW bit of the PORT
#define LCD_RS  4     // The RS bit of the PORT
#define LCD_EN  5     // The EN bit of the PORT
#define LCD_D4  0     // The D4 bit of the PORT
#define LCD_D5  1     // The D5 bit of the PORT
#define LCD_D6  2     // The D6 bit of the PORT
#define LCD_D7  3     // The D7 bit of the PORT

// *****************************************************************************

#define ClearDisplay        0b00000001
#define ReturnHome          0b00000010
#define DisplayOn           0b00000100
#define DisplayOff          0b00000100
#define CursorOn            0b00000010
#define CursorOff           0b00000010
#define CursorBlinkOn       0b00000001
#define CursorBlinkOff      0b00000001
#define ShiftToLeft         0b00000100
#define ShiftToRight        0b00000100
#define ShiftCursor         0b00001000
#define ShiftDisplay        0b00001000
#define FirstLine           0b10000000
#define SecondLine          0b11000000

uint8_t lcdEntryMode = 0b00000111;
uint8_t lcdDisplayControl = 0b00001100;
uint8_t lcdCursorDisplayShift = 0b00010000;

void LCDInitialize();
void LCDSendByte(uint8_t reg, uint8_t byte);
void LCDSendNibble(uint8_t nibble);
void LCDCommand(uint8_t byte);
void LCDClearDisplay(void);
void LCDReturnHome(void);
void LCDDisplayToggle(uint8_t time, uint8_t n);
void LCDDisplayOn(void);
void LCDDisplayOff(void);
void LCDCursorOn(void);
void LCDCursorOff(void);
void LCDCursorBlinkOn(void);
void LCDCursorBlinkOff(void);
void LCDShiftDisplayRight(void);
void LCDShiftDisplayLeft(void);
void LCDShiftCursorRight(void);
void LCDShiftCursorLeft(void);
void LCDSetPos(uint8_t x, uint8_t y);
void LCDPrintChar(uint8_t ch, uint8_t y, uint8_t x);
void LCDPrintString(uint8_t *string, uint8_t y, uint8_t x);

#endif
