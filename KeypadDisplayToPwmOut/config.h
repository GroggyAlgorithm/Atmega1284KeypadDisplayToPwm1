/**
 * \file config.h
 * \author Tim Robbins
 * \brief The project configuration file for project definitions.
 */
#ifndef CONFIG_H_
#define CONFIG_H_   1

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */


///The baud rate for serial communications
#define BAUD							1200

#if defined(__XC)

///The frequency being used for the controller
#define _XTAL_FREQ                                  64000000

#else

///The frequency being used for the controller
#define F_CPU                                       12000000UL

#endif

#include "mcuPinUtils.h"

//#define LCD_USE_4_BIT_MODE			0
//#define LCD_SHOW_DEFINE_ERRORS		0
//#define LCD_D6						6
//#define LCD_D5						5
//#define LCD_D4						4

#define LCD_COLUMN_COUNT				20
#define LCD_ROW_COUNT					4

#define LCD_CONTROL_PORT				_GET_OUTPUT_REG(D)
#define LCD_RS_PIN						2
#define LCD_RW_PIN						3
#define LCD_E_PIN						6

#define LCD_DATA_PORT					_GET_OUTPUT_REG(B)
#define LCD_DATA_PORT_READ				_GET_READ_REG(B)
#define LCD_DATA_PORT_DIR				_GET_DIR_REG(B)
#define LCD_BUSY_FLAG_POSITION			7

#define KP_COLUMN_PORT					_GET_OUTPUT_REG(A)
#define KP_COLUMN_READ					_GET_READ_REG(A)
#define KP_COLUMN_DIR					_GET_DIR_REG(A)

#define KP_COLUMN_PIN_MSK				0b00000111

#define KP_ROW_PORT						_GET_OUTPUT_REG(C)
#define KP_ROW_READ						_GET_READ_REG(C)
#define KP_ROW_DIR						_GET_DIR_REG(C)

#define KP_ROW_PIN_MSK					0b11000011

#define KP_COLUMNS						3
#define KP_ROWS							4








#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

