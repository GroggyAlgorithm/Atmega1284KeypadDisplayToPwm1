/**
 * \file mcuUtils.c
 * \author Tim Robbins
 * \brief Utilities file for microcontrollers
 */ 

#include "mcuUtils.h"

#ifndef MCUUTILS_C_
#define MCUUTILS_C_ 1





/**
* \brief Converts the passed value to a percentage in the range of min to max valus
* \param minValue The minimum possible value
* \param maxValue The maximum possible value
* \param value The value to convert to a percentage
* \return uint8_t percentage
*/
uint8_t ConvertRangeToPercentage(uint16_t minValue, uint16_t maxValue, uint16_t value)
{
    //The calculated value for the value from the percentage value passed
	uint8_t calculatedValue = 0; 
	
    //Swap
    if(minValue > maxValue)
    {
        maxValue ^= minValue;
        minValue ^= maxValue;
        maxValue ^= minValue;
    }
    
	//If the percentage passed is greater than or equal to 100%...
	if(value >= maxValue || minValue == maxValue)
	{
		//Set to the max value
		calculatedValue = 100;
	}
	//else if the value is greater than minValue...
	else if(value > minValue)
	{
        
		//Get the beginning point of the value
		float mathedUpPercentage =  (float)((float)(value-minValue)/(maxValue - minValue));
		
		//Multiply this value by 100
		calculatedValue = (uint8_t)(mathedUpPercentage * 100);
	
	}
    else
    {
        calculatedValue = 0;
    }
	
	return calculatedValue;
}



/**
* \brief Converts the passed percentage value to a value in the range of min to max
* \param minValue The minimum possible value
* \param maxValue The maximum possible value
* \param percentageValue The percentage value in the range
* \return uint16_t calculated value
*/
uint16_t ConvertPercentageInRange(uint16_t minValue, uint16_t maxValue, uint16_t percentageValue)
{
    //The calculated value for the value from the percentage value passed
	uint16_t calculatedValue = 0; 
	
    //Swap
    if(minValue > maxValue)
    {
        maxValue ^= minValue;
        minValue ^= maxValue;
        maxValue ^= minValue;
    }
    
	//If the percentage passed is greater than or equal to 100%...
	if(percentageValue >= 100 || minValue == maxValue)
	{
		//Set to the max value
		calculatedValue = maxValue;
	}
	//else if the value is greater than minValue...
	else if(percentageValue > 0)
	{
		//Get the beginning point of the value by taking the percentage and dividing by 100
		float mathedUpPercentage =  (float)((float)percentageValue/100.0f);
		
		//Multiply this value by the max - min value to get the calculated value.
		calculatedValue = (uint16_t)(mathedUpPercentage * (maxValue - minValue));
	
	}
    else
    {
        calculatedValue = minValue;
    }
	
	return calculatedValue;
}



/**
* \brief Converts the passed percentage value to a value in the range of 0 to max
* \param maxValue The maximum possible value
* \param percentageValue The percentage value in the range
* \return uint16_t calculated value
*/
uint16_t ConvertPercentage(uint16_t maxValue, uint16_t percentageValue)
{
	//The calculated value for the value from the percentage value passed
	uint16_t calculatedValue = 0; 
	
	//If the percentage passed is greater than or equal to 100%...
	if(percentageValue >= 100)
	{
		//Set to the max value
		calculatedValue = maxValue;
	}
	//else if the value is greater than 0...
	else if(percentageValue > 0)
	{
		//Get the beginning point of the value by taking the percentage and dividing by 100
		float mathedUpPercentage =  (float)((float)percentageValue/100.0f);
		
		//Multiply this value by the max value to get the calculated value.
		calculatedValue = (uint16_t)(mathedUpPercentage * maxValue);
	
	}
	
	return calculatedValue;

}



/**
 * \brief Takes a 10 bit ADC value and converts it to a voltage within 5 volts. Max = 5000
 * \param adcValue The adc value done gotten
 * \return The voltage value, up to 5000 = 5 volts
 */
uint16_t Adc10bitTo5Volts(uint16_t adcValue)
{
    //The percentage calculated
    uint8_t adcPercentage = 0;
    
    //The adc value as a voltage
    uint16_t adcVoltage = 0;
    
    adcPercentage = ConvertRangeToPercentage(0,1024, adcValue);
    adcVoltage = (ConvertPercentage(5000,adcPercentage)); 
    
    return adcVoltage;
}



/**
 * \brief Converts the desired frequency to the number of required timer counts and the amount of required overflow counts for a 16 bit timer
 * \param systemFreq The frequency to be used
 * \param prescaler The timer prescaler
 * \param freqInHz The desired frequency, in Hz
 * \param overflowCounts The amount of overflow counts
 * \return The calculated clock value
 */
uint16_t ClockCountsFor16BitFreq(uint64_t systemFreq, uint16_t prescaler, uint16_t freqInHz, uint16_t *overflowCounts)
{
    //Calculate the time required for the frequency by dividing 1 by the desired frequency
    float calcDesiredFreq = (1.0f/(float)freqInHz);
    
    //Calculate the number of clock pulses needed by dividing our time desired by the time per clock pulse (1/system frequency)
    float numClockPulses = ((float)calcDesiredFreq / ((double)(1.0/(double)systemFreq)));
    
    //Divide by the prescaler passed to get the calculated TOTAL number of counts
    uint64_t calculatedTotalCounts = (numClockPulses/prescaler)-1;
    
    //Create a variable for the return value
    uint16_t calculatedTimerCounts = 0;
    
    //Reset the overflow counts
    *overflowCounts = 0;
    
    //If the calculated counts are over 16 bit max
    if(calculatedTotalCounts >= 65536)
    {
        *overflowCounts = (uint16_t)(calculatedTotalCounts / 65536);
        calculatedTotalCounts = 65535;
    }
    
    //Convert the calculated total counts to a unsigned short
    calculatedTimerCounts = ((uint16_t)calculatedTotalCounts);
    
    //Return the calculated number of timer counts
    return calculatedTimerCounts;
    
    
}



/**
 * \brief Converts the desired frequency to the number of required timer counts and the amount of required overflow counts for an 8 bit timer
 * \param systemFreq The frequency to be used
 * \param prescaler The timer prescaler
 * \param freqInHz The desired frequency, in Hz
 * \param overflowCounts The amount of overflow counts
 * \return The calculated clock value
 */
uint8_t ClockCountsFor8BitFreq(uint64_t systemFreq, uint16_t prescaler, uint16_t freqInHz, uint16_t *overflowCounts)
{
    //Calculate the time required for the frequency by dividing 1 by the desired frequency
    float calcDesiredFreq = (1.0f/(float)freqInHz);
    
    //Calculate the number of clock pulses needed by dividing our time desired by the time per clock pulse (1/system frequency)
    float numClockPulses = ((float)calcDesiredFreq / ((double)(1.0/(double)systemFreq)));
    
    //Divide by the prescaler passed to get the calculated TOTAL number of counts
    uint64_t calculatedTotalCounts = (numClockPulses/prescaler)-1;
    
    //Create a variable for the return value
    uint8_t calculatedTimerCounts = 0;
    
    //Reset the overflow counts
    *overflowCounts = 0;
    
    //If the calculated counts are over 8 bit max
    if(calculatedTotalCounts >= 256)
    {
        *overflowCounts = (uint16_t)(calculatedTotalCounts / 256);
        calculatedTotalCounts = 255;
    }
    
    //Convert the calculated total counts to a unsigned char
    calculatedTimerCounts = ((uint8_t)calculatedTotalCounts);
    
    //Return the calculated number of timer counts
    return calculatedTimerCounts;
    
    
}



/**
 * \brief Converts the desired time to the number of required timer counts and the amount of required overflow counts for a 16 bit timer
 * \param systemFreq The frequency to be used
 * \param prescaler The timer prescaler
 * \param seconds The desired time, in seconds
 * \param overflowCounts The amount of overflow counts
 * \return The calculated clock value
 */
uint16_t ClockCountsFor16BitTime(uint64_t systemFreq, uint16_t prescaler, float seconds, uint16_t *overflowCounts)
{
    
    //Calculate the number of clock pulses needed by dividing our time desired by the time per clock pulse (1/system frequency)
    float numClockPulses = (seconds / ((double)(1.0/(double)systemFreq)));
    
    //Divide by the prescaler passed to get the calculated TOTAL number of counts
    uint64_t calculatedTotalCounts = (numClockPulses/prescaler)-1;
    
    //Create a variable for the return value
    uint16_t calculatedTimerCounts = 0;
    
    //Reset the overflow counts
    *overflowCounts = 0;
    
    //If the calculated counts are over 16 bit max
    if(calculatedTotalCounts >= 65536)
    {
        *overflowCounts = (uint16_t)(calculatedTotalCounts / 65536);
        calculatedTotalCounts = 65535;
    }
    
    //Convert the calculated total counts to a unsigned short
    calculatedTimerCounts = ((uint16_t)calculatedTotalCounts);
    
    //Return the calculated number of timer counts
    return calculatedTimerCounts;
    
    
}



/**
 * \brief Converts the desired time to the number of required timer counts and the amount of required overflow counts for an 8 bit timer
 * \param systemFreq The frequency to be used
 * \param prescaler The timer prescaler
 * \param seconds The desired time, in seconds
 * \param overflowCounts The amount of overflow counts
 * \return The calculated clock value
 */
uint8_t ClockCountsFor8BitTime(uint64_t systemFreq, uint16_t prescaler, uint16_t seconds, uint16_t *overflowCounts)
{   
    //Calculate the number of clock pulses needed by dividing our time desired by the time per clock pulse (1/system frequency)
    float numClockPulses = (seconds / ((double)(1.0/(double)systemFreq)));
    
    //Divide by the prescaler passed to get the calculated TOTAL number of counts
    uint64_t calculatedTotalCounts = (numClockPulses/prescaler)-1;
    
    //Create a variable for the return value
    uint8_t calculatedTimerCounts = 0;
    
    //Reset the overflow counts
    *overflowCounts = 0;
    
    //If the calculated counts are over 8 bit max
    if(calculatedTotalCounts >= 256)
    {
        *overflowCounts = (uint16_t)(calculatedTotalCounts / 256);
        calculatedTotalCounts = 255;
    }
    
    //Convert the calculated total counts to a unsigned char
    calculatedTimerCounts = ((uint8_t)calculatedTotalCounts);
    
    //Return the calculated number of timer counts
    return calculatedTimerCounts;
    
    
}



/**
 * \brief Converts the desired frequency to the number of required timer counts and the amount of required overflow counts for a 10 bit value
 * \param systemFreq The frequency to be used
 * \param prescaler The timer prescaler
 * \param freqInHz The desired frequency, in Hz
 * \param overflowCounts The amount of overflow counts
 * \return The calculated clock value
 */
uint16_t ClockCountsFor10BitFreq(uint64_t systemFreq, uint16_t prescaler, uint16_t freqInHz, uint16_t *overflowCounts)
{
    //Calculate the time required for the frequency by dividing 1 by the desired frequency
    float calcDesiredFreq = (1.0f/(float)freqInHz);
    
    //Calculate the number of clock pulses needed by dividing our time desired by the time per clock pulse (1/system frequency)
    float numClockPulses = ((float)calcDesiredFreq / ((double)(1.0/(double)systemFreq)));
    
    //Divide by the prescaler passed to get the calculated TOTAL number of counts
    uint64_t calculatedTotalCounts = (numClockPulses/prescaler)-1;
    
    //Create a variable for the return value
    uint16_t calculatedTimerCounts = 0;
    
    //Reset the overflow counts
    *overflowCounts = 0;
    
    //If the calculated counts are over 10 bit max
    if(calculatedTotalCounts >= 1024)
    {
        *overflowCounts = (uint16_t)(calculatedTotalCounts / 1024);
        calculatedTotalCounts = 1024;
    }
    
    //Convert the calculated total counts to a unsigned short
    calculatedTimerCounts = ((uint16_t)calculatedTotalCounts);
    
    //Return the calculated number of timer counts
    return calculatedTimerCounts;
    
    
}







#endif
