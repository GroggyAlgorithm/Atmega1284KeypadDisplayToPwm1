/**
 * \file lcd.h
 * \author Tim Robbins
 * \brief Header file for LCD character displays. \n
 * \version v2.0.0.0
 * REQUIREMENTS: requires a "config.h" file for the macro definitions, "mcuUtils.h", and "mcuDelays.h". \n
 * LCD_ROW_COUNT for the amount of rows on the lcd, \n
 * LCD_COLUMN_COUNT for the amount of columns on the LCD, \n
 * Port registers defined as LCD_CONTROL_PORT, LCD_DATA_PORT, LCD_DATA_PORT_READ, LCD_DATA_PORT_DIR. The commands assume the pins are ordered sequentially. \n
 * LCD_RS_PIN, LCD_RW_PIN, and LCD_E_PIN for control pin positions on LCD_CONTROL_PORT. These do not need to be defined in sequential order. \n
 * LCD_BUSY_FLAG_POSITION as the pin position of the busy flag pin on LCD_DATA_PORT. \n
 * LCD_USE_4_BIT_MODE is used to describe using the LCD in 4 bit mode. This must be defined as 1 to be active. \n
 * If LCD_USE_4_BIT_MODE is selected, pins as LCD_D6, LCD_D5, LCD_D4 must be defined as their respective pin numbers. Since D7 is the same as the busy flag, D7 is not required to be defined. \n
 * To see any ERRORS, define LCD_SHOW_DEFINE_ERRORS as 1
 * \todo Needs to have 4 bit modes tested.
 */ 
#ifndef CLCD_H_
#define CLCD_H_             1
#define __INCLUDED_CLCD__   1

#ifdef __cplusplus
extern "C" {
#endif

//INCLUDES
    
#include "config.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "mcuUtils.h"
#include "mcuDelays.h"
#include "mcuPinUtils.h"


#ifdef __AVR

#include <avr/io.h>

#elif defined(__XC)

#include <xc.h>        /* XC8 General Include File */

#elif defined(HI_TECH_C)

#include <htc.h>       /* HiTech General Include File */

#elif defined(__18CXX)

#include <p18cxxx.h>   /* C18 General Include File */

#elif (defined __XC8)

#include <xc.h>            /* XC8 General Include File */

#endif


//ERROR CHECKING

//The amount of columns on the display
#ifndef LCD_COLUMN_COUNT
#define CLCD_C_ -1
#undef __INCLUDED_CLCD__
#endif

//The amount of rows on the display
#ifndef LCD_ROW_COUNT
#define CLCD_C_ -1
#undef __INCLUDED_CLCD__
#endif
    
//The output register for the control pins
#ifndef LCD_CONTROL_PORT
#define CLCD_C_ -1
#undef __INCLUDED_CLCD__
#endif

//The output register for the data pins
#ifndef LCD_DATA_PORT
#define CLCD_C_ -1
#undef __INCLUDED_CLCD__
#endif

//The read register for the data pins
#ifndef LCD_DATA_PORT_READ
#define CLCD_C_ -1
#undef __INCLUDED_CLCD__
#endif

//The direction register for the data pins
#ifndef LCD_DATA_PORT_DIR
#define CLCD_C_ -1
#undef __INCLUDED_CLCD__
#endif

//The bit position of the e control pin
#ifndef LCD_E_PIN
#define CLCD_C_ -1
#undef __INCLUDED_CLCD__
#endif

//The bit position of the rs control pin
#ifndef LCD_RS_PIN
#define CLCD_C_ -1
#undef __INCLUDED_CLCD__
#endif

//The bit position of the rw control pin
#ifndef LCD_RW_PIN
#define CLCD_C_ -1
#undef __INCLUDED_CLCD__
#endif

//Position of the busy flag pin
#ifndef LCD_BUSY_FLAG_POSITION
#define LCD_BUSY_FLAG_POSITION  7
#warning clcd.h: LCD_BUSY_FLAG_POSITION is defaulted to 7, define LCD_BUSY_FLAG_POSITION in config file to change.
#endif

//If 4 bit mode, the positions of D6, D5, and D4 must be defined
#if defined(LCD_USE_4_BIT_MODE) && LCD_USE_4_BIT_MODE == 1
#if !defined(LCD_D6) || !defined(LCD_D5) || !defined(LCD_D4)
#define CLCD_C_ -1
#undef __INCLUDED_CLCD__
#endif
#endif
    
    
    
    
    
#if defined(__INCLUDED_CLCD__) && __INCLUDED_CLCD__ == 1

///Value for LCD omega symbol for cfah2004A family
#define LCD_OMEGA_SYMBOL			0xDE

///Value for left arrow for cfah2004A family
#define LCD_LEFT_ARROW				0b01111111

///Value for right arrow for cfah2004A family
#define LCD_RIGHT_ARROW				0b01111110

///Value for degrees symbol for cfah2004A family
#define LCD_DEGREES_UPPER_LEFT		223

///Value for degrees symbol  for cfah2004A family
#define LCD_DEGREES_LOWER_LEFT		0b10100001


///Backspace
#define LCD_BS					    0x08

///Horizontal Tab
#define LCD_TAB					    0x09

///Linefeed
#define LCD_LF					    0x0A

///Formfeed
#define LCD_FF					    0x0C

///Carriage return
#define LCD_CR					    0x0D

///Top of page
#define LCD_TOP					    0x0E

///Bottom of page
#define LCD_BOTTOM					0x0F

///Up 1 line
#define LCD_UP					    0x1C

///Down 1 line
#define LCD_DN					    0x19

///Right 1 char
#define LCD_RT					    0x1A

///Left 1 char
#define LCD_LFT					    0x1D

///End of Line
#define LCD_EOL					    0x17

///Clear screen command
#define LCD_CLEAR_SCREEN		    0x01

///Return home command
#define LCD_RETURN_HOME			    0x02

///Display off command
#define LCD_DISPLAY_OFF			    0x08

///Display on command, also is cursor off
#define LCD_DISPLAY_ON			    0x0C
#define LCD_CURSOR_OFF			    0x0C

///Cursor on command, also is blink off
#define LCD_CURSOR_ON			    0x0E
#define LCD_CUSOR_NO_BLINK		    0x0E

///Cursor blink command
#define LCD_CURSOR_BLINK		    0x0F

///Entire Display shift Right
#define LCD_DISPLAY_SHIFT_R			0x1C

///Entire Display shift left
#define LCD_DISPLAY_SHIFT_L			0x18

///Cursor shift Right
#define LCD_CURSOR_SHIFT_R			0x14

///Cursor shift left
#define LCD_CURSOR_SHIFT_L			0x10

///Command for LCD DD Ram
#define LCD_DD_RAM_CMD				0x80
    
///Command for LCD CG Ram
#define LCD_CG_RAM_CMD				0x40

///The value to send for resetting/initialization of the LCD.
#define LCD_INITIALIZATION_CMD      0x30
    
///LCD 8 bit mode setting cmd
#define LCD_MODE_8BIT				0x30

///LCD 4 bit mode setting cmd
#define LCD_MODE_4BIT				0x03


/*
    Function line, mode, font commands
    RS R/W      DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
    0   0        0   0   1   1   N   F   X   X

*/

///LCD 5x8 font, 8 bit mode, single line command
#define LCD_MODE_LINE_1_FONT_5x8_8BIT       LCD_Function_Set(1, 1, 1, 0, 0)

///LCD 5x11 font, 8 bit mode, single line command
#define LCD_MODE_LINE_1_FONT_5x11_8BIT      LCD_Function_Set(1, 0, 0, 0, 0)

///LCD 5x8 font, 8 bit mode, double line command
#define LCD_MODE_LINE_2_FONT_5x8_8BIT       0b00111000

///LCD 5x11 font, 8 bit mode, double line command
#define LCD_MODE_LINE_2_FONT_5x11_8BIT      0b00111100


///LCD 5x8 font, 4 bit mode, single line command
#define LCD_MODE_LINE_1_FONT_5x8_4BIT       0b00100000

///LCD 5x11 font, 4 bit mode, single line command
#define LCD_MODE_LINE_1_FONT_5x11_4BIT      0b00100100

///LCD 5x8 font, 4 bit mode, double line command
#define LCD_MODE_LINE_2_FONT_5x8_4BIT       0b00101000

///LCD 5x11 font, 4 bit mode, double line command
#define LCD_MODE_LINE_2_FONT_5x11_4BIT      0b00101100


    
///INITIALIZATION RELATED COMMANDS
#define LCD_Entry_Mode(x,y)				(0x04 | ((x & 0x01) << 1) | (y & 0x01))
#define LCD_Display_Mode(dp,c,b)		(0x08 | ((dp & 0x01) << 2) | ((c & 0x01) << 1) | (b & 0x01))
#define LCD_Shift_Mode(sc,rl)			(0x10 | ((sc & 0x01) << 3) | ((rc & 0x01) << 2))
#define LCD_Function_Set(dl,nV,fV,x,y)	(0x20 | ((dl & 0x01) << 4) | ((nV & 0x01) << 3) | ((fV & 0x01)<< 2) | ((x & 0x01)<<1) | (y & 0x01))

#define LCD_MOVE_R_NO_SHIFT				LCD_Entry_Mode(1, 0)
#define LCD_MOVE_R_SHIFT				LCD_Entry_Mode(1, 1)
#define LCD_MOVE_L_NO_SHIFT				LCD_Entry_Mode(0, 0)
#define LCD_MOVE_L_SHIFT				LCD_Entry_Mode(0, 1)

#define LCD_DISPLAY_OFF_CURSOR_OFF		LCD_Display_Mode(0,0,0)
#define LCD_DISPLAY_ON_NO_CURSOR  		LCD_Display_Mode(1,0,0)
#define LCD_DISPLAY_ON_NO_BLINK			LCD_Display_Mode(1,1,0)
#define LCD_DISPLAY_ON_CURSOR_BLINK		LCD_Display_Mode(1,1,1)


#if defined(LCD_USE_4_BIT_MODE) && LCD_USE_4_BIT_MODE == 1

#define LCD_4_BIT_DATA_PIN_MASK     ((1 << LCD_BUSY_FLAG_POSITION) | (1 << LCD_D6) | (1 << LCD_D5) | (1 << LCD_D4))
#define __LCD_4_BIT_WRITER_HELPER(d7, d6, d5, d4) ((d7 << LCD_BUSY_FLAG_POSITION) | (d6 << LCD_D6) | (d5 << LCD_D5) | (d4 << LCD_D4))
#define __LCD_4_BIT_VAL_WRITER_HELPER_HIGH(val) ((((val & 0x80) >> 7) << LCD_BUSY_FLAG_POSITION) | (((val & 0x40) >> 6) << LCD_D6) | (((val & 0x20) >> 5) << LCD_D5) | (((val & 0x10) >> 4) << LCD_D4))
#define __LCD_4_BIT_VAL_WRITER_HELPER_LOW(val) ((((val & 0x08) >> 3) << LCD_BUSY_FLAG_POSITION) | (((val & 0x04) >> 2) << LCD_D6) | (((val & 0x02) >> 1) << LCD_D5) | (((val & 0x01)) << LCD_D4))

#endif


///\deprecated
#define LCD_FONT5X7_8BIT				LCD_Function_Set(1, 1, 1, 0, 0)

///\deprecated
#define LCD_2LINE_5X7FONT_8BIT			LCD_Function_Set(1, 0, 0, 0, 0)

///\deprecated
#define LCD_FONT5X10_8BIT				LCD_Function_Set(1, 0, 1, 0, 0)

///\deprecated
#define LCD_2LINE_5X10FONT_8BIT			LCD_Function_Set(1, 0, 1, 0, 0)



extern void LcdConstInit(const unsigned char startupSequence[], const unsigned char lineStartPositions[]);
extern void LcdStoreCustomConstCharacter(unsigned char uchrAddress, const unsigned char auchrCharacter[8]);


extern void LcdInit(unsigned char startupSequence[], unsigned char lineStartPositions[]);
extern unsigned char LcdGetCurrentLine();
extern unsigned char LcdGetCurrentColumn();
extern void LcdBusyFlagWait();
extern void LcdPerformCommand(unsigned char cmd);
extern void LcdSendCommand(unsigned char cmd);
extern void LcdSendData(unsigned char data);

///Helper for sending the command for clearing the screen
#define LcdClearScreen()		        LcdPerformCommand(LCD_CLEAR_SCREEN)

///Helper for sending the command for returning to the home position
#define LcdReturnHome()			        LcdPerformCommand(LCD_RETURN_HOME)

///Helper for sending the command for moving the cursor left
#define LcdCursorLeft()			        LcdPerformCommand(LCD_LFT)

///Helper for sending the command for moving the cursor right
#define LcdCursorRight()		        LcdPerformCommand(LCD_RT)	

///Helper for sending the command for moving the cursor up
#define LcdCursorUp()			        LcdPerformCommand(LCD_UP)

///Helper for sending the command for moving the cursor down
#define LcdCursorDown()			        LcdPerformCommand(LCD_DN)	

///Helper for sending the command for running the back space command
#define LcdBackspace()			        LcdPerformCommand(LCD_BS)	

///Helper for sending the command for moving to the top line at the current column
#define LcdToTop()				        LcdPerformCommand(LCD_TOP)

///Helper for sending the command for turning the display off
#define LcdDisplayOff()			        LcdPerformCommand(LCD_DISPLAY_OFF)

///Helper for setting if the Lcd is turned on or turned off
#define LcdSetOnOff(state)				LcdPerformCommand(((state == 0) ? LCD_DISPLAY_OFF : LCD_DISPLAY_ON))

///Helper for sending commands for the character generator ram
#define LCD_set_cg_ram(val)				LcdSendCommand(LCD_CG_RAM_CMD | (val & 0x3F))

///Helper for sending commands for the DD ram
#define LCD_set_dd_ram(val)				LcdSendCommand(LCD_DD_RAM_CMD | (val))

///Helper for turning the cursor OFF
#define LcdCursorOff()					LcdSendCommand(LCD_DISPLAY_ON_NO_CURSOR)

///Helper for turning the cursor On without a blink
#define LcdCursorOn()					LcdSendCommand(LCD_DISPLAY_ON_NO_BLINK)

///Helper for turning the cursor On with a blink
#define LcdBlinkingCursorOn()			LcdSendCommand(LCD_DISPLAY_ON_CURSOR_BLINK)


extern void LcdStoreCGData(unsigned char cgAddress, unsigned char data[], uint8_t dataLength);
extern void LcdDisplayOn(bool cursorOn, bool cursorBlink);
extern void LcdClearLine(unsigned char uchrLine);
extern void LcdClearLineFromColumn(unsigned char uchrLine, unsigned char uchrColumn);
extern void LcdClearLineAtColumns(unsigned char uchrLine, unsigned char uchrStartColumn, unsigned char uchrEndColumn);
extern void LcdClearPosition(unsigned char uchrLine, unsigned char uchrColumn);
extern void LcdStoreDotRow(unsigned char uchrAddress, unsigned char uchrNewDot);
extern void LcdStoreCustomCharacter(unsigned char uchrAddress, unsigned char auchrCharacter[8]);
extern unsigned char LcdGetAddressCounter();
extern void LcdGoToPosition(unsigned char uchrLine, unsigned char uchrColumn);

extern void LcdSendByte(unsigned char uchrByte);
extern void LcdSendByteDelay(unsigned char uchrByte, unsigned short ushtDelayTime);
extern void LcdSendByteAtPosition(unsigned char uchrByte, unsigned char uchrRow, unsigned char uchrColumn);
extern void LcdSendByteDelayAtPosition(unsigned char uchrByte, unsigned char uchrRow, unsigned char uchrColumn, unsigned short ushtDelayTime);

extern void LcdPrintChar(char uchrChar);
extern void LcdPrintCharDelay(char uchrChar, unsigned short ushtDelayTime);
extern void LcdPrintCharAtPosition(char uchrChar, unsigned char uchrRow, unsigned char uchrColumn);
extern void LcdPrintCharDelayAtPosition(char uchrChar, unsigned char uchrRow, unsigned char uchrColumn, unsigned short ushtDelayTime);
extern void LcdPrintString(char* strToSend);
extern void LcdPrintStringDelay(char* strToSend, unsigned short ushtDelayTime);
extern void LcdPrintStringAtPosition(char* strToSend, unsigned char uchrRow, unsigned char uchrColumn);
extern void LcdPrintStringDelayAtPosition(char* strToSend, unsigned char uchrRow, unsigned char uchrColumn, unsigned short ushtDelayTime);

extern void LcdPrint(char* strToSend);
extern void LcdPrintDelay(char* strToSend, unsigned short ushtDelayTime);
extern void LcdPrintAtPosition(char* strToSend, unsigned char uchrRow, unsigned char uchrColumn);
extern void LcdPrintDelayAtPosition(char* strToSend, unsigned char uchrRow, unsigned char uchrColumn, unsigned short ushtDelayTime);

extern void LcdPrintNumericalByte(uint8_t numVal);
extern void LcdPrintNumericalByteDelay(uint8_t numVal, unsigned short ushtDelayTime);
extern void LcdPrintNumericalByteAtPosition(uint8_t numVal, unsigned char uchrRow, unsigned char uchrColumn);
extern void LcdPrintNumericalByteDelayAtPosition(uint8_t numVal, unsigned char uchrRow, unsigned char uchrColumn, unsigned short ushtDelayTime);

extern void LcdPrintNumericalShort(uint16_t numVal);
extern void LcdPrintNumericalShortDelay(uint16_t numVal, unsigned short ushtDelayTime);
extern void LcdPrintNumericalShortAtPosition(uint16_t numVal, unsigned char uchrRow, unsigned char uchrColumn);
extern void LcdPrintNumericalShortDelayAtPosition(uint16_t numVal, unsigned char uchrRow, unsigned char uchrColumn, unsigned short ushtDelayTime);

extern void LcdDisplayByteHex(uint8_t byteValue);
extern void LcdDisplayByteBinary(uint8_t byteValue);





#elif defined(LCD_SHOW_DEFINE_ERRORS) && LCD_SHOW_DEFINE_ERRORS == 1

//ERROR CHECKING

//The amount of columns on the display
#ifndef LCD_COLUMN_COUNT
#error clcd.h: LCD_COLUMN_COUNT must be defined to use file.
#endif

//The amount of rows on the display
#ifndef LCD_ROW_COUNT
#error clcd.h: LCD_ROW_COUNT must be defined to use file.
#endif
    
//The output register for the control pins
#ifndef LCD_CONTROL_PORT
#error clcd.h: LCD_CONTROL_PORT must be defined to use file.
#endif

//The output register for the data pins
#ifndef LCD_DATA_PORT
#error clcd.h: LCD_DATA_PORT must be defined to use file.
#endif

//The read register for the data pins
#ifndef LCD_DATA_PORT_READ
#error clcd.h: LCD_DATA_PORT_READ must be defined to use file.
#endif

//The direction register for the data pins
#ifndef LCD_DATA_PORT_DIR
#error clcd.h: LCD_DATA_PORT_DIR must be defined to use file.
#endif

//The bit position of the e control pin
#ifndef LCD_E_PIN
#error clcd.h: LCD_E_PIN must be defined to use file.
#endif

//The bit position of the rs control pin
#ifndef LCD_RS_PIN
#error clcd.h: LCD_RS_PIN must be defined to use file.
#endif

//The bit position of the rw control pin
#ifndef LCD_RW_PIN
#error clcd.h: LCD_RW_PIN must be defined to use file.
#endif

//If 4 bit mode, the positions of D6, D5, and D4 must be defined
#if defined(LCD_USE_4_BIT_MODE) && LCD_USE_4_BIT_MODE == 1

#if !defined(LCD_D6)
#error clcd.h: LCD_D6 must be defined to use file.
#endif

#if !defined(LCD_D5)
#error clcd.h: LCD_D5 must be defined to use file.
#endif

#if !defined(LCD_D4)
#error clcd.h: LCD_D4 must be defined to use file.
#endif

#endif


#else



#warning clcd.h: Check required definitions to include file of define LCD_SHOW_DEFINE_ERRORS as 1 in config file.



#endif



#ifdef __cplusplus
}
#endif





#endif