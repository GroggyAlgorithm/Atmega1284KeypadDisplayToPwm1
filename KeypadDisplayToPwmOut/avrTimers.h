/**
 * \file avrTimers.h
 * \author Tim Robbins
 * \brief header file for avr timers functions and utilities \n
 *
 * \todo Finish remaking functions for timer 2 and timer 3.
 */
#ifndef __AVR_TIMERS_H__
#define __AVR_TIMERS_H__

#if defined(__AVR)

#ifdef __cplusplus
extern "C" {
#endif

 #include <avr/io.h>
 #include <stdlib.h>
 #include <stdbool.h>

///Struct for output compare settings
typedef struct _OUTPUT_COMPARE_MODE_SELECT_BITS {

    uint8_t comA:2;
    uint8_t comB:2;
    uint8_t forceOutA:1;
    uint8_t forceOutB:1;
    uint8_t __RESERVED:2;


} Output_compare_bits;


///Struct for waveform select settings
typedef struct _WAVEFORM_BIT_SELECTS {

    uint8_t WGM0:1;
    uint8_t WGM1:1;
    uint8_t WGM2:1;
    uint8_t WGM3:1;
    uint8_t __RESERVED:4;

} Waveform_select_bits;


///Struct for prescaler bit settings
typedef struct _PRESCALE_BIT_SELECTS
{
    uint8_t cs0:1;
    uint8_t cs1:1;
    uint8_t cs2:1;

    uint8_t __RESERVED:5;

} Prescaler_select_bits;


///struct for interrupt masks
typedef struct _INT_MASK_BIT_SELECTS
{
    uint8_t outputCompareMatchA : 1;
    uint8_t outputCompareMatchB : 1;
    uint8_t overflow : 1;

    uint8_t __RESERVED:5;

} Interrupt_mask_bits;


///Struct for timers including the select structs
typedef struct _TIMERS_ {
    Output_compare_bits output_mode;
    Waveform_select_bits waveform;
    Prescaler_select_bits prescaler;
    Interrupt_mask_bits interrupts;
} Timer_t;


#ifdef TCNT0
    #define T0_load(v)                          TCNT0 = v;
    #define PWM_0A_load_duty_cycle(dc)		    OCR0A = dc
    #define PWM_0B_load_duty_cycle(dc)		    OCR0B = dc
    #define T0_clear_prescaler()		TCCR0B &= ~(1 << CS00 | 1 << CS01 | 1 << CS02)
    #define T0_set_prescaler(__prescalerSelectBitsVariable__) T0_clear_prescaler(); TCCR0B |= ((Prescaler_select_bits)__prescalerSelectBitsVariable__.cs0 << CS00 | (Prescaler_select_bits)__prescalerSelectBitsVariable__.cs1 << CS01 | (Prescaler_select_bits)__prescalerSelectBitsVariable__.cs2 << CS02)
    

	int8_t Timer_0_init(Timer_t timer_settings);
	void Timer_0_enable();
	void Timer_0_disable();
    void PwmOCR0A_SetDutyCycle(uint8_t dutyCycle);
    void PwmOCR0B_SetDutyCycle(uint8_t dutyCycle);
#endif


#ifdef TCNT1
    #define T1_load(v)                 TCNT1 = v;
    #define T1_load_HL(vL, vH)         TCNT1L = (vL & 0xFF); TCNT1H = (vH & 0xFF)

    #define PWM_1A_load_duty_cycle(dc)		    OCR1A = dc
    #define PWM_1A_load_duty_cycle_HL(dcL, dcH)    OCR1AL = dcL; OCR1AH = dcH

	#define PWM_1B_load_duty_cycle(dc)		        OCR1B = dc
	#define PWM_1B_load_duty_cycle_HL(dcL, dcH)     OCR1BL = dcL; OCR1BH = dcH
	
	#define T1_clear_prescaler()		TCCR1B &= ~(1 << CS10 | 1 << CS11 | 1 << CS12)
    #define T1_set_prescaler(__prescalerSelectBitsVariable__) T1_clear_prescaler(); TCCR1B |= ((Prescaler_select_bits)__prescalerSelectBitsVariable__.cs0 << CS10 | (Prescaler_select_bits)__prescalerSelectBitsVariable__.cs1 << CS11 | (Prescaler_select_bits)__prescalerSelectBitsVariable__.cs2 << CS12)

	int8_t Timer_1_init(Timer_t timer_settings);
	void Timer_1_enable();
	void Timer_1_disable();
    void PwmOCR1A_SetDutyCycle(uint16_t dutyCycle);
    void PwmOCR1B_SetDutyCycle(uint16_t dutyCycle);

#endif

#ifdef TCNT2
    int8_t Timer_2_init(Output_compare_bits outputCompBits, Waveform_select_bits waveFormBits, Interrupt_mask_bits interrupts);
    void Timer_2_enable();
    void Timer_2_disable();
#endif

#ifdef TCNT3
    int8_t Timer_3_init(Output_compare_bits outputCompBits, Waveform_select_bits waveFormBits, Interrupt_mask_bits interrupts);
    void Timer_3_enable();
    void Timer_3_disable();
#endif


#ifdef ICR0
    #define ICR0_INPUT_CAPTURE_load_HL(vL, vH)       ICR0L = vL; ICR0H = vH
    #define ICR0_INPUT_CAPTURE_load(v)               ICR0 = v
#endif

#ifdef ICR1
    #define ICR1_INPUT_CAPTURE_load_HL(vL, vH)       ICR1L = vL; ICR1H = vH
    #define ICR1_INPUT_CAPTURE_load(v)               ICR1 = v
#endif





#ifdef __cplusplus
}
#endif

#endif




#endif