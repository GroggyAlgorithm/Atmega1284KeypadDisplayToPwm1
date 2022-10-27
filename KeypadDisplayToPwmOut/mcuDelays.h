/**
 * \file mcuDelays.h
 * \author Tim Robbins
 * \brief Header file for delay functions. Requires "config.h" to be included for macro definitions
 */ 
#ifndef MCUDELAYS_H_
#define MCUDELAYS_H_ 1

#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __AVR

#include <avr/io.h>

#include <util/delay.h>

#define __DELAYS_US_DELAY_CALL(x)  _delay_us(x);
#define __DELAYS_MS_DELAY_CALL(x)  _delay_ms(x);

#ifndef F_CPU
#error mcuDelays.h: F_CPU not defined. This is needed for any delay functionality.
#endif

#elif defined(__XC)

#ifndef _XTAL_FREQ

    #ifdef F_CPU

        #define _XTAL_FREQ F_CPU

    #else

        #error mcuDelays.h: _XTAL_FREQ is undefined

    #endif
#endif

#include <xc.h>        /* XC8 General Include File */

#define __DELAYS_US_DELAY_CALL(x)   __delay_us(x);
#define __DELAYS_MS_DELAY_CALL(x)   __delay_ms(x);
#define WATCH_DOG_MICROSEC_DELAY(x) __delaywdt_us(x)
#define WATCH_DOG_MILLISEC_DELAY(x) __delaywdt_ms(x)

#elif defined(HI_TECH_C)

#ifndef _XTAL_FREQ

    #ifdef F_CPU

        #define _XTAL_FREQ F_CPU

    #else

        #error mcuDelays.h: _XTAL_FREQ is undefined

    #endif
#endif

#include <htc.h>       /* HiTech General Include File */

#define __DELAYS_US_DELAY_CALL(x)   __delay_us(x);
#define __DELAYS_MS_DELAY_CALL(x)   __delay_ms(x);
#define WATCH_DOG_MICROSEC_DELAY(x) __delaywdt_us(x)
#define WATCH_DOG_MILLISEC_DELAY(x) __delaywdt_ms(x)

#elif defined(__18CXX)

#ifndef _XTAL_FREQ

    #ifdef F_CPU

        #define _XTAL_FREQ F_CPU

    #else

        #error mcuDelays.h: _XTAL_FREQ is undefined

    #endif
#endif

#include <p18cxxx.h>   /* C18 General Include File */

#define __DELAYS_US_DELAY_CALL(x)   __delay_us(x);
#define __DELAYS_MS_DELAY_CALL(x)   __delay_ms(x);
#define WATCH_DOG_MICROSEC_DELAY(x) __delaywdt_us(x)
#define WATCH_DOG_MILLISEC_DELAY(x) __delaywdt_ms(x)

#elif (defined __XC8)

#ifndef _XTAL_FREQ

    #ifdef F_CPU

        #define _XTAL_FREQ F_CPU

    #else

        #error mcuDelays.h: _XTAL_FREQ is undefined

    #endif
#endif

#include <xc.h>        /* XC8 General Include File */

#define __DELAYS_US_DELAY_CALL(x)   __delay_us(x);
#define __DELAYS_MS_DELAY_CALL(x)   __delay_ms(x);
#define WATCH_DOG_MICROSEC_DELAY(x) __delaywdt_us(x)
#define WATCH_DOG_MILLISEC_DELAY(x) __delaywdt_ms(x)

#endif

//Delays for x microseconds
extern void delayForMicroseconds(uint16_t microseconds);

//Delays for x milliseconds
extern void delayForMilliseconds(uint16_t milliseconds);

//Delays for x tenth seconds
extern void delayForTenthSeconds(uint16_t tenthSeconds);



#ifdef __cplusplus
}
#endif


#endif /* MCUDELAYS_H_ */