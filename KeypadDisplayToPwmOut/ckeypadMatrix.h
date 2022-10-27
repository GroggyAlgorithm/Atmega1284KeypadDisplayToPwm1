/**
 * \file ckeypadMatrix.h
 * \author Tim Robbins
 * \brief header file for keypad interfacing \n
 * REQUIREMENTS: \n
 * "config.h", "mcuUtils.h", and "mcuDelays.h" must be included. \n
 * KP_COLUMN_PORT, KP_COLUMN_READ, KP_COLUMN_DIR, KP_ROW_PORT, KP_ROW_READ, KP_ROW_DIR, KP_COLUMN_PIN_MSK, and KP_ROW_PIN_MSK must be defined.
 */
#include "config.h"

#ifndef __CKEYPADMATRIX_H__

#define __CKEYPADMATRIX_H__ 1
#define __INCLUDED_CKEYPADMATRIX__  1

#ifdef __cplusplus
extern "C" {
#endif



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


#include "mcuUtils.h"
#include "mcuDelays.h"

#ifndef KP_COLUMN_PORT
//#warning ckeypadMatrix.h: KP_COLUMN_PORT must be defined as the ports output register to use
#define __CKEYPADMATRIX_C__ -1
#undef __INCLUDED_CKEYPADMATRIX__
#endif

#ifndef KP_COLUMN_READ
//#warning ckeypadMatrix.h: KP_COLUMN_READ must be defined as the ports read register to use
#define __CKEYPADMATRIX_C__ -1
#undef __INCLUDED_CKEYPADMATRIX__
#endif

#ifndef KP_COLUMN_DIR
//#warning ckeypadMatrix.h: KP_COLUMN_DIR must be defined as the ports direction register to use
#define __CKEYPADMATRIX_C__ -1
#undef __INCLUDED_CKEYPADMATRIX__
#endif

#ifndef KP_ROW_PORT
//#warning ckeypadMatrix.h: KP_ROW_PORT must be defined as the ports output register to use
#define __CKEYPADMATRIX_C__ -1
#undef __INCLUDED_CKEYPADMATRIX__
#endif

#ifndef KP_ROW_READ
//#warning ckeypadMatrix.h: KP_ROW_READ must be defined as the ports read register to use
#define __CKEYPADMATRIX_C__ -1
#undef __INCLUDED_CKEYPADMATRIX__
#endif

#ifndef KP_ROW_DIR
//#warning ckeypadMatrix.h: KP_ROW_DIR must be defined as the ports direction register to use
#define __CKEYPADMATRIX_C__ -1
#undef __INCLUDED_CKEYPADMATRIX__
#endif

#ifndef KP_COLUMN_PIN_MSK
//#warning ckeypadMatrix.h: KP_COLUMN_PIN_MSK must be defined to use. Example: (1 << 3 | 1 << 4...
#define __CKEYPADMATRIX_C__ -1
#undef __INCLUDED_CKEYPADMATRIX__
#endif

#ifndef KP_ROW_PIN_MSK
//#warning ckeypadMatrix.h: KP_ROW_PIN_MSK must be defined to use. Example: (1 << 3 | 1 << 4...)
#define __CKEYPADMATRIX_C__ -1
#undef __INCLUDED_CKEYPADMATRIX__
#endif




#if __CKEYPADMATRIX_C__ != -1

#ifndef KP_COLUMNS
//#warning ckeypadMatrix.h: KP_COLUMNS must be defined for the amount of column pins. Defaulting to 3
#define KP_COLUMNS	            3
#endif

#ifndef KP_ROWS
//#warning ckeypadMatrix.h: KP_ROWS must be defined for the amount of row pins. Defaulting to 4
#define KP_ROWS	                4
#endif


extern uint8_t kp_Scan_const(const unsigned char uchrColumnPinPositions[KP_COLUMNS],
const unsigned char uchrRowPinPositions[KP_ROWS], const unsigned char uchrKeypadValues[KP_ROWS][KP_COLUMNS]);

extern uint8_t kp_Scan(unsigned char uchrColumnPinPositions[KP_COLUMNS],
unsigned char uchrRowPinPositions[KP_ROWS], unsigned char uchrKeypadValues[KP_ROWS][KP_COLUMNS]);



#else

#warning ckeypadMatrix.h: Check Required macro definitions to include functionality.

#endif

#ifdef __cplusplus
}
#endif

#endif /* __CKEYPADMATRIX_H__ */