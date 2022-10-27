/**
 * \file mcuAdc.h
 * \author Tim Robbins
 * \brief Header file for analog to digital (ADC) functionalities, including digital to analog (DAC) functionalities. \n
 * REQUIREMENTS: "config.h" and "mcuUtils.h" must be included
 */

#ifndef MCU_ADC_H_
#define	MCU_ADC_H_   1

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

#include "config.h"
#include "mcuUtils.h"


#ifdef __AVR

#include <avr/io.h>


///Sets the adc results to be left adjusted
#define ADC_adjust_left()						ADMUX |= (1 << ADLAR)

///Sets the adc results to b right adjusted
#define ADC_adjust_right()						ADMUX &= ~(1 << ADLAR)

///Enables the adc
#define ADC_enable()							ADCSRA |= (1 << ADEN)

///Disables the ADC
#define ADC_disable()							ADCSRA &= ~(1 << ADEN)

///Enables ADC interrupts
#define ADC_enable_interrupt()					ADCSRA |= (1 << ADIE)

///Disables adc interrupts
#define ADC_disable_interrupt()					ADCSRA &= ~(1 << ADIE)

///Starts ADC conversion
#define ADC_start_conversion()					ADCSRA |= (1 << ADSC)

///Enables the auto trigger
#define ADC_enable_auto_trigger()				ADCSRA |= (1 << ADATE)

///Disables the auto trigger
#define ADC_disable_auto_trigger()				ADCSRA &= ~(1 << ADATE)

///Voltage reference mode 1
#define ADC_REF_MODE_1							(0b00 << REFS0)

///Voltage reference mode 2
#define ADC_REF_MODE_2							(0b01 << REFS0)

///Voltage reference mode 3
#define ADC_REF_MODE_3							(0b10 << REFS0)

///Voltage reference mode 4
#define ADC_REF_MODE_4							(0b11 << REFS0)


#ifdef AREFEN
	
	
	///Connects internal AREF to external AREF pin. Formally capacitor_on_aref
    #define ADC_AREF_ENABLE()					ADCSRB |= (1 << AREFEN)
	
	///Connects internal AREF to external AREF pin. Formally no_capacitor_on_aref
    #define ADC_AREF_DISABLE()					ADCSRB &= ~(1 << AREFEN)
	
	
#endif

///Enables free running mode
#define ADC_free_running_mode()					ADCSRB &= ~(1 << ADTS0);


#ifdef ADHSM
    #define ADC_high_speed_mode()				ADCSRB |= (1 << ADHSM)
#endif


#ifdef AC0EN
	#define ACMP0_enable_output()				ACSR |= (1 << AC0O)
	#define ACMP0_disable_output()				ACSR &= ~(1 << AC0O)
	#define ACMP0_enable_comparator()			AC0CON |= (1 << AC0EN)
	#define ACMP0_enable_interrupt()			AC0CON |= (1 << AC0IE)
	#define ACMP0_disable_comparator()			AC0CON &= ~(1 << AC0EN)
	#define ACMP0_disable_interrupt()			AC0CON &= ~(1 << AC0IE)
#endif


#ifdef AC1EN
	#define ACMP1_enable_output()				ACSR |= (1 << AC1O)
	#define ACMP1_disable_output()				ACSR &= ~(1 << AC1O)
	#define ACMP1_enable_comparator()			AC1CON |= (1 << AC1EN)
	#define ACMP1_enable_interrupt()			AC1CON |= (1 << AC1IE)
	#define ACMP1_disable_comparator()			AC1CON &= ~(1 << AC1EN)
	#define ACMP1_disable_interrupt()			AC1CON &= ~(1 << AC1IE)
#endif

#ifdef AC2EN
	#define ACMP2_enable_output()				ACSR |= (1 << AC2O)
	#define ACMP2_disable_output()				ACSR &= ~(1 << AC2O)
	#define ACMP2_enable_comparator()			AC2CON |= (1 << AC2EN)
	#define ACMP2_enable_interrupt()			AC2CON |= (1 << AC2IE)
	#define ACMP2_disable_comparator()			AC2CON &= ~(1 << AC2EN)
	#define ACMP2_disable_interrupt()			AC2CON &= ~(1 << AC2IE)
#endif

#ifdef AC3EN
	#define ACMP3_enable_output()				ACSR |= (1 << AC3O)
	#define ACMP3_disable_output()				ACSR &= ~(1 << AC3O)
	#define ACMP3_enable_comparator()			AC3CON |= (1 << AC3EN)
	#define ACMP3_enable_interrupt()			AC3CON |= (1 << AC3IE)
	#define ACMP3_disable_comparator()			AC3CON &= ~(1 << AC3EN)
	#define ACMP3_disable_interrupt()			AC3CON &= ~(1 << AC3IE)
#endif



#ifdef DACON

#define __DAC_INCLUDED__ 1

#define DAC_auto_trigger_setup(trigSelect)		DACON &= ~(0xF0); DACON |= (1 << DAATE | trigSelect << DATS0)

#define DAC_output_enable()						DACON |= (1 << DAOE)
#define DAC_output_disable()					DACON &= ~(1 << DAOE)

#define DAC_enable()							DACON |= (1 << DAEN)
#define DAC_disable()							DACON &= ~(1 << DAEN)

#define DAC_left_adjust()						DACON |= (1 << DALA)
#define DAC_right_adjust()						DACON &= ~(1 << DALA)

#define DAC_load_bytes(hVal, lVal)				DACH = hVal; DACL = lVal
#define DAC_load(v)								DAC = v

#define DAC_load_10_bit(v)						DAC = (v & 0x3FF)

extern void DacSet(uint16_t dacValue);

#endif


#define ADC_CHANNEL_REG			ADMUX

#define ADC_RESULT_REG			ADC

#define ADC_get_result()		ADC

#define ADC_get_status()		((ADCSRA >> ADSC) & 0x01)



#elif defined(__XC)

#include <xc.h>        /* XC8 General Include File */

///The channel select register
#define ADC_CHANNEL_REG                             ADPCH

///Enables the adc
#define ADC_enable()                                ADCON0bits.ADON = 1

///Disables the ADC
#define ADC_disable()                               ADCON0bits.ADON = 0

///Starts ADC conversion
#define ADC_start_conversion()                      ADCON0bits.ADGO = 1

///Checks the Status of the adc conversion
#define ADC_get_status()                            ADCON0bits.ADGO

///Enables the auto trigger
#define ADC_enable_auto_trigger()                   ADCON0bits.ADCONT = 1

///Disables the auto trigger
#define ADC_disable_auto_trigger()                  ADCON0bits.ADCONT = 0

///Sets the adc results to be left adjusted
#define ADC_adjust_left()                           ADCON0bits.ADFM = 0

///Sets the adc results to b right adjusted
#define ADC_adjust_right()                          ADCON0bits.ADFM = 1

///Sets the adc to use dedicated FRC oscillator
#define ADC_enable_frc_clock()                      ADCON0bits.ADCS = 1

///Sets the adc to use clock supplied by Fosc and divided by adclk register
#define ADC_enable_fosc_divided_clock()             ADCON0bits.ADCS = 0

#define ADC_RESULT_REG                              ADRES

#define ADC_get_result()                            ((ADRESH << 8) | ADRESL)

#define ADC_set_auto_trigger_source(v)              ADACT = (v & 0x1F)

#define ADC_set_precharge_polarity_bit(v)           ADCON1bits.ADPPOL = (v&1)

#define ADC_set_precharge_inverted_enable_bit(v)    ADCON1bits.ADIPEN = (v&1)

#define ADC_set_guard_ring_polarity_bit(v)          ADCON1bits.ADGPOL = (v&1)

#define ADC_set_double_sample_enable_bit(v)         ADCON1bits.ADDSEN = (v&1)

#define ADC_set_op_mode_select_bits(v)              ADCON2bits.ADMD = (v & 0b111)

#define ADC_vref_internal()                         ADREF |= (0b11)

#define ADC_vref_external()                         ADREF |= (0b10)

#define ADC_vref_connected_to_vdd()                 ADREF &= ~(0b11)


#elif defined(HI_TECH_C)

#include <htc.h>       /* HiTech General Include File */


#elif defined(__18CXX)

#include <p18cxxx.h>   /* C18 General Include File */


#elif (defined __XC8)
    
#include <xc.h>        /* XC8 General Include File */

#endif





typedef uint8_t adc_channel_t;

extern uint16_t AdcGet(adc_channel_t adcChannel);
extern uint16_t AdcSample(adc_channel_t adcChannel, uint8_t sampleCount);














#ifdef	__cplusplus
}
#endif /* __cplusplus */




#endif	/* XC_HEADER_TEMPLATE_H */

