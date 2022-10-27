/**
 * \file mcuUtils.h
 * \author Tim Robbins
 * \brief Utilities file for microcontrollers \n
 * CONFIGURATION OPTIONS \n
 * If defined as 1 in this file, MCU_UTILS_USE_INLINE will cause many of the macro functions to be inline functions, some of these as always inline. \n
 * With some of these macros being useful for more than 1 data type, these will not be included in the inline functionalities. \n
 * This is, for the most part, referencing the bit manipulations. \n
 * Currently, this only changes the char roll over functions and the sleep functions
 */ 
#ifndef MCUUTILS_H_
#define MCUUTILS_H_


///If the macros should be inline functions instead
#define MCU_UTILS_USE_INLINE	0


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */



#ifdef __AVR

#include <avr/io.h>


///Value for input
#define INPUT				0x0

///Value for output
#define OUTPUT				0x1

///Value for an 8 bit port being set to output
#define FULL_OUTPUT		    0xFF

///Value for an 8 bit port being set to Input.
#define FULL_INPUT		    0x00

///Enables global interrupts
#define interruptsOn()    __asm__ __volatile__ ("sei" ::: "memory")

///Disables global interrupts
#define interruptsOff()   __asm__ __volatile__ ("cli" ::: "memory")

///The no process function
#define noP()	__asm__ __volatile__("nop")

#elif defined(__XC)

#include <xc.h>        /* XC8 General Include File */


///Value for input
#define INPUT				0x1

///Value for output
#define OUTPUT				0x0

///Value for an 8 bit port being set to output
#define FULL_OUTPUT		    0x00

///Value for an 8 bit port being set to Input.
#define FULL_INPUT		    0xFF

///Enables global interrupts
#define interruptsOn()      ei()

///Disables global interrupts
#define interruptsOff()     di()


#elif defined(HI_TECH_C)

#include <htc.h>       /* HiTech General Include File */

///Value for input
#define INPUT				0x1

///Value for output
#define OUTPUT				0x0

///Value for an 8 bit port being set to output
#define FULL_OUTPUT		    0x00

///Value for an 8 bit port being set to Input.
#define FULL_INPUT		    0xFF

#elif defined(__18CXX)

#include <p18cxxx.h>   /* C18 General Include File */

///Value for input
#define INPUT				0x1

///Value for output
#define OUTPUT				0x0

///Value for an 8 bit port being set to output
#define FULL_OUTPUT		    0x00

///Value for an 8 bit port being set to Input.
#define FULL_INPUT		    0xFF

#elif (defined __XC8)
    
#include <xc.h>        /* XC8 General Include File */

///Value for input
#define INPUT				0x1

///Value for output
#define OUTPUT				0x0

///Value for an 8 bit port being set to output
#define FULL_OUTPUT		    0x00

///Value for an 8 bit port being set to Input.
#define FULL_INPUT		    0xFF


#endif








///Value for forever (for ever == for(;;). Get it haha) loops. Is just fun.
#define forever	for (;;)

///Value for high
#define HIGH				0x1

///Value for low
#define LOW					0x0

///Value for bit true
#define TRUE   	            0x1

///Value for bit false
#define FALSE  	            0x0

///Value for an 8 bit port being set high
#define FULL_HIGH           0xFF

///Value for a port being set low. A redef of LOW.
#define FULL_LOW            0x00

///Macro shorthand for unsigned char
#define uchar 				unsigned char

///Macro shorthand for unsigned short
#define usht  				unsigned short

///Macro shorthand for an unsigned integer
#define uint 				unsigned int

///Macro shorthand for unsigned long
#define ulng				unsigned long

///Math value for PI
#define PI 					3.1415926535897932384626433832795

///Math value for 1/2 PI
#define HALF_PI 			1.5707963267948966192313216916398

///Math value for PI * 2
#define TWO_PI 				6.283185307179586476925286766559

///Constant value for converting degrees to radians
#define DEG_TO_RAD 			0.017453292519943295769236907684886

///Constant value for converting radians to degrees
#define RAD_TO_DEG 			57.295779513082320876798154814105

///Value for a EULER
#define EULER 				2.718281828459045235360287471352

///Swaps the char values high and low nibble
#define swapNibble(value)	(((value & 0xF0) >> 4) | ((value & 0x0F) << 4))

///Returns the swapped char values high and low nibble
#define nibbleSwap(value)	(((value & 0xF0) >> 4) | ((value & 0x0F) << 4))

///returns the values bit at the passed bit position
#define readBit(value, bit) (((value) >> (bit)) & 0x01)

///Returns true if the values bit at the passed bit position is low
#define bitIsClear(value, bit)	(readBit(value, bit) ? 0 : 1)

///Returns true if the values bit at the passed bit position is high
#define bitIsSet(value, bit)	(readBit(value, bit) ? 1 : 0)

///Sets the values bit to high at the passed bit position
#define setBit(value, bit) ((value) |= (1UL << (bit)))

///Clears the values bit to low at the passed bit position
#define clearBit(value, bit) ((value) &= ~(1UL << (bit)))

///Toggles the values bit at the passed bit position
#define toggleBit(value, bit) ((value) ^= (1UL << (bit)))

///Sets the bit at value's bit position to the specified bit value. If bitValue > 0, it sets the bit, else it clears it
#define writeBit(value, bitPosition, bitValue) ((bitValue) ? setBit(value, bitPosition) : clearBit(value, bitPosition))

///Sets the bit in the value to the input value
#define setBitInput(value, bitPosition)	 writeBit(value, bitPosition, INPUT)

///Sets the bit in the value to the output value
#define setBitOutput(value, bitPosition) writeBit(value, bitPosition, OUTPUT)


#if INPUT > 0x00

///Sets the mask to in the value to input
#define writeMaskInput(value, bitPositionMask) value |= (bitPositionMask)

///Sets the mask to in the value to output
#define writeMaskOutput(value, bitPositionMask) value &= ~(bitPositionMask)


#else

///Sets the mask to in the value to input
#define writeMaskInput(value, bitPositionMask) value &= ~(bitPositionMask)

///Sets the mask to in the value to output
#define writeMaskOutput(value, bitPositionMask) value |= (bitPositionMask)


#endif


///Returns the lower byte in a short/word/int16_t or larger
#define lowByte(shortVal)   ((shortVal) & 0xFF)

///Returns the high byte in a short/word/int16_t or larger
#define highByte(shortVal)  ((shortVal & 0xFF00) >> 8)

///Returns the lower bits of a byte
#define lowNibble(byteVal)	((byteVal) & 0x0F)

///Returns the higher bits of a byte
#define highNibble(byteVal)	((byteVal & 0xF0) >> 4)

///Clears the lower bits of a byte
#define clearLowerNibble(byteVal)	byteVal &= ~(0x0F)

///Clears the upper bits
#define clearUpperNibble(byteVal)	byteVal &= ~(0xF0)

///Clears the low byte in a word/short/uint16_t or larger
#define clearLowerByte(shortInt)	shortInt &= ~0x00FF

///\Clears the high byte in a word/short/uint16_t or larger
#define clearUpperByte(shortInt)	shortInt &= ~0xFF00

///Swap operation using no temp variable
#define swap(a, b)	a ^= b; b ^= a; a ^= b

///Returns the smallest of the two values
#define min(a,b) ((a)<(b)?(a):(b))

///Returns the largest of the two values
#define max(a,b) ((a)>(b)?(a):(b))

///Returns the absolute value of the value passed
#define abosolute(val)	((val < 0) ? (-val) : val)

///Returns the negative absolute value of the value passed
#define nabsolute(val) (-abosolute(val))

///Clamps a value between the low and high values
#define clamp(val,low,high) (((val) < (low)) ? (low) : ((val) > (high) ? (high)) : (val))

///Converts degrees to radians
#define degreesToRadians(deg)	((deg) * DEG_TO_RAD)

///Converts radians to degrees
#define radiansToDegrees(rad) ((rad) * RAD_TO_DEG)

///Normalizes the value between 0 and 1 within the range passed
//#define normalizeInRange(value, minVal, maxVal)  ((maxVal - minVal) > 0 && (value > minVal) && (value < maxVal)) ? ((value - minVal) / (maxVal - minVal)) :  (value < maxVal) ? 1 : 0
#define normalizeInRange(value, minVal, maxVal)  (((maxVal > minVal) && (value > minVal)) ? (value - minVal) / (maxVal - minVal)) : 0)

///Converts a byte value to a percentage
#define byteToPercent(v)	((v*100)/255)

///Converts a 10 bit value to a percentage(Useful for 10 bit adc)
#define tenBitToPercent(v)	((v*10)/102.3)

///Converts a short value to a percentage
#define shortToPercent(v)	(((v)/655.35)*100)

///Squares the value passed
#define sqr(val)	(val*val)


#if defined(MCU_UTILS_USE_INLINE) && MCU_UTILS_USE_INLINE == 1



#ifdef SMCR


/**
 * \brief Enable sleep
 */
__attribute__((always_inline)) inline void sleep_enable() 
{
	SMCR |= (1 << SE);
}


/**
 * \brief Disable sleep
 */
__attribute__((always_inline)) inline void sleep_disable() 
{
	SMCR &= ~(1 << SE);
}


/**
 * \brief Set sleep mode to use when entering sleep state
 *
 * \param mode Sleep mode
 */
inline void sleep_set_mode(uint8_t mode) {
	SMCR = (mode | (SMCR & ~((1 << SM0) | (1 << SM1) | (1 << SM2))));
}

#endif



///8 bit roll over right bit shift
inline char cror(char byte)	
{
	if(readBit(byte,0)) 
	{
		clearBit(byte,0); 
		byte = byte >> 1; 
		setBit(byte,7); 
	} 
	else 
	{
		byte = byte >> 1;
	}

	return byte;
}

///8 bit roll over right bit shift
inline char crol(char byte)	
{
	if(readBit(byte,7)) 
	{
		clearBit(byte,7); 
		byte = byte << 1; 
		setBit(byte,0); 
	} 
	else 
	{
		byte = byte << 1;
	}

	return byte;
}

///8 bit roll over right bit shift, high bits only
inline char crorH(char byte)	
{
	if(readBit(byte,4)) 
	{
		clearBit(byte,4); 
		byte = (((byte & 0xF0) >> 1) | (byte & 0x0F)); 
		setBit(byte,7); 
	} 
	else 
	{
		byte = (((byte & 0xF0) >> 1) | (byte & 0x0F));
	}

	return byte;
}

///8 bit roll over right bit shift, high bits only
inline char crolH(char byte)	
{
	if(readBit(byte,7)) 
	{
		clearBit(byte,7); 
		byte = (((byte & 0xF0) << 1) | (byte & 0x0F)); 
		setBit(byte,4); 
		} 
		else 
		{
			byte = (((byte & 0xF0) << 1) | (byte & 0x0F));
		}

		return byte;
}

///8 bit roll over right bit shift, low bits only
inline char crorL(char byte)	
{
	if(readBit(byte,0)) 
	{
		clearBit(byte,0); 
		byte = (((byte & 0x0F) >> 1) | (byte & 0xF0)); 
		setBit(byte,3); 
	} 
	else 
	{
		byte = (((byte & 0x0F) >> 1) | (byte & 0xF0));
	}

	return byte;
}

///8 bit roll over right bit shift, low bits only
inline char crolL(char byte)
{
	if(readBit(byte,3)) 
	{
		clearBit(byte,3); 
		byte = (((byte & 0x0F) << 1) | (byte & 0xF0)); 
		setBit(byte,0); 
	} 
	else 
	{
		byte = (((byte & 0x0F) << 1) | (byte & 0xF0));
	}

	return byte;
}




#else

///8 bit roll over right bit shift
#define cror(byte)	if(readBit(byte,0)) {clearBit(byte,0); byte = byte >> 1; setBit(byte,7); } else byte = byte >> 1

///8 bit roll over right bit shift
#define crol(byte)	if(readBit(byte,7)) {clearBit(byte,7); byte = byte << 1; setBit(byte,0); } else byte = byte << 1

///8 bit roll over right bit shift, high bits only
#define crorH(byte)	if(readBit(byte,4)) {clearBit(byte,4); byte = (((byte & 0xF0) >> 1) | (byte & 0x0F)); setBit(byte,7); } else byte = (((byte & 0xF0) >> 1) | (byte & 0x0F))

///8 bit roll over right bit shift, high bits only
#define crolH(byte)	if(readBit(byte,7)) {clearBit(byte,7); byte = (((byte & 0xF0) << 1) | (byte & 0x0F)); setBit(byte,4); } else byte = (((byte & 0xF0) << 1) | (byte & 0x0F))

///8 bit roll over right bit shift, low bits only
#define crorL(byte)	if(readBit(byte,0)) {clearBit(byte,0); byte = (((byte & 0x0F) >> 1) | (byte & 0xF0)); setBit(byte,3); } else byte = (((byte & 0x0F) >> 1) | (byte & 0xF0))

///8 bit roll over right bit shift, low bits only
#define crolL(byte)	if(readBit(byte,3)) {clearBit(byte,3); byte = (((byte & 0x0F) << 1) | (byte & 0xF0)); setBit(byte,0); } else byte = (((byte & 0x0F) << 1) | (byte & 0xF0))

#ifdef SMCR


/**
 * \brief Enable sleep
 */
#define sleep_enable() SMCR |= (1 << SE)


/**
 * \brief Disable sleep
 */
#define sleep_disable() SMCR &= ~(1 << SE)


/**
 * \brief Set sleep mode to use when entering sleep state
 *
 * \param mode Sleep mode
 */
#define sleep_set_mode(mode) SMCR = ((uint8_t)mode | (SMCR & ~((1 << SM0) | (1 << SM1) | (1 << SM2))))


#endif

#endif







#if defined(F_CPU)

///Conversion for clock cycles per microsecond
#define clockCyclesPerMicrosecond() ( F_CPU / 4000000UL )

#elif defined(_XTAL_FREQ)

///Conversion for clock cycles per microsecond
#define clockCyclesPerMicrosecond() ( _XTAL_FREQ / 4000000UL )

#endif

///Converts hertz to period
#define calculatePeriod(hertz)  (1/hertz)

///Calculates the average voltage from duty cycle
#define averageVoltageFromDutyCycle(highOutputVoltage, lowOutputVoltage, dutyHigh, dutyLow) (((highOutputVoltage*dutyHigh)+(lowOutputVoltage*dutyLow))/(dutyHigh+dutyLow))

///Converts microseconds to ticks. Prescaler, generally 8
#define microToTicks(_us, prescaler)    (( clockCyclesPerMicrosecond()* _us) / prescaler)     

///Converts from ticks back to microseconds. Prescaler, generally 8
#define ticksToMicro(_ticks, prescaler) (( (unsigned)_ticks * prescaler)/ clockCyclesPerMicrosecond() ) 

///Converts clock cycles to microseconds
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )

///Converts microseconds to clock cycles
#define microsecondsToClockCycles(a) ((a) * clockCyclesPerMicrosecond() )

///Converts milliseconds to clock cycles
#define millisecondsToClockCycles(a) ((a) * microsecondsToClockCycles(1000))

///Converts microseconds to milliseconds
#define microToMilliseconds(a) (clockCyclesToMicroseconds(a) * 1000)




///Helper macro for macro stringizing the plain text passed
#define _STRINGIZE(x)		#x

///Helper macro for token pasting
#define _TOKENIZE(x,y)		x##y

//Using vfunc will add variable arguments based on the amount of arguments.

#define __NARG__(...)  __NARG_I_(__VA_ARGS__,__RSEQ_N())
#define __NARG_I_(...) __ARG_N(__VA_ARGS__)

#define __ARG_N( \
_1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
_11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
_21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
_31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
_41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
_51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
_61,_62,_63,N,...) N
#define __RSEQ_N() \
63,62,61,60,                   \
59,58,57,56,55,54,53,52,51,50, \
49,48,47,46,45,44,43,42,41,40, \
39,38,37,36,35,34,33,32,31,30, \
29,28,27,26,25,24,23,22,21,20, \
19,18,17,16,15,14,13,12,11,10, \
9,8,7,6,5,4,3,2,1,0


#define _VFUNC_(name, n) name##n
#define _VFUNC(name, n) _VFUNC_(name, n)


///Macro to call different macros based on variable count and names ending with the amount of variables passed
#define VFUNC(func, ...) _VFUNC(func, __NARG__(__VA_ARGS__)) (__VA_ARGS__)



///Macros for manually building a value bit by bit(idk any use cases, was experimenting)
#define _BUILDVALV1(b0)										(1 << b0)

///Macros for manually building a value bit by bit(idk any use cases, was experimenting)
#define _BUILDVALV2(b0, b1)									(1 << b0 | 1 << b1)

///Macros for manually building a value bit by bit(idk any use cases, was experimenting)
#define _BUILDVALV3(b0, b1, b2)								(1 << b0 | 1 << b1 | 1 << b2)

///Macros for manually building a value bit by bit(idk any use cases, was experimenting)
#define _BUILDVALV4(b0, b1, b2, b3)							(1 << b0 | 1 << b1 | 1 << b2 | 1 << b3)

///Macros for manually building a value bit by bit(idk any use cases, was experimenting)
#define _BUILDVALV5(b0, b1, b2, b3, b4)						(1 << b0 | 1 << b1 | 1 << b2 | 1 << b3 | 1 << b4)

///Macros for manually building a value bit by bit(idk any use cases, was experimenting)
#define _BUILDVALV6(b0, b1, b2, b3, b4, b5)					(1 << b0 | 1 << b1 | 1 << b2 | 1 << b3 | 1 << b4 | 1 << b5)

///Macros for manually building a value bit by bit(idk any use cases, was experimenting)
#define _BUILDVALV7(b0, b1, b2, b3, b4, b5, b6)				(1 << b0 | 1 << b1 | 1 << b2 | 1 << b3 | 1 << b4 | 1 << b5 | 1 << b6)

///Macros for manually building a value bit by bit(idk any use cases, was experimenting)
#define _BUILDVALV8(b0, b1, b2, b3, b4, b5, b6, b7)			(1 << b0 | 1 << b1 | 1 << b2 | 1 << b3 | 1 << b4 | 1 << b5 | 1 << b6 | 1 << b7)



///Helpers for reordering a values bits. Seemed like it could be useful for LCD's
#define _REORDERBITSV3(val, b0, b1)								(readBit(val,0) << b0 | readBit(val,1) << b1)

///Helpers for reordering a values bits. Seemed like it could be useful for LCD's
#define _REORDERBITSV4(val, b0, b1, b2)							(readBit(val,0) << b0 | readBit(val,1) << b1 | readBit(val,2) << b2)

///Helpers for reordering a values bits. Seemed like it could be useful for LCD's
#define _REORDERBITSV5(val, b0, b1, b2, b3)						(readBit(val,0) << b0 | readBit(val,1) << b1 | readBit(val,2) << b2 | readBit(val,3) << b3)

///Helpers for reordering a values bits. Seemed like it could be useful for LCD's
#define _REORDERBITSV6(val, b0, b1, b2, b3, b4)					(readBit(val,0) << b0 | readBit(val,1) << b1 | readBit(val,2) << b2 | readBit(val,3) << b3 \
| readBit(val,4) << b4)

///Helpers for reordering a values bits. Seemed like it could be useful for LCD's
#define _REORDERBITSV7(val, b0, b1, b2, b3, b4, b5)				(readBit(val,0) << b0 | readBit(val,1) << b1 | readBit(val,2) << b2 | readBit(val,3) << b3 \
| readBit(val,4) << b4 | readBit(val,5) << b5)

///Helpers for reordering a values bits. Seemed like it could be useful for LCD's
#define _REORDERBITSV8(val, b0, b1, b2, b3, b4, b5, b6)			(readBit(val,0) << b0 | readBit(val,1) << b1 | readBit(val,2) << b2 | readBit(val,3) << b3 \
| readBit(val,4) << b4 | readBit(val,5) << b5 | readBit(val,6) << b6)

///Helpers for reordering a values bits. Seemed like it could be useful for LCD's
#define _REORDERBITSV9(val, b0, b1, b2, b3, b4, b5, b6, b7)		(readBit(val,0) << b0 | readBit(val,1) << b1 | readBit(val,2) << b2 | readBit(val,3) << b3 \
| readBit(val,4) << b4 | readBit(val,5) << b5 | readBit(val,6) << b6 | readBit(val,7) << b7)



///Macro for helper abstraction
#define __BUILD_VAL(...)					VFUNC(_BUILDVALV, __VA_ARGS__)

///Macro for helper abstraction
#define __REORDER_VALUE(val, ...)			VFUNC(_REORDERBITSV, val, __VA_ARGS__)


///Macro for building a value bit by bit or byte by byte and so on. Still not sure what the use would be.
#define BUILD_BIT_VALUE(...)				__BUILD_VAL(__VA_ARGS__)

///Macro for reordering a values bits. Seemed useful for LCD's
#define REORDER_BITS(val, ...)				__REORDER_VALUE(val, __VA_ARGS__)


///Sets a volatile pointer variable to a register. If passed as a parameter, do not use. Instead, pass as &register to the functions volatile <datatype> *register variable. For memory.
#define setPointerAsRegister(p, r) p = &r


/**
 * \union ShortSplits
 * \brief Typedef union for easily splitting short ints into high and low bytes
 */
typedef union _SHORT_SPLIT_UNION
{

	unsigned short int total; ///The total to load and split

	unsigned char bytes[2]; ///The bytes split

} ShortSplit_t;




/**
 * \union IntSplits
 * \brief Typedef union for easily splitting ints into bytes
 */
typedef union _INT_SPLIT_UNION
{

	unsigned int total; ///The total to load and split

	unsigned char bytes[4]; ///The bytes split

} IntSplit_t;




/**
 * \union LongSplits
 * \brief Typedef union for easily splitting long ints into bytes
 */
typedef union _LONG_SPLIT_UNION
{

	unsigned long total; ///The total to load and split

	unsigned char bytes[8]; ///The bytes split

} LongSplit_t;


///Union that takes a byte value and splits it into bits
typedef union _BYTE_MASK_UNION {
	unsigned char byte;
	struct
	{
		volatile unsigned char b0: 1;
		volatile unsigned char b1: 1;
		volatile unsigned char b2: 1;
		volatile unsigned char b3: 1;
		volatile unsigned char b4: 1;
		volatile unsigned char b5: 1;
		volatile unsigned char b6: 1;
		volatile unsigned char b7: 1;
	} bits;
	
}ByteMask_t;


/// @brief Union that splits a byte into nibbles
typedef union _NIBBLE_SPLIT_UNION_
{
	unsigned char byte;
	struct
	{
		volatile unsigned char nibbleA:4;
		volatile unsigned char nibbleB:4;

	} nibbles;
	
}NibbleSplit_t;






extern uint8_t ConvertRangeToPercentage(uint16_t minValue, uint16_t maxValue, uint16_t value);
extern uint16_t ConvertPercentageInRange(uint16_t minValue, uint16_t maxValue, uint16_t percentageValue);
extern uint16_t ConvertPercentage(uint16_t maxValue, uint16_t percentageValue);
extern uint16_t Adc10bitTo5Volts(uint16_t adcValue);
extern uint16_t ClockCountsFor16BitFreq(uint64_t systemFreq, uint16_t prescaler, uint16_t freqInHz, uint16_t *overflowCounts);
extern uint8_t ClockCountsFor8BitFreq(uint64_t systemFreq, uint16_t prescaler, uint16_t freqInHz, uint16_t *overflowCounts);
extern uint16_t ClockCountsFor16BitTime(uint64_t systemFreq, uint16_t prescaler, float seconds, uint16_t *overflowCounts);
extern uint8_t ClockCountsFor8BitTime(uint64_t systemFreq, uint16_t prescaler, uint16_t seconds, uint16_t *overflowCounts);


#ifdef	__cplusplus
}
#endif /* __cplusplus */




#endif /* MCUUTILS_H_ */