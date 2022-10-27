/**
 * \file mcuPinUtils.h
 * \author Tim Robbins
 *
 * \brief Macros and such for pin related utilities
 * \todo Started adding helpers for interrupt vectors, need to finish maybe
 */ 
#ifndef MCUPINUTILS_H_
#define MCUPINUTILS_H_ 1

#include "mcuUtils.h"

#ifdef __AVR

#include <avr/io.h>

#define __PIN_UTIL_PREFIX_READ_REG          PIN
#define __PIN_UTIL_PREFIX_DIR_REG           DDR
#define __PIN_UTIL_PREFIX_WRITE_REG         PORT
#define __PIN_UTIL_PIN_CHANGE_INT_PREFIX    PCINT
#define __PIN_UTIL_EXT_INT_PREFIX           INT
#define __PIN_UTIL_WDT_INT_PREFIX           WDT
#define __PIN_UTIL_INT_VECT_POSTFIX         _vect

#elif defined(__XC)

#include <xc.h>        /* XC8 General Include File */

#define __PIN_UTIL_PREFIX_READ_REG    PORT
#define __PIN_UTIL_PREFIX_DIR_REG     TRIS
#define __PIN_UTIL_PREFIX_WRITE_REG   LAT

#elif defined(HI_TECH_C)

#include <htc.h>       /* HiTech General Include File */

#define __PIN_UTIL_PREFIX_READ_REG    PORT
#define __PIN_UTIL_PREFIX_DIR_REG     TRIS
#define __PIN_UTIL_PREFIX_WRITE_REG   LAT

#elif defined(__18CXX)

#include <p18cxxx.h>   /* C18 General Include File */

#define __PIN_UTIL_PREFIX_READ_REG    PORT
#define __PIN_UTIL_PREFIX_DIR_REG     TRIS
#define __PIN_UTIL_PREFIX_WRITE_REG   LAT

#elif (defined __XC8)

#include <xc.h>            /* XC8 General Include File */

#define __PIN_UTIL_PREFIX_READ_REG    PORT
#define __PIN_UTIL_PREFIX_DIR_REG     TRIS
#define __PIN_UTIL_PREFIX_WRITE_REG   LAT

#endif





#define _NO_PIN_FUNC    -1


#pragma region PIN_CHECKS

#ifdef PORTA

#ifdef PINA0
#define PIN_A0 A, 0
#endif

#ifdef PINA1
#define PIN_A1 A, 1
#endif

#ifdef PINA2
#define PIN_A2 A, 2
#endif

#ifdef PINA3
#define PIN_A3 A, 3
#endif

#ifdef PINA4
#define PIN_A4 A, 4
#endif

#ifdef PINA5
#define PIN_A5 A, 5
#endif

#ifdef PINA6
#define PIN_A6 A, 6
#endif

#ifdef PINA7
#define PIN_A7 A, 7
#endif

#endif

#ifdef PORTB

#ifdef PINB0
#define PIN_B0 B, 0
#endif

#ifdef PINB1
#define PIN_B1 B, 1
#endif

#ifdef PINB2
#define PIN_B2 B, 2
#endif

#ifdef PINB3
#define PIN_B3 B, 3
#endif

#ifdef PINB4
#define PIN_B4 B, 4
#endif

#ifdef PINB5
#define PIN_B5 B, 5
#endif

#ifdef PINB6
#define PIN_B6 B, 6
#endif

#ifdef PINB7
#define PIN_B7 B, 7
#endif

#endif

#ifdef PORTC

#ifdef PINC0
#define PIN_C0 C, 0
#endif

#ifdef PINC1
#define PIN_C1 C, 1
#endif

#ifdef PINC2
#define PIN_C2 C, 2
#endif

#ifdef PINC3
#define PIN_C3 C, 3
#endif

#ifdef PINC4
#define PIN_C4 C, 4
#endif

#ifdef PINC5
#define PIN_C5 C, 5
#endif

#ifdef PINC6
#define PIN_C6 C, 6
#endif

#ifdef PINC7
#define PIN_C7 C, 7
#endif

#endif

#ifdef PORTD

#ifdef PIND0
#define PIN_D0 D, 0
#endif

#ifdef PIND1
#define PIN_D1 D, 1
#endif

#ifdef PIND2
#define PIN_D2 D, 2
#endif

#ifdef PIND3
#define PIN_D3 D, 3
#endif

#ifdef PIND4
#define PIN_D4 D, 4
#endif

#ifdef PIND5
#define PIN_D5 D, 5
#endif

#ifdef PIND6
#define PIN_D6 D, 6
#endif

#ifdef PIND7
#define PIN_D7 D, 7
#endif

#endif

#ifdef PORTE

#ifdef PINE0
#define PIN_E0 E, 0
#endif

#ifdef PINE1
#define PIN_E1 E, 1
#endif

#ifdef PINE2
#define PIN_E2 E, 2
#endif

#ifdef PINE3
#define PIN_E0 E, 3
#endif

#ifdef PINE4
#define PIN_E1 E, 4
#endif

#ifdef PINE5
#define PIN_E2 E, 5
#endif

#ifdef PINE6
#define PIN_E0 E, 6
#endif

#ifdef PINE7
#define PIN_E1 E, 7
#endif


#endif



#ifdef PORTF

#ifdef PINF0
#define PIN_F0 F, 0
#endif

#ifdef PINF1
#define PIN_F1 F, 1
#endif

#ifdef PINF2
#define PIN_F2 F, 2
#endif

#ifdef PINF3
#define PIN_F0 F, 3
#endif

#ifdef PINF4
#define PIN_F1 F, 4
#endif

#ifdef PINF5
#define PIN_F2 F, 5
#endif

#ifdef PINF6
#define PIN_F0 F, 6
#endif

#ifdef PINF7
#define PIN_F1 F, 7
#endif


#endif

#pragma endregion

#pragma region ADC_CHECKS

#ifdef ADC0D
#define ADC_0 0
#endif

#ifdef ADC1D
#define ADC_1 1
#endif

#ifdef ADC2D
#define ADC_2 2
#endif

#ifdef ADC3D
#define ADC_3 3
#endif

#ifdef ADC4D
#define ADC_4 4
#endif

#ifdef ADC5D
#define ADC_5 5
#endif

#ifdef ADC6D
#define ADC_6 6
#endif

#ifdef ADC7D
#define ADC_7 7
#endif

#ifdef ADC8D
#define ADC_8 8
#endif

#ifdef ADC9D
#define ADC_9 9
#endif

#ifdef ADC10D
#define ADC_10 10
#endif

#pragma endregion

#pragma region INTERRUPT_VECT_CHECKS

#ifdef PCINT0_vect

#define PCINT_0_TO_7_VECT  PCINT0_vect

#endif

#ifdef PCINT1_vect

#define PCINT_8_TO_15_VECT  PCINT1_vect

#endif

#ifdef PCINT2_vect

#define PCINT_16_TO_23_VECT  PCINT2_vect

#endif

#ifdef PCINT3_vect

#define PCINT_24_TO_31_VECT  PCINT3_vect

#endif



#ifdef PCMSK0

#define PCINT_0_TO_7_MASK  PCMSK0

#endif

#ifdef PCMSK1

#define PCINT_8_TO_15_MASK  PCMSK1

#endif

#ifdef PCMSK2

#define PCINT_16_TO_23_MASK  PCMSK2

#endif

#ifdef PCMSK3

#define PCINT_24_TO_31_MASK  PCMSK3

#endif


#pragma endregion




#if defined(__AVR_ATmega16M1__) || defined(__AVR_ATmega32M1__) || defined(__AVR_ATmega64M1__)

#define P4   _NO_PIN_FUNC
#define P5   _NO_PIN_FUNC
#define P19  _NO_PIN_FUNC
#define P20  _NO_PIN_FUNC
#define P21  _NO_PIN_FUNC


#define TEMPERATURE_SENSOR 11

#define P1 PIN_D2
#define MISO_A_PIN PIN_D2
#define OC1A_PIN PIN_D2
#define PSCIN2_PIN PIN_D2

#define P2 PIN_D3
#define MOSI_A_PIN PIN_D3
#define TX_PIN PIN_D3
#define TXD_PIN PIN_D3
#define TXLIN_PIN PIN_D3
#define OC0A_PIN PIN_D3
#define SS_PIN PIN_D3

#define P3 PIN_C1
#define OC1B_PIN PIN_C1
#define SS_A_PIN PIN_C1
#define PSCIN1 PIN_C1

#define P6 PIN_C2
#define TXCAN_PIN PIN_C2
#define T0_PIN PIN_C2

#define P7 PIN_C3
#define RXCAN_PIN PIN_C3
#define T1_PIN PIN_C3
#define ICP1B_PIN PIN_C3

#define P8 PIN_B0
#define MISO_PIN PIN_B0
#define PCINT0_PIN PIN_B0
#define PSCOUT2A_PIN PIN_B0

#define P9 PIN_B1
#define MOSI_PIN PIN_B1
#define PSCOUT2B_PIN PIN_B1
#define PCINT1_PIN PIN_B1

#define P10 PIN_E1
#define XTAL1_PIN PIN_E1
#define OC0B_PIN PIN_E1

#define P11 PIN_E2
#define XTAL2_PIN PIN_E2
#define ADC0_PIN PIN_E2
#define PIN_E2_ADC	0

#define P12 PIN_D4
#define SCK_A_PIN PIN_D4
#define RX_PIN PIN_D4
#define RXD_PIN PIN_D4
#define RXDD_PIN PIN_D4
#define ADC1_PIN PIN_D4
#define RXLIN_PIN PIN_D4
#define ICP1A_PIN PIN_D4
#define PIN_D4_ADC	1	

#define P13 PIN_D5
#define ADC2_PIN PIN_D5
#define ACMP2_PIN PIN_D5
#define PIN_D5_ADC	2

#define P14 PIN_D6
#define ADC3_PIN PIN_D6
#define ACMP2N_PIN PIN_D6
#define INT0_PIN PIN_D6
#define PIN_D6_ADC	3

#define P15 PIN_D7
#define ACMP0_PIN PIN_D7

#define P16 PIN_B2
#define ADC5_PIN PIN_B2
#define INT1_PIN PIN_B2
#define ACMPN0_PIN PIN_B2
#define PCINT2_PIN PIN_B2
#define PIN_B2_ADC	5

#define P17 PIN_C4
#define ADC8_PIN PIN_C4
#define ACMPN3_PIN PIN_C4
#define AMP1_NEG_PIN PIN_C4
#define PIN_C4_ADC	8

#define P18 PIN_C5
#define ADC9_PIN PIN_C5
#define AMP1_POS_PIN PIN_C5
#define ACMP3_PIN PIN_C5
#define PIN_C5_ADC	9

#define P22 PIN_C6
#define ADC10_PIN PIN_C6
#define ACMP1_PIN PIN_C6
#define PIN_C6_ADC	10

#define P23 PIN_B3
#define AMP0_NEG_PIN PIN_B3
#define PCINT3_PIN PIN_B3

#define P24 PIN_B4
#define AMP0_POS_PIN PIN_B4
#define PCINT4_PIN PIN_B4

#define P25 PIN_C7
#define D2A_PIN PIN_C7
#define AMP2_POS_PIN PIN_C7

#define P26 PIN_B5
#define ADC6_PIN PIN_B5
#define INT2_PIN PIN_B5
#define AMP2_NEG_PIN PIN_B5
#define ACMPN1_PIN PIN_B5
#define PIN_B5_ADC	6

#define P27 PIN_B6
#define ADC7_PIN PIN_B6
#define PSCOUT1B_PIN PIN_B6
#define PIN_B6_ADC	7

#define P28 PIN_B7
#define SCK_PIN PIN_B7
#define ADC4_PIN PIN_B7
#define PSCOUT0B_PIN PIN_B7
#define PIN_B7_ADC	4

#define P29 PIN_D0
#define PSCOUT0A_PIN PIN_D0

#define P30 PIN_C0
#define PSCOUT1A_PIN PIN_C0
#define INT3_PIN PIN_C0

#define P31 PIN_E0
#define OCD_PIN PIN_E0
#define RESET_PIN PIN_E0

#define P32 PIN_D1
#define CLKO_PIN PIN_D1
#define PSCIN0_PIN PIN_D1



#elif defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164PA__) || defined(__AVR_ATmega324A__) || defined(__AVR_ATmega324PA__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644PA__) || defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)


#define P9              _NO_PIN_FUNC
#define P10             _NO_PIN_FUNC
#define P11             _NO_PIN_FUNC
#define P12             _NO_PIN_FUNC
#define P13             _NO_PIN_FUNC
#define P30             _NO_PIN_FUNC
#define P31             _NO_PIN_FUNC
#define P32             _NO_PIN_FUNC


#define P1_PCINT_NUM        8
#define T0_PCINT_NUM        8
#define XCK0_PCINT_NUM      8

#define P2_PCINT_NUM        9
#define CLKO_PCINT_NUM      9
#define T1_PCINT_NUM        9

#define P3_PCINT_NUM        10
#define AIN0_PCINT_NUM      10

#define P4_PCINT_NUM        11
#define OC0A_PCINT_NUM      11
#define AIN1_PCINT_NUM      11

#define P5_PCINT_NUM        12
#define OC0B_PCINT_NUM      12
#define SS_PCINT_NUM        12


#define P1_PCINT_VECT        PCINT_8_TO_15_VECT
#define T0_PCINT_VECT        PCINT_8_TO_15_VECT
#define XCK0_PCINT_VECT      PCINT_8_TO_15_VECT

#define P2_PCINT_VECT        PCINT_8_TO_15_VECT
#define CLKO_PCINT_VECT      PCINT_8_TO_15_VECT
#define T1_PCINT_VECT        PCINT_8_TO_15_VECT

#define P3_PCINT_VECT        PCINT_8_TO_15_VECT
#define AIN0_PCINT_VECT      PCINT_8_TO_15_VECT

#define P4_PCINT_VECT        PCINT_8_TO_15_VECT
#define OC0A_PCINT_VECT      PCINT_8_TO_15_VECT
#define AIN1_PCINT_VECT      PCINT_8_TO_15_VECT

#define P5_PCINT_VECT        PCINT_8_TO_15_VECT
#define OC0B_PCINT_VECT      PCINT_8_TO_15_VECT
#define SS_PCINT_VECT        PCINT_8_TO_15_VECT





#define P1              PIN_B0
#define XCK0_PIN        PIN_B0
#define T0_PIN          PIN_B0
#define PCINT8_PIN      PIN_B0

#define P2              PIN_B1
#define CLKO_PIN        PIN_B1
#define T1_PIN          PIN_B1
#define PCINT9_PIN      PIN_B1

#define P3              PIN_B2
#define AIN0_PIN        PIN_B2
#define INT2_PIN        PIN_B2
#define PCINT10_PIN     PIN_B2

#define P4              PIN_B3
#define OC0A_PIN        PIN_B3
#define AIN1_PIN        PIN_B3
#define PCINT11_PIN     PIN_B3

#define P5              PIN_B4
#define OC0B_PIN        PIN_B4
#define SS_PIN          PIN_B4
#define PCINT12_PIN     PIN_B4

#define P6 PIN_B5
#define MOSI_PIN PIN_B5
#define ICP3_PIN PIN_B5
#define PCINT13_PIN PIN_B5

#define P7 PIN_B6
#define MISO_PIN PIN_B6
#define OC3A_PIN PIN_B6
#define PCINT14_PIN PIN_B6

#define P8 PIN_B7
#define PCINT15_PIN PIN_B7
#define OC3B_PIN PIN_B7
#define SCK_PIN PIN_B7

#define P14 PIN_D0
#define T3_PIN PIN_D0
#define RX0_PIN PIN_D0
#define RXD0_PIN PIN_D0
#define PCINT24_PIN PIN_D0

#define P15 PIN_D1
#define TX0_PIN PIN_D1
#define TXD0_PIN PIN_D1
#define PCINT25_PIN PIN_D1

#define P16 PIN_D2
#define RXD1_PIN PIN_D2
#define RX1_PIN PIN_D2

#define P17 PIN_D3
#define TXD1_PIN PIN_D3
#define TX1_PIN PIN_D3

#define P18 PIN_D4
#define OC1B_PIN PIN_D4
#define XCK1_PIN PIN_D4

#define P19 PIN_D5
#define OC1A_PIN PIN_D5

#define P20 PIN_D6
#define OC2B_PIN PIN_D6
#define ICP_PIN PIN_D6

#define P21 PIN_D7
#define OC2A_PIN PIN_D7

#define P22 PIN_C0
#define SCL_PIN PIN_C0

#define P23 PIN_C1
#define SDA_PIN PIN_C1

#define P24 PIN_C2
#define TCK_PIN PIN_C2

#define P25 PIN_C3
#define TMS_PIN PIN_C3

#define P26 PIN_C4
#define TDO_PIN PIN_C4

#define P27 PIN_C5
#define TDI_PIN PIN_C5

#define P28 PIN_C6
#define TOSC1_PIN PIN_C6

#define P29 PIN_C7
#define TOSC2_PIN PIN_C7

#define P33 PIN_A7
#define ADC7_PIN PIN_A7

#define P34 PIN_A6
#define ADC6_PIN PIN_A6

#define P35 PIN_A5
#define ADC5_PIN PIN_A5

#define P36 PIN_A4
#define ADC4_PIN PIN_A4

#define P37 PIN_A3
#define ADC3_PIN PIN_A3

#define P38 PIN_A2
#define ADC2_PIN PIN_A2

#define P39 PIN_A1
#define ADC1_PIN PIN_A1

#define P40 PIN_A0
#define ADC0_PIN PIN_A0


#elif defined(__AVR_ATmega328P__)

#define P7   _NO_PIN_FUNC
#define P8   _NO_PIN_FUNC
#define P20  _NO_PIN_FUNC
#define P21  _NO_PIN_FUNC
#define P22  _NO_PIN_FUNC


#define P1 PIN_C6
#define RESET_PIN PIN_C6
#define PCINT14_PIN PIN_C6

#define P2 PIN_D0
#define RXD_PIN PIN_D0
#define PCINT16_PIN PIN_D0

#define P3 PIN_D1
#define TXD_PIN PIN_D1
#define PCINT17_PIN PIN_D1

#define P4 PIN_D2
#define INT0_PIN PIN_D2
#define PCINT18_PIN PIN_D2

#define P5 PIN_D3
#define OC2B_PIN PIN_D3
#define INT1_PIN PIN_D3
#define PCINT19_PIN PIN_D3

#define P6 PIN_D4
#define XCK_PIN PIN_D4
#define T0_PIN PIN_D4
#define PCINT20_PIN PIN_D4

#define P9 PIN_B6
#define XTAL1_PIN PIN_B6
#define TOSC1_PIN PIN_B6
#define PCINT6_PIN PIN_B6

#define P10 PIN_B7
#define XTAL2_PIN PIN_B7
#define TOSC2_PIN PIN_B7
#define PCINT7_PIN PIN_B7

#define P11 PIN_D5
#define OC0B_PIN PIN_D5
#define T1_PIN PIN_D5
#define PCINT21_PIN PIN_D5

#define P12 PIN_D6
#define OC0A_PIN PIN_D6
#define AIN0_PIN PIN_D6
#define PCINT22_PIN PIN_D6

#define P13 PIN_D7
#define AIN1_PIN PIN_D7
#define PCINT23_PIN PIN_D7

#define P14 PIN_B0
#define CLKO_PIN PIN_B0
#define ICP1_PIN PIN_B0
#define PCINT0_PIN PIN_B0

#define P15 PIN_B1
#define OC1A_PIN PIN_B1
#define PCINT1_PIN PIN_B1

#define P16 PIN_B2
#define SS_PIN PIN_B2
#define OC1B_PIN PIN_B2
#define P16_PIN PIN_B2
#define PCINT2_PIN PIN_B2

#define P17 PIN_B3
#define MOSI_PIN PIN_B3
#define OC2A_PIN PIN_B3
#define PCINT3_PIN PIN_B3

#define P18 PIN_B4
#define MISO_PIN PIN_B4
#define PCINT4_PIN PIN_B4

#define P19 PIN_B5
#define SCK_PIN PIN_B5
#define PCINT5_PIN PIN_B5

#define P23 PIN_C0
#define ADC0_PIN PIN_C0
#define PCINT8_PIN PIN_C0

#define P24 PIN_C1
#define ADC1_PIN PIN_C1
#define PCINT9_PIN PIN_C1

#define P25 PIN_C2
#define ADC2_PIN PIN_C2
#define PCINT10_PIN PIN_C2

#define P26 PIN_C3
#define ADC3_PIN PIN_C3
#define PCINT11_PIN PIN_C3

#define P27 PIN_C4
#define ADC4_PIN PIN_C4
#define PCINT12_PIN PIN_C4
#define SDA_PIN PIN_C4

#define P28 PIN_C5
#define ADC5_PIN PIN_C5
#define PCINT13_PIN PIN_C5
#define SCL_PIN PIN_C5



#endif









///Helper for tokenizing 
#define __PIN_UTIL_TOKENIZE_REG_NAME(reg, t)	_TOKENIZE(reg, t)

///Helper for tokenizing 
#define __PIN_UTIL_TOKENIZE_INT_NAME(inttype, n) __PIN_UTIL_TOKENIZE_REG_NAME(_TOKENIZE(inttype, n), __PIN_UTIL_INT_VECT_POSTFIX)

///Helper for getting the pin change interrupt related to the pin change interrupt passed
#define _GET_PCINT_VECT(n)   __PIN_UTIL_TOKENIZE_INT_NAME(__PIN_UTIL_PIN_CHANGE_INT_PREFIX, n)





//#pragma region PINS&PORTS

///Abstraction macro for variable argument pin high macros
#define _PIN_HIGHV2(pL, ...)		__PIN_UTIL_TOKENIZE_REG_NAME(__PIN_UTIL_PREFIX_WRITE_REG, pL) |= VFUNC(_BUILDVALV, __VA_ARGS__)

///Abstraction macro for variable argument pin low macros
#define _PIN_LOWV2(pL, ...)			__PIN_UTIL_TOKENIZE_REG_NAME(__PIN_UTIL_PREFIX_WRITE_REG, pL) &= ~VFUNC(_BUILDVALV, __VA_ARGS__)

///Abstraction macro for variable argument pin input/output macros
#define _PIN_DIR_HIGHV2(pL, ...)	__PIN_UTIL_TOKENIZE_REG_NAME(__PIN_UTIL_PREFIX_DIR_REG, pL) |= VFUNC(_BUILDVALV, __VA_ARGS__)

///Abstraction macro for variable argument pin input/output macros
#define _PIN_DIR_LOWV2(pL, ...)		__PIN_UTIL_TOKENIZE_REG_NAME(__PIN_UTIL_PREFIX_DIR_REG, pL) &= ~(VFUNC(_BUILDVALV, __VA_ARGS__))

///Abstraction macro for port high macros
#define _PORT_DIR_HIGH(pL)			__PIN_UTIL_TOKENIZE_REG_NAME(__PIN_UTIL_PREFIX_DIR_REG, pL) |= 0xFF

///Abstraction macro for port low macros
#define _PORT_DIR_LOW(pL)			__PIN_UTIL_TOKENIZE_REG_NAME(__PIN_UTIL_PREFIX_DIR_REG, pL) &= ~(0xFF)

///Abstraction macro for reading pin value macros
#define _READ_PIN(pL, pN)			readBit(__PIN_UTIL_TOKENIZE_REG_NAME(__PIN_UTIL_PREFIX_READ_REG, pL), pN)

///Abstraction macro for reading port value macros
#define _READ_PORT(pL, ...)			__PIN_UTIL_TOKENIZE_REG_NAME(__PIN_UTIL_PREFIX_READ_REG, pL)


///Abstraction macro for getting read registers 
#define _GET_READ(pL, ...)			__PIN_UTIL_TOKENIZE_REG_NAME(__PIN_UTIL_PREFIX_READ_REG, pL)

///Abstraction macro for Getting a specific port from letter passed
#define _GET_PORT(pL, ...)			__PIN_UTIL_TOKENIZE_REG_NAME(__PIN_UTIL_PREFIX_WRITE_REG, pL)

///Abstraction macro for Getting a specific output register from letter passed
#define _GET_OUTPUT_REG(pL, ...)	__PIN_UTIL_TOKENIZE_REG_NAME(__PIN_UTIL_PREFIX_WRITE_REG, pL)

///Abstraction macro for getting a specific direction register from the letter passed
#define _GET_DIR(pL, ...)			__PIN_UTIL_TOKENIZE_REG_NAME(__PIN_UTIL_PREFIX_DIR_REG, pL)

///Abstraction macro for getting a specific direction register from the letter passed
#define _GET_DIR_REG(pL, ...)		__PIN_UTIL_TOKENIZE_REG_NAME(__PIN_UTIL_PREFIX_DIR_REG, pL)

///Abstraction macro for getting read registers
#define _GET_READ_REG(pL, ...)		__PIN_UTIL_TOKENIZE_REG_NAME(__PIN_UTIL_PREFIX_READ_REG, pL)

///Abstractions for getting a pin number
#define _PIN_NUMBER(pL, pN)         pN



///Variable argument count macros for getting the pin number from pin utilities. Useful for creating arrays for port positions
#define _PIN_NUMBER_V2(pL1, pN1)                                                                         pN1
#define _PIN_NUMBER_V4(pL1, pN1, pL2, pN2)                                                               pN1, pN2
#define _PIN_NUMBER_V6(pL1, pN1, pL2, pN2, pL3, pN3)                                                     pN1, pN2, pN3
#define _PIN_NUMBER_V8(pL1, pN1, pL2, pN2, pL3, pN3, pL4, pN4)                                           pN1, pN2, pN3, pN4
#define _PIN_NUMBER_V10(pL1, pN1, pL2, pN2, pL3, pN3, pL4, pN4, pL5, pN5)                                pN1, pN2, pN3, pN4, pN5
#define _PIN_NUMBER_V12(pL1, pN1, pL2, pN2, pL3, pN3, pL4, pN4, pL5, pN5, pL6, pN6)                      pN1, pN2, pN3, pN4, pN5, pN6
#define _PIN_NUMBER_V14(pL1, pN1, pL2, pN2, pL3, pN3, pL4, pN4, pL5, pN5, pL6, pN6, pL7, pN7)            pN1, pN2, pN3, pN4, pN5, pN6, pN7
#define _PIN_NUMBER_V16(pL1, pN1, pL2, pN2, pL3, pN3, pL4, pN4, pL5, pN5, pL6, pN6, pL7, pN7, pL8, pN8)  pN1, pN2, pN3, pN4, pN5, pN6, pN7, pN8




#if INPUT == 0x1

///Helper for variable argument pin input macros
#define _PIN_INPUT(pL, ...)		    _PIN_DIR_HIGHV2(pL, __VA_ARGS__)

///Helper for variable argument pin output macros
#define _PIN_OUTPUT(pL, ...)	    _PIN_DIR_LOWV2(pL, __VA_ARGS__)


///Helper for port input macros
#define _PORT_INPUT(pL)		        _PORT_DIR_HIGH(pL)

///Helper for port output macros
#define _PORT_OUTPUT(pL)	        _PORT_DIR_LOW(pL)


#else

///Helper for variable argument pin macros
#define _PIN_INPUT(pL, ...)			_PIN_DIR_LOWV2(pL, __VA_ARGS__)

///Helper for variable argument pin macros
#define _PIN_OUTPUT(pL, ...)		_PIN_DIR_HIGHV2(pL, __VA_ARGS__)

///Helper for port macros
#define _PORT_INPUT(pL)		        _PORT_DIR_LOW(pL)

///Helper for port macros
#define _PORT_OUTPUT(pL)	        _PORT_DIR_HIGH(pL)



#endif


///Abstraction Macro for setting a pin high
#define _PIN_HIGH(pL, ...)				_PIN_HIGHV2(pL, __VA_ARGS__)

///Abstraction Macro for setting a pin low
#define _PIN_LOW(pL, ...)				_PIN_LOWV2(pL, __VA_ARGS__)





///Macro for getting a direction register from the literal letter passed(Example: GET_DIRECTION(B) = 0; Sets direction register for port B to 0. Do not pass quotes, only the letter)
#define GET_DIRECTION(...)			    _GET_DIR(__VA_ARGS__)

///Macro for getting a port from the literal letter passed(Example: GET_PORT(B) = 0; Sets port B to 0. Do not pass quotes, only the letter)
#define GET_PORT(...)				    _GET_PORT(__VA_ARGS__)

///Alt definition macro for getting a port from the literal letter passed(Example: port(B) = 0; Sets port B to 0. Do not pass quotes, only the letter)
#define port(...)     					_GET_PORT(__VA_ARGS__)

///Gets the pin number from predefined pin macros and discards the port letter
#define PIN_NUMBER(...)                 _PIN_NUMBER(__VA_ARGS__)

///Gets the pin number from predefined pin macros and discards the port letter
#define PIN_GET_POSITIONS(...)          VFUNC(_PIN_NUMBER_V, __VA_ARGS__)

///Macro for setting a variable amount of pins to input. First argument must be the port letter and any others are the pins to set.
#define PIN_INPUT(...)				    _PIN_INPUT(__VA_ARGS__)

///Macro for setting a variable amount of pins to output. First argument must be the port letter and any others are the pins to set.
#define PIN_OUTPUT(...)				    _PIN_OUTPUT(__VA_ARGS__)

///Macro for setting a variable amount of pins to high. First argument must be the port letter and any others are the pins to set.
#define PIN_HIGH(...)				    _PIN_HIGH(__VA_ARGS__)

///Macro for setting a variable amount of pins to low. First argument must be the port letter and any others are the pins to set.
#define PIN_LOW(...)				    _PIN_LOW(__VA_ARGS__)





///Macro for setting a port to input
#define PORT_INPUT_MODE(pL)				_PORT_INPUT(pL)

///Macro for setting a pin to output
#define PORT_OUTPUT_MODE(pL)			_PORT_OUTPUT(pL)




///Abstraction macro for writing a value to a pin
#define _WRITE_PINV3(pL, pN, pV)					writeBit(__PIN_UTIL_TOKENIZE_REG_NAME(__PIN_UTIL_PREFIX_WRITE_REG, pL), pN, pV)

///Abstraction macro for writing a value to a pin and its direction
#define _WRITE_PINV4(pL, pN, pV, pD)				writeBit(__PIN_UTIL_TOKENIZE_REG_NAME(__PIN_UTIL_PREFIX_WRITE_REG, pL), pN, pV); writeBit(__PIN_UTIL_TOKENIZE_REG_NAME(__PIN_UTIL_PREFIX_DIR_REG, pL), pN, pD)

///Abstraction macro for writing a value to a pins direction
#define _WRITE_DIR(pL, pN, pD)						writeBit(__PIN_UTIL_TOKENIZE_REG_NAME(__PIN_UTIL_PREFIX_DIR_REG, pL), pN, pD)

///Abstraction macro for writing a value a ports direction
#define _WRITE_PORT_DIR(pL, pD)						if(pD == INPUT || pD == FULL_INPUT)	PORT_INPUT_MODE(pL); else PORT_OUTPUT_MODE(pL)



///Abstraction for setting a port high
#define _SET_PORT(pL, pV)							__PIN_UTIL_TOKENIZE_REG_NAME(__PIN_UTIL_PREFIX_WRITE_REG, pL) |= pV

///Abstraction for setting a port low
#define _CLEAR_PORT(pL, pV)							__PIN_UTIL_TOKENIZE_REG_NAME(__PIN_UTIL_PREFIX_WRITE_REG, pL) &= ~(pV)

///Abstraction for setting a ports direction high
#define _SET_PORT_DIR(pL, pV)						__PIN_UTIL_TOKENIZE_REG_NAME(__PIN_UTIL_PREFIX_DIR_REG, pL) |= pV

///Abstraction for setting a ports direction low
#define _CLEAR_PORT_DIR(pL, pV)						__PIN_UTIL_TOKENIZE_REG_NAME(__PIN_UTIL_PREFIX_DIR_REG, pL) &= ~(pV)

///Abstraction for toggling a pin
#define _PIN_TOGGLE(pL, ...)                        __PIN_UTIL_TOKENIZE_REG_NAME(__PIN_UTIL_PREFIX_WRITE_REG, pL) ^= VFUNC(_BUILDVALV, __VA_ARGS__)



///Gets the value of the port. Takes the literal letter of the port and discards all other variables
#define PORT_READ(...)								_READ_PORT(__VA_ARGS__)

///Sets the bits(|=) of the port to the value passed
#define PORT_SET(port_letter, val)					_SET_PORT(port_letter, val)

///Clears the bit(&=~) of the port
#define PORT_CLEAR(port_letter, val)				_CLEAR_PORT(port_letter, val)

///Sets the direction(|=) of the port passed
#define PORT_SET_MODE(port_letter, val)				_SET_PORT_DIR(port_letter, val)

///Clears the direction(&=~) of the port passed
#define PORT_CLEAR_MODE(port_letter, val)			_CLEAR_PORT_DIR(port_letter, val)


///Writes a pins value. Takes the text letter for the port(PORTA would be A)
///the pin number, and the value for the pin and optionally the value for the direction
#define PIN_WRITE(...)								VFUNC(_WRITE_PINV, __VA_ARGS__)

///Writes a pins direction. Takes the text letter for the port(PORTA would be A)
///the pin number, and the value for the direction
#define PIN_MODE(port_letter, pin_num, pin_direction)	_WRITE_DIR(port_letter, pin_num, pin_direction)

///Reads the value of the pin passed. Takes the literal letter(PORTA would be A) and the pins position
#define PIN_READ(...)			                _READ_PIN(__VA_ARGS__)

///Toggles a pin. Takes the literal letter(PORTA would be A) and the position of the pin
#define PIN_TOGGLE(...)			                _PIN_TOGGLE(__VA_ARGS__);

///Sets a Ports direction to the direction passed. Takes the literal letter(PORTA would be A)
#define PORT_MODE(port_letter, mode)			_WRITE_PORT_DIR(port_letter, mode)

///Writes a port to the value passed Takes the literal letter(PORTA would be A) and the value.
#define PORT_WRITE(port_letter, val)			GET_PORT(port_letter) = val





#endif /* MCUPINUTILS_H_ */