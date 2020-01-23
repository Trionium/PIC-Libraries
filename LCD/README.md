# LCD Library for 8-bit PIC

This is a powerful library for 8-bit **PIC** microcontrollers written in **XC8** language. You can use it in an 8-bit microcontroller with small changes. Create a project in **MPLAB IDE** and follow the steps below.

[For a reading post about this visit our site.](https://trion-projects.blogspot.com/2020/01/lcd-interfacing-with-pic-using-xc8.html)

## Step 1
Firstly, you must create `config.h` file in **Header Files** and include it in `main.c` file.  Write your  **Configuration Bit Settings** and  `#define _XTAL_FREQ FrequencyInHertz` in `config.h` file. After that add include statements. For LCD library you need;
 - `#include <xc.h>`
 - `#include <stdint.h>`
 - `#include <stdio.h>`
 - `#include <"lcd.h">`
In this file you should include all of used libraries. Example (`config.h` file) is shown for PIC16F628A microcontroller.

## Step 2
Install `lcd.c` and `lcd.h` files and move them to your `*.X` directory. Then in **Projects** panel right-click to `Header Files` and click `Add Existing Item...`. Select `lcd.h` file and click **Select**. Do the same thing for `lcd.c` file but add it to **Source Files**.

## Step 3
Finally, go into `lcd.h` file and edit section between stars for your microcontroller. You must use one PORT for LCD.

## Usage of Functions

### LCDInitialize()
This function initializes the LCD. Before use any function make sure that `LCDInitialize()` function is called once like code below.
``` c
void main(void) {
    LCDInitialize();
    while(1) {
      LCDPrintString("Trion Projects", 1, 1);
    }
}
```
### LCDClearDisplay()
To clear display use this function. To execute this function you need about 2ms.

### LCDReturnHome()
To move curser home use this function. To execute this function you need about 2ms.

### LCDDisplayToggle(time, n)
When you need display toggle to use this function. `time` is between 0 and 256. `n` is toggle number. Each time multiplied by 100ms. See the example below.

``` c
void main(void) {
        LCDInitialize();
        while(1) {
          LCDPrintString("Trion Projects", 1, 1);
          // Toggle display 3 times with 500ms time.
          LCDDisplayToggle(5, 3);
        }
    }
```

### LCDDisplayOn()
Turn display on when display is off or stay display at on state. This function can be used for toggle display with **LCDDisplayOff()** function.

### LCDDisplayOff()
Turn display off when the display is on or stay display at off state.

### LCDCursorOn()
To turn on cursor use this function.

### LCDCursorOff()
To turn off cursor use this function.

### LCDCursorBlinkOn()
To turn on cursor blink use this function.

### LCDCursorBlinkOff()
To turn off cursor blink use this function.

### LCDShiftDisplayRight()
To shift display right use this function.

### LCDShiftDisplayLeft()
To shift display left use this function.

### LCDShiftCursorRight()
To shift cursor right use this function.

### LCDShiftCursorLeft()
To shift cursor left use this function.

### LCDPrintChar(ch, y, x)
If you want to print one character to a specific position use this function. `ch` is char which you want to print. `y` is line number. The first line is 1, the second line is 2.  `x` is the position of the line.  `x` must be between 0 and 17. Which can be a minimum of 1 and a maximum of 16.

### LCDPrintString(string, y, x)
If you want to print the string to a specific position use this function. `string` is data which you want to print. `y` is line number. The first line is 1, the second line is 2.  `x` is the position of the line.  `x` must be between 0 and 17. Which can be a minimum of 1 and a maximum of 16. To center string, you could write 0 to x position and string will be centered. See examples below:

You can write string directly to function.

``` c
void main(void) {
      LCDInitialize();
      while(1) {
        // Right justified string
        LCDPrintString("Trion Projects", 1, 1);
        // Centered string
        LCDPrintString("Trion Projects", 2, 0);
      }
}
```
Or you can define char string and pass it to function.

``` c
void main(void) {
      LCDInitialize();
      char str[15] = "Trion Projects";
      while(1) {
        LCDPrintString(str, 1, 1);
      }
}
```

## Print Numbers
If you want to print some numbers, firstly, you need to convert it a string and then pass it to function. Let see the example below:

This example shows how to print variable integer numbers to LCD.

``` c
  void main(void) {
        LCDInitialize();
        char str[10];
        uint8_t num = 0;
        while(1) {
          sprintf(str, "%d", num);
          LCDPrintString(str, 1, 1);
          __delay_ms(1000);
          num++;
        }
  }
```

This example shows how to print variable double numbers to LCD.

``` c
void main(void) {
      LCDInitialize();
      char str[10];
      double num = 0.15;
      while(1) {
        sprintf(str, "%.2f", num);
        LCDPrintString(str, 1, 1);
        __delay_ms(1000);
        num += 0.05;
      }
}
```
