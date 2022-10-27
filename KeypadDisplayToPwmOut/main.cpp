/**
 * \file main.cpp
 * \brief 3x4 Keypad Entry, 4x20 CFAH2004 LCD Display, and PWM out
 * \author Tim Robbins
 */ 
#include <avr/io.h>



#include "config.h"

#include "avrTimers.h"
#include "mcuUtils.h"
#include "mcuPinUtils.h"
#include "mcuDelays.h"

#include "mcuAdc.h"
#include "ckeypadMatrix.h"
#include "clcd.h"

//Macros
//-----------------------------------------------------------------------------------------------------------------------------------------

///The value for the prescaler so I don't forget
#define PWM_1_PRESCALER				256

///Gets the frequency value in HZ from the top value passed
#define PWM_1_CALC_FREQ(topValue)	(F_CPU / (PWM_1_PRESCALER*(1+ topValue)))

///Gets the top value required for a specific frequency
#define PWM_1_CALC_TOP(freqInHz)	(F_CPU / (PWM_1_PRESCALER * ( 1 + freqInHz)))

///The maximum Frequency on PWM 1
#define PWM_1_MAX_HZ				65535

///The pwm channel for the pwm frequency
#define PWM_1_FREQ_ADC_CHANNEL		7

///The pwm channel for the pwm 1 A duty cycle
#define PWM_1_A_ADC_CHANNEL			6

///The pwm channel for the pwm 1 B duty cycle
#define PWM_1_B_ADC_CHANNEL			5


//-----------------------------------------------------------------------------------------------------------------------------------------


//Variables
//-----------------------------------------------------------------------------------------------------------------------------------------

inline uint16_t CalculatePwmFreq(uint16_t prescaler, uint16_t hertz)
{
	return (F_CPU / (prescaler * ( 1 + hertz)));
}


///Variable for Timer 1
volatile Timer_t m_udtTimer1;

///Variable for the current frequency for timer 1's pwm outs
volatile uint16_t m_ushtTimer1FrequencyValue = 0x1d0; //Starts at 100 Hz

///Variable for the current duty cycle register value for pwm 1A
volatile uint16_t m_ushtPwm1ADutyCycleValue = 0;

///Variable for the current duty cycle register value for pwm 1B
volatile uint16_t m_ushtPwm1BDutyCycleValue = 0;


///Standard values for the LCDs startup initialization
const unsigned char m_uchrStandardStartupValues[9] =
{

	#if !defined(LCD_USE_4_BIT_MODE) || LCD_USE_4_BIT_MODE != 1
	LCD_MODE_8BIT,
	LCD_MODE_8BIT,
	LCD_MODE_8BIT,
	LCD_MODE_LINE_1_FONT_5x8_8BIT,
	#else
	LCD_MODE_4BIT,
	LCD_MODE_4BIT,
	LCD_MODE_4BIT,
	LCD_MODE_LINE_1_FONT_5x8_4BIT,
	#endif
	LCD_DISPLAY_OFF,
	LCD_CLEAR_SCREEN,
	LCD_MOVE_R_NO_SHIFT,
	LCD_DISPLAY_ON_NO_CURSOR, /*To blink or not to blink? To be even on at all?*/
	//LCD_DISPLAY_ON_CURSOR_BLINK, /*To blink or not to blink? To be even on at all?*/
	0x00
};

///Values for CFAH2004A 4-Line LCD's line start addresses
const unsigned char m_uchrCFAH2004LineStartAddresses[] =
{
	0x00, 0x40, 0x14, 0x54
};


///The pin positions for the columns on the matrix
const uint8_t m_uchrKeypdMatrixColumnPins[KP_COLUMNS] =
{
	0,1,2
};

///The pin positions for the rows on the matrix
const uint8_t m_uchrKeypdMatrixRowPins[KP_ROWS] =
{
	0,1,6,7
};


///The values for the input matrix, when pressed. Adjust for any schematic and button position changes
const uint8_t m_uchrKeypadMatrixValues[KP_ROWS][KP_COLUMNS] =
{
	{
		'1', '2', '3'
	},
	{
		'4', '5', '6'
	},
	{
		'7', '8', '9'
	},
	{
		'*', '0', '#'
	}
};


char m_astrFastPwm1MainScreen[4][21] = 
{
	{
		"Fast: *=Next #=Enter"	
	},
	
	{
		"Frequency:00000Hz"
	},
	
	{
		"Duty Cycle 1A:000%"
	},
	
	{
		"Duty Cycle 1B:000%"
	}
};



//-----------------------------------------------------------------------------------------------------------------------------------------


//Functions
//-----------------------------------------------------------------------------------------------------------------------------------------
void Initialization();
void DisplaySplash();
void Pwm1Init();
void Pwm1SetFreq(uint16_t inHertz);
void Pwm1A_SetDutyCycle(uint8_t percentage);
void Pwm1B_SetDutyCycle(uint8_t percentage);
//-----------------------------------------------------------------------------------------------------------------------------------------


/**
* \brief Main program
*
*/
int main(void)
{
	//Variables
	unsigned char currentKeypress = 0; //The current key pressed on the keypad
	unsigned char previousKeypress = 0; //The previous key pressed on the keypad
	uint8_t currentState = 0; //The current state the program is on
	uint8_t currentPwm1A_DC_Percentage = 0; //The duty cycle percentage for pwm 1A
	uint8_t currentPwm1B_DC_Percentage = 0; //The duty cycle percentage for pwm 1B
	uint16_t currentPwmFreqHz = 0; //The current frequency, in HZ, for PWM 1 
	uint8_t currentDigit = 0; //The current digit the input is on
	char currentFreqInput[5] = {0}; //The current input
	char current1AInput[3] = {0}; //The current input
	char current1BInput[3] = {0}; //The current input	
	
	//Initialize everything
	Initialization();
	
	LcdGoToPosition(1,10);
	
	LcdBlinkingCursorOn();
	
    /* Replace with your application code */
    while (1) 
    {
		//Read any key presses
		currentKeypress = kp_Scan_const(m_uchrKeypdMatrixColumnPins, m_uchrKeypdMatrixRowPins,m_uchrKeypadMatrixValues);
		
		//If there's a new key press that isn't 0...
		if(currentKeypress != 0 && currentKeypress != previousKeypress)
		{
			switch(currentKeypress)
			{
				case '*':
					
					if(currentState == 0)
					{
						currentPwmFreqHz =  (currentFreqInput[0] * 10000);
						currentPwmFreqHz += (currentFreqInput[1] * 1000);
						currentPwmFreqHz += (currentFreqInput[2] * 100);
						currentPwmFreqHz += (currentFreqInput[3] * 10);
						currentPwmFreqHz += (currentFreqInput[4]);
					}
					else if(currentState == 1)
					{
						
						currentPwm1A_DC_Percentage = (current1AInput[0] * 100);
						currentPwm1A_DC_Percentage += (current1AInput[1] * 10);
						currentPwm1A_DC_Percentage += (current1AInput[2]);
					}
					else
					{
						currentPwm1B_DC_Percentage = (current1BInput[0] * 100);
						currentPwm1B_DC_Percentage += (current1BInput[1] * 10);
						currentPwm1B_DC_Percentage += (current1BInput[2]);
					}
				
					//Add to the current state
					currentState += 1;
					
					//If the current state is greater than or equal to 3 (The amount of items to set)...
					if( currentState >= 3)
					{
						currentState = 0;
					};
					
					//Reset the currently active digit
					currentDigit = 0;
	
					//Set the percentages and frequencies before changing states
					Pwm1SetFreq(currentPwmFreqHz);
					Pwm1A_SetDutyCycle(currentPwm1A_DC_Percentage);
					Pwm1B_SetDutyCycle(currentPwm1B_DC_Percentage);
					
					
					
					if(currentState == 0)
					{
						LcdGoToPosition(1,10);
					}
					else if(currentState == 1)
					{
						
						LcdGoToPosition(2,14);
					}
					else
					{
						LcdGoToPosition(3,14);
					}
					
					
					
				break;
				
				case '#':
					currentDigit = 0;
					
					//Set the values for
					switch(currentState)
					{
						case 0:
						
							currentPwmFreqHz =  (currentFreqInput[0] * 10000);
							currentPwmFreqHz += (currentFreqInput[1] * 1000);
							currentPwmFreqHz += (currentFreqInput[2] * 100);
							currentPwmFreqHz += (currentFreqInput[3] * 10);
							currentPwmFreqHz += (currentFreqInput[4]);
							
							if(currentPwmFreqHz > PWM_1_MAX_HZ)
							{
								currentPwmFreqHz = PWM_1_MAX_HZ;
							}
							LcdPrintNumericalShortDelayAtPosition(currentPwmFreqHz,1,10,50000);
							delayForMilliseconds(10);
							Pwm1SetFreq(currentPwmFreqHz);
							
							
						break;
						
						case 1:
						
							currentPwm1A_DC_Percentage = (current1AInput[0] * 100);
							currentPwm1A_DC_Percentage += (current1AInput[1] * 10);
							currentPwm1A_DC_Percentage += (current1AInput[2]);
							
							
							Pwm1A_SetDutyCycle(currentPwm1A_DC_Percentage);
							LcdPrintNumericalByteDelayAtPosition(currentPwm1A_DC_Percentage,2,14,50000);
							LcdGoToPosition(2,14);
							delayForMilliseconds(10);
							
							
	
						break;
						
						case 2:
							currentPwm1B_DC_Percentage = (current1BInput[0] * 100);
							currentPwm1B_DC_Percentage += (current1BInput[1] * 10);
							currentPwm1B_DC_Percentage += (current1BInput[2]);
							
							Pwm1B_SetDutyCycle(currentPwm1B_DC_Percentage);
							
							LcdPrintNumericalByteDelayAtPosition(currentPwm1B_DC_Percentage,3,14,50000);
							LcdGoToPosition(3,14);
							delayForMilliseconds(10);
		
							
						break;
						
						default:
							currentState = 0;
							
						break;
					};
				break;
				
				default:
					switch(currentState)
					{
						case 0:
							if(currentDigit >= 5)
							{
								currentDigit = 4;
							}
							
							
							//Display the pressed key
							LcdPrintCharDelayAtPosition(currentKeypress,1,(10 + (currentDigit)),10000);
							
							currentFreqInput[currentDigit] = (currentKeypress - 0x30);
							
						break;
						
						case 1:
							if(currentDigit >= 3)
							{
								currentDigit = 2;
							}
							
							LcdPrintCharDelayAtPosition(currentKeypress,2,(14 + (currentDigit)),10000);
							current1AInput[currentDigit] = (currentKeypress - 0x30);
							
							
						break;
						
						case 2:
							if(currentDigit >= 3)
							{
								currentDigit = 2;
							}
							LcdPrintCharDelayAtPosition(currentKeypress,3,(14 + (currentDigit)),10000);
							current1BInput[currentDigit] = (currentKeypress - 0x30);
							
						break;
						
						default:
						break;
					};
					currentDigit++;
				break;
				
				
			};
			
			
		}
		
		//Debounce
		delayForMilliseconds(100);
		
		//Set the previous key press variable
		previousKeypress = currentKeypress;
		
    }
}



/**
* \brief Initializes the Controller
*
*/
void Initialization()
{
	//Reset pins
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	DDRA = FULL_OUTPUT;
	DDRB = FULL_OUTPUT;
	DDRC = FULL_OUTPUT;
	DDRD = FULL_OUTPUT;
	
	
	
	//Initialize the display
	LcdConstInit(m_uchrStandardStartupValues, m_uchrCFAH2004LineStartAddresses);
	
	//Display the splash screen
	DisplaySplash();
	
	//Initialize the ADC
	DDRA &= ~(1 << PWM_1_A_ADC_CHANNEL | 1 << PWM_1_B_ADC_CHANNEL | 1 << PWM_1_FREQ_ADC_CHANNEL); //Input
	
	ADC_adjust_right(); //Right justify results
	ADCSRB = (0x00 << ADTS0); //Free running mode
	ADMUX = ADC_REF_MODE_1; //Set admux mode
	ADC_enable(); //Turn on ADC
	
	//Initialize the PWM
	Pwm1Init();
}



/**
* \brief Displays the splash screen for the controller
*
*/
void DisplaySplash()
{
	//Clear the screen
	LcdClearScreen();
	
	LcdCursorOff();
	
	//Print design
	for(uint8_t i = 0; i < (LCD_ROW_COUNT * LCD_COLUMN_COUNT); i++)
	{
		LcdPrintCharDelay('-',10000);
	}
	
	
	//Print at the appropriate location
	LcdGoToPosition(1,5);
	LcdPrintDelay("PWM 1",10000);
	LcdGoToPosition(2,8);
	LcdPrintDelay("Generator",10000);
	
	
	
	//Display module
	LcdGoToPosition(3,4);
	LcdPrintDelay("-Version 1.0-", 10000);
	delayForTenthSeconds(10);
	
	//Clear design in cool way
	LcdPrintDelayAtPosition("                    ",0,0,10000);
	LcdPrintDelayAtPosition("                    ",3,0,10000);
	LcdPrintDelayAtPosition("                    ",1,0,10000);
	LcdPrintDelayAtPosition("                    ",2,0,10000);
	
	
	for(uint8_t i = 0; i < 4; i++)
	{
		LcdPrintDelayAtPosition(m_astrFastPwm1MainScreen[i],i,0,10000);
	}
}



/**
* \brief Initializes the PWM on Timer 1
*
*/
void Pwm1Init()
{
	//Setting to 0 in case timer 1 is already running
	TCCR1B = 0;
	
	
	//Make sure timer enabled in power register
	#if defined(PRR)
		PRR &= ~(1 << PRTIM1);
	#elif defined(PRR0)
		PRR0 &= ~(1 << PRTIM1);
	#endif
	
	
	//Write the PWM output pins to low. Using OCR1 for PWM generation
	PIN_WRITE(OC1B_PIN,LOW,OUTPUT);
	PIN_WRITE(OC1A_PIN,LOW,OUTPUT);
	
	
	//Set prescaler 256
	m_udtTimer1.prescaler.cs0                    = 0;
	m_udtTimer1.prescaler.cs1                    = 0;
	m_udtTimer1.prescaler.cs2                    = 1;
	
	//Set for pwm mode, FAST pwm with ICR1 as TOP
	m_udtTimer1.waveform.WGM0                    = 0;
	m_udtTimer1.waveform.WGM1                    = 1;
	m_udtTimer1.waveform.WGM2                    = 1;
	m_udtTimer1.waveform.WGM3                    = 1;
	
	//Set output modes
	m_udtTimer1.output_mode.comA			        = 2;
	m_udtTimer1.output_mode.comB			        = 2;
	m_udtTimer1.output_mode.forceOutA	        = 0;
	m_udtTimer1.output_mode.forceOutB	        = 0;
	
	//Set interrupts to none
	m_udtTimer1.interrupts.outputCompareMatchA	= 0;
	m_udtTimer1.interrupts.outputCompareMatchB	= 0;
	m_udtTimer1.interrupts.overflow				= 0;
	
	
	//Set frequency value
	ICR1 = 0;
	
	//Set interrupts
	TIMSK1 = (m_udtTimer1.interrupts.outputCompareMatchA << OCIE1A | m_udtTimer1.interrupts.outputCompareMatchB << OCIE1B | m_udtTimer1.interrupts.overflow << TOIE1);

	//Setting force out bits
	TCCR1C = (m_udtTimer1.output_mode.forceOutA << FOC1A | m_udtTimer1.output_mode.forceOutB << FOC1B);
	
	//Setting output mode
	TCCR1A = (m_udtTimer1.output_mode.comA << COM1A0 | m_udtTimer1.output_mode.comB << COM1B0);
	
	//Setting waveform bits
	TCCR1A |= (m_udtTimer1.waveform.WGM0 << WGM10 | m_udtTimer1.waveform.WGM1 << WGM11);
	TCCR1B = (m_udtTimer1.waveform.WGM2 << WGM12 | m_udtTimer1.waveform.WGM3 << WGM13);
	
	//Setting initial duty cycle to 0
	PwmOCR1A_SetDutyCycle(0);
	PwmOCR1B_SetDutyCycle(0);
	
	
	
	//Setting m_uchrPrescaler to start timer. We will keep it running and control PWM output through duty cycle settings alone
	TCCR1B |= (m_udtTimer1.prescaler.cs0 << CS10 | m_udtTimer1.prescaler.cs1 << CS11 | m_udtTimer1.prescaler.cs2 << CS12);
	
}



void Pwm1SetFreq(uint16_t inHertz)
{
	if(inHertz > PWM_1_MAX_HZ)
	{
		inHertz = PWM_1_MAX_HZ;
	}
	
	//m_ushtTimer1FrequencyValue = PWM_1_CALC_TOP(inHertz);
	TCCR1B &= ~(1 << CS10 | 1 << CS11 | 1 << CS12);
	
	if(inHertz >= 5000)
	{
		//Set prescaler 1
		m_udtTimer1.prescaler.cs0                    = 1;
		m_udtTimer1.prescaler.cs1                    = 0;
		m_udtTimer1.prescaler.cs2                    = 0;
		
		m_ushtTimer1FrequencyValue = CalculatePwmFreq(1,inHertz);
	}
	else if(inHertz >= 1000)
	{
		//Set prescaler 8
		m_udtTimer1.prescaler.cs0                    = 0;
		m_udtTimer1.prescaler.cs1                    = 1;
		m_udtTimer1.prescaler.cs2                    = 0;
		
		m_ushtTimer1FrequencyValue = CalculatePwmFreq(8,inHertz);
	}
	else if(inHertz >= 200)
	{
		//Set prescaler 64
		m_udtTimer1.prescaler.cs0                    = 1;
		m_udtTimer1.prescaler.cs1                    = 1;
		m_udtTimer1.prescaler.cs2                    = 0;
		
		m_ushtTimer1FrequencyValue = CalculatePwmFreq(64,inHertz);
	}
	else if(inHertz >= 50)
	{
		//Set prescaler 256
		m_udtTimer1.prescaler.cs0                    = 0;
		m_udtTimer1.prescaler.cs1                    = 0;
		m_udtTimer1.prescaler.cs2                    = 1;
		
		m_ushtTimer1FrequencyValue = CalculatePwmFreq(256,inHertz);
	}
	else
	{
		//Set prescaler 1024
		m_udtTimer1.prescaler.cs0                    = 1;
		m_udtTimer1.prescaler.cs1                    = 0;
		m_udtTimer1.prescaler.cs2                    = 1;
		
		m_ushtTimer1FrequencyValue = CalculatePwmFreq(1024,inHertz);
	}
	
	
	ICR1 = m_ushtTimer1FrequencyValue;
	TCCR1B |= (m_udtTimer1.prescaler.cs0 << CS10 | m_udtTimer1.prescaler.cs1 << CS11 | m_udtTimer1.prescaler.cs2 << CS12);
	Pwm1A_SetDutyCycle((ConvertRangeToPercentage(0,m_ushtTimer1FrequencyValue,m_ushtPwm1ADutyCycleValue)));
	Pwm1B_SetDutyCycle((ConvertRangeToPercentage(0,m_ushtTimer1FrequencyValue,m_ushtPwm1BDutyCycleValue)));
	
	LcdPrintNumericalByteDelayAtPosition((ConvertRangeToPercentage(0,m_ushtTimer1FrequencyValue,m_ushtPwm1ADutyCycleValue)),2,14,50000);
	delayForMilliseconds(10);
	LcdPrintNumericalByteDelayAtPosition((ConvertRangeToPercentage(0,m_ushtTimer1FrequencyValue,m_ushtPwm1BDutyCycleValue)),3,14,50000);
	LcdGoToPosition(1,10);
	
	
	
}
void Pwm1A_SetDutyCycle(uint8_t percentage)
{
	if(percentage > 100)
	{
		percentage = 100;
	}
	
	m_ushtPwm1ADutyCycleValue = (ConvertPercentage(m_ushtTimer1FrequencyValue,percentage));
	
	PwmOCR1A_SetDutyCycle(m_ushtPwm1ADutyCycleValue);
	

	
	
	
}
void Pwm1B_SetDutyCycle(uint8_t percentage)
{
	if(percentage > 100)
	{
		percentage = 100;
	}
	
	
	m_ushtPwm1BDutyCycleValue = (ConvertPercentage(m_ushtTimer1FrequencyValue,percentage));
	PwmOCR1B_SetDutyCycle(m_ushtPwm1BDutyCycleValue);
	

	
}
