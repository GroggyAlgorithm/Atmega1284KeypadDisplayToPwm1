/**
 * \file mcuAdc.c
 * \author Tim Robbins
 * \brief Source file for analog to digital (ADC) functionalities, including digital to analog (DAC) functionalities
 */
#ifndef MCU_ADC_C_
#define MCU_ADC_C_ 1

#include "mcuAdc.h"



/**
 * \brief Gets an adc value
 * \param adcChannel The adc channel to use
 * \return The adc value
 */
uint16_t AdcGet(adc_channel_t adcChannel)
{
    
    ADC_CHANNEL_REG = adcChannel;
    
    ADC_start_conversion();
    
    while(ADC_get_status());
    
    return (uint16_t)ADC_get_result();
    
}



/**
 * \brief Samples an ADC reading for x counts
 * \param adcChannel The adc channel to use
 * \param sampleCount The amount of times to sample the ADC
 * \return  The adc value
 */
uint16_t AdcSample(adc_channel_t adcChannel, uint8_t sampleCount)
{
    uint16_t adcResult = 0;
    
    if(sampleCount > 0)
    {
        uint8_t i = 0;

        ADC_CHANNEL_REG = adcChannel;



        while(i < sampleCount)
        {
            i++;

            ADC_start_conversion();
            while(ADC_get_status());
            adcResult += (uint16_t)ADC_get_result();
        }
        
        adcResult /= sampleCount;

    }
    
    return adcResult;
}





#if defined(__DAC_INCLUDED__)


/**
 * \brief Sets and outputs a passed DAC value
 * \param dacValue the value to load into the DAC data register
 */
void DacSet(uint16_t dacValue)
{
    //If the value is 0....
    if(dacValue == 0)
    {
        //Disable the DAC and clear the values
        DAC_disable();
        DAC_output_disable();
        DAC_load(0);
    }
    //Else...
    else
    {
        //Enable the DAC
        DAC_enable();
        
        //Disable the output while loading
        DAC_output_disable();
        
        //Load the DAC value
        DAC_load(dacValue);
        
        //Re-enable the DAC output
        DAC_output_enable();
    }
    
    
    
}


#endif


#endif
