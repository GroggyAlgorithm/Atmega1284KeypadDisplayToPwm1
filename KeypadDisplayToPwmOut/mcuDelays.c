/**
 * \file mcuDelays.c
 * \author Tim Robbins
 * \brief Functions for delays
 */ 
#ifndef MCUDELAYS_C_
#define MCUDELAYS_C_

#include "mcuDelays.h"




/**
 * \brief Delays for x microseconds
 * @param microseconds delay time
 */
void delayForMicroseconds(uint16_t microseconds) {
	for(uint16_t i = 0; i < microseconds; i++) {
		__DELAYS_US_DELAY_CALL(1);
	}
}



/**
 * Delays for x milliseconds
 * @param milliseconds delay time
 */
void delayForMilliseconds(uint16_t milliseconds) {
	for(uint16_t i = 0; i < milliseconds; i++) {
		__DELAYS_MS_DELAY_CALL(1);
	}
}



/**
 * Delays for x tenth seconds
 * @param tenthSeconds the amount of tenth seconds/100 milliseconds to delay for
 */
void delayForTenthSeconds(uint16_t tenthSeconds) {
	for(uint16_t i = 0; i < tenthSeconds; i++) {
		__DELAYS_MS_DELAY_CALL(100);
	}
}


#endif