/**
 * \file clcd.c
 * \author Tim Robbins
 * \brief C Source file for LCD
 */
#include "clcd.h"

#if !defined(CLCD_C) && defined(__INCLUDED_CLCD__)
#define CLCD_C 1



///The first positions in each row, in order from top to bottom
unsigned char m_auchrLineStartValues[LCD_ROW_COUNT];

///The line we're currently at on the LCD
unsigned char m_uchrCurrentLine = 0;

///The column we're currently at on the LCD
unsigned char m_uchrCurrentColumn = 0;


/**
* \brief Initializes the LCD from CONST values
* \param startupSequence The sequence to run through the startup. Should be the initialization sequence in the datasheets followed by any additional commands.
* \param lineStartPositions The position at the beginning or each line on the display. Must be ordered from top to bottom
*/
void LcdConstInit(const unsigned char startupSequence[], const unsigned char lineStartPositions[])
{
	//Variables
	unsigned char index = 0; //Index for looping through the passed arrays.
	unsigned char currentByte = 0; //The current byte we're on in the parameters.
	
	LCD_CONTROL_PORT &= ~(1 << LCD_E_PIN | 1 << LCD_RS_PIN | 1 << LCD_RW_PIN);
	
	#if !defined(LCD_USE_4_BIT_MODE) || LCD_USE_4_BIT_MODE != 1
	
	//Set the data pins to output
	writeMaskOutput(LCD_DATA_PORT_DIR, 0xFF);

	#else

	//Set the data pins to output
	writeMaskOutput(LCD_DATA_PORT_DIR, LCD_4_BIT_DATA_PIN_MASK);

	#endif
	

	//Loop through the initialization values and send as commands
	for(index = 0; startupSequence[index] != '\0'; index++)
	{
		currentByte = startupSequence[index];
		LcdSendCommand(currentByte);
		delayForMilliseconds(10);
	}
	
	//Copy the line start positions
	for(index = 0; index < LCD_ROW_COUNT; index++)
	{
		currentByte = lineStartPositions[index];
		m_auchrLineStartValues[index] = currentByte;
	}

	delayForMicroseconds(10);
}



/**
* \brief Creates and stores the custom character at the address passed
* \param uchrAddress The address to store the character at
* \param auchrCharacter Array of the characters "dots" to save
*/
void LcdStoreCustomConstCharacter(unsigned char uchrAddress, const unsigned char auchrCharacter[8])
{
	LcdSendCommand(LCD_CG_RAM_CMD + uchrAddress);

	for(unsigned char i = 0; i < 8; i++) {

		LcdSendData(auchrCharacter[i]);
		delayForMicroseconds(10);
	}
	
}



/**
* \brief Lcd initializer function. Runs through the startup sequence passed and copies the line start positions passed.
* \param startupSequence The sequence to run through the startup. Should be the initialization sequence in the datasheets followed by any additional commands.
* \param lineStartPositions The position at the beginning or each line on the display. Must be ordered from top to bottom
*/
void LcdInit(unsigned char startupSequence[], unsigned char lineStartPositions[])
{
	
	//Variables
	unsigned char index = 0; //Index for looping through the passed arrays.
    unsigned char currentByte = 0; //The current byte we're on in the parameters.
	
	LCD_CONTROL_PORT &= ~(1 << LCD_E_PIN | 1 << LCD_RS_PIN | 1 << LCD_RW_PIN);
	
	#if !defined(LCD_USE_4_BIT_MODE) || LCD_USE_4_BIT_MODE != 1
	
	//Set the data pins to output
	writeMaskOutput(LCD_DATA_PORT_DIR, 0xFF);

	#else

	//Set the data pins to output
	writeMaskOutput(LCD_DATA_PORT_DIR, LCD_4_BIT_DATA_PIN_MASK);

	#endif
	

	//Loop through the initialization values and send as commands
	for(index = 0; startupSequence[index] != '\0'; index++) 
	{
        currentByte = startupSequence[index];
		LcdSendCommand(currentByte);
		delayForMilliseconds(10);
	}
	
	//Copy the line start positions
	for(index = 0; index < LCD_ROW_COUNT; index++) 
	{
	 	currentByte = lineStartPositions[index];
	 	m_auchrLineStartValues[index] = currentByte;
	 }

	delayForMicroseconds(10);
}



/**
 * \brief Returns the current line the LCD is on
 * 
 * 
 * \return unsigned char The current line
 */
unsigned char LcdGetCurrentLine() 
{
	return m_uchrCurrentLine;
}



/**
 * \brief Returns the current column the LCD is on
 * 
 * 
 * \return unsigned char The current column
 */
unsigned char LcdGetCurrentColumn() 
{
	return m_uchrCurrentColumn;
}



/**
 * \brief Sends a command to the LCD
 * 
 * 
 * \param cmd The command to send
 */
void LcdSendCommand(unsigned char cmd) 
{
	LCD_CONTROL_PORT &= ~(1 << LCD_RS_PIN | 1 << LCD_RW_PIN);
	LCD_CONTROL_PORT |= (1 << LCD_E_PIN);
	

	#if !defined(LCD_USE_4_BIT_MODE) || LCD_USE_4_BIT_MODE != 1
	LCD_DATA_PORT &= ~(0xFF);
	LCD_DATA_PORT |= cmd;
	LCD_CONTROL_PORT &= ~(1 << LCD_E_PIN);
	delayForMilliseconds(1);
	#else

	LCD_DATA_PORT &= (~LCD_4_BIT_DATA_PIN_MASK);
	LCD_DATA_PORT |= (__LCD_4_BIT_VAL_WRITER_HELPER_HIGH(cmd));
	LCD_CONTROL_PORT &= ~(1 << LCD_E_PIN);
	delayForMilliseconds(1);
	LCD_CONTROL_PORT |= (1 << LCD_E_PIN);
	
	LCD_DATA_PORT &= (~LCD_4_BIT_DATA_PIN_MASK);
	LCD_DATA_PORT |= (__LCD_4_BIT_VAL_WRITER_HELPER_LOW(cmd));
	LCD_CONTROL_PORT &= ~(1 << LCD_E_PIN);
	delayForMilliseconds(1);

	#endif

	
}



/**
* \brief Sends a data value to the LCD
* \param data The data to send
*/
void LcdSendData(unsigned char data) 
{
	LCD_CONTROL_PORT &= ~(1 << LCD_RW_PIN);
	LCD_CONTROL_PORT |= (1 << LCD_RS_PIN);
	LCD_CONTROL_PORT |= (1 << LCD_E_PIN);
	

	#if !defined(LCD_USE_4_BIT_MODE) || LCD_USE_4_BIT_MODE != 1
	
	LCD_DATA_PORT &= ~(0xFF);
	LCD_DATA_PORT |= data;
	LCD_CONTROL_PORT &= ~(1 << LCD_E_PIN);
	delayForMilliseconds(1);

	#else

	LCD_DATA_PORT &= (~LCD_4_BIT_DATA_PIN_MASK);
	LCD_DATA_PORT |= (__LCD_4_BIT_VAL_WRITER_HELPER_HIGH(data));
	LCD_CONTROL_PORT &= ~(1 << LCD_E_PIN);
	delayForMilliseconds(1);
	LCD_CONTROL_PORT |= (1 << LCD_E_PIN);
	
	LCD_DATA_PORT &= (~LCD_4_BIT_DATA_PIN_MASK);
	LCD_DATA_PORT |= (__LCD_4_BIT_VAL_WRITER_HELPER_LOW(data));
	LCD_CONTROL_PORT &= ~(1 << LCD_E_PIN);
	delayForMilliseconds(1);

	#endif
}



/**
* \brief Sends char generator data to the LCD
*
*/
void LcdStoreCGData(unsigned char cgAddress, unsigned char data[], uint8_t dataLength)
{
	LCD_set_cg_ram((cgAddress));

	for(unsigned char i=0; i < dataLength; i++) 
	{
		LcdSendData(data[i]);
		delayForMicroseconds(37);
	}
	
	
}



/**
* \brief Waits for the LCD's busy flag to trigger
*
*/
void LcdBusyFlagWait() 
{
	//Set RW pin for READ mode
	LCD_CONTROL_PORT &= ~(1 << LCD_RS_PIN);
	LCD_CONTROL_PORT |= ( 1 << LCD_RW_PIN);

	delayForMilliseconds(20);
	
	//Set the busy flag pin to input
	LCD_DATA_PORT |= (1 << LCD_BUSY_FLAG_POSITION);
	
	setBitInput(LCD_DATA_PORT_DIR, LCD_BUSY_FLAG_POSITION);
	
	//Toggle the E pin while the busy flag is high
	do
	{
		LCD_CONTROL_PORT |= (1 << LCD_E_PIN);
		delayForMicroseconds(1);
		LCD_CONTROL_PORT &= ~(1 << LCD_E_PIN);
	} while (readBit(LCD_DATA_PORT_READ,LCD_BUSY_FLAG_POSITION));
	
	
	//Reset
	LCD_CONTROL_PORT &= ~(1 << LCD_RS_PIN | 1 << LCD_RW_PIN | 1 << LCD_E_PIN);
	setBitOutput(LCD_DATA_PORT_DIR, LCD_BUSY_FLAG_POSITION);
}



/**
* \brief Turns the LCD on and optionally sets the cursor on and sets the cursors blink blinking
* \param cursorOn If the cursor is on or not
* \param cursorBlink If the cursor is on, sets whether or not the cursor is a blinking cursor
*/
void LcdDisplayOn(bool cursorOn, bool cursorBlink)
{
	if(cursorOn) {
		if(cursorBlink) LcdSendCommand(LCD_DISPLAY_ON_CURSOR_BLINK);
		else LcdSendCommand(LCD_DISPLAY_ON_NO_BLINK);
	}
	else {
		LcdSendCommand(LCD_DISPLAY_ON_NO_CURSOR);
	}
}



/**
* \brief Clears the line passed
* \param uchrLine The line to clear
*/
void LcdClearLine(unsigned char uchrLine) 
{
	if(uchrLine < LCD_ROW_COUNT) {
		unsigned char savedColumn = m_uchrCurrentColumn;
		unsigned char savedRow = m_uchrCurrentLine;
		LcdGoToPosition(uchrLine, 0);
		for(unsigned char i = 0; i < LCD_COLUMN_COUNT-1; i++) {
			LcdPrintChar(' ');
		}
		LcdGoToPosition(savedRow, savedColumn);
	}
}



/**
* \brief Clears the line passed starting at the column passed
* \param uchrLine The line to clear
* \param uchrColumn The column to begin clearing at
*/
void LcdClearLineFromColumn(unsigned char uchrLine, unsigned char uchrColumn) 
{
	if(uchrLine < LCD_ROW_COUNT && uchrColumn < LCD_COLUMN_COUNT - 1) {
		unsigned char savedColumn = m_uchrCurrentColumn;
		unsigned char savedRow = m_uchrCurrentLine;
		LcdGoToPosition(uchrLine, uchrColumn);
		for(unsigned char i = uchrColumn; i < LCD_COLUMN_COUNT-1; i++) {
			LcdPrintChar(' ');
		}
		LcdGoToPosition(savedRow, savedColumn);
	}
}



/**
* \brief Clears the line passed starting at the start column passed and ending at the ending column passed
* \param uchrLine The line to clear
* \param uchrStartColumn The column to begin clearing at
* \param uchrEndColumn The column to stop clearing at
*/
void LcdClearLineAtColumns(unsigned char uchrLine, unsigned char uchrStartColumn, unsigned char uchrEndColumn) 
{
    
    
	if(uchrLine < LCD_ROW_COUNT && (uchrStartColumn < LCD_COLUMN_COUNT - 1 || uchrEndColumn < LCD_COLUMN_COUNT - 1)) {
		unsigned char savedColumn = m_uchrCurrentColumn;
		unsigned char savedRow = m_uchrCurrentLine;
		LcdGoToPosition(uchrLine, uchrStartColumn);
		for(unsigned char i = uchrStartColumn; i < LCD_COLUMN_COUNT-1 && i < uchrEndColumn; i++) {
			LcdPrintChar(' ');
		}
		LcdGoToPosition(savedRow, savedColumn);
	}
}



/**
* \brief Clears the position passed
* \param uchrLine The line to clear
* \param uchrColumn The column position to clear
*/
void LcdClearPosition(unsigned char uchrLine, unsigned char uchrColumn) 
{
	if(uchrLine < LCD_ROW_COUNT && uchrColumn < LCD_COLUMN_COUNT - 1) {
		unsigned char savedColumn = m_uchrCurrentColumn;
		unsigned char savedRow = m_uchrCurrentLine;
		LcdGoToPosition(uchrLine, uchrColumn);
		LcdPrintChar(' ');
		LcdGoToPosition(savedRow, savedColumn);
	}
}



/**
* \brief Creates and stores the customer character dot line at the address passed
* \param uchrAddress The address to store the character at
* \param uchrNewDot The character "dots" to save
*/
void LcdStoreDotRow(unsigned char uchrAddress, unsigned char uchrNewDot) 
{
	LCD_set_cg_ram(uchrAddress);
	LcdSendData(uchrNewDot);
	LcdBusyFlagWait();
}



/**
* \brief Creates and stores the custom character at the address passed
* \param uchrAddress The address to store the character at
* \param auchrCharacter Array of the characters "dots" to save
*/
void LcdStoreCustomCharacter(unsigned char uchrAddress, unsigned char auchrCharacter[8]) 
{
	LcdSendCommand(LCD_CG_RAM_CMD + uchrAddress);
	
	for(unsigned char i = 0; i < 8; i++) {

		LcdSendData(auchrCharacter[i]);
		delayForMicroseconds(10);
	}
}



/**
* \brief Reads and returns the address counter from the LCD
*
*/
unsigned char LcdGetAddressCounter() 
{
	//Variables
	unsigned char address = 0; //The address returned
	
	//Set RW pin for READ mode
	LCD_CONTROL_PORT &= ~(1 << LCD_RS_PIN);
	LCD_CONTROL_PORT |= ( 1 << LCD_RW_PIN);

	delayForMilliseconds(20);
	
	//Set the busy flag pin to input
	
	#if !defined(LCD_USE_4_BIT_MODE) || LCD_USE_4_BIT_MODE != 1
	LCD_DATA_PORT |= (0xFF);
	LCD_DATA_PORT_DIR = (FULL_INPUT);
	#else
	LCD_DATA_PORT |= ((1 << LCD_BUSY_FLAG_POSITION) | (1 << LCD_D6) | (1 << LCD_D5) | (1 << LCD_D4));
	writeMaskInput(LCD_DATA_PORT_DIR, ((1 << LCD_BUSY_FLAG_POSITION) | (1 << LCD_D6) | (1 << LCD_D5) | (1 << LCD_D4)));
	#endif	
	
	
	//Toggle the E pin while the busy flag is high
	do
	{
		LCD_CONTROL_PORT |= (1 << LCD_E_PIN);
		delayForMicroseconds(1);
		LCD_CONTROL_PORT &= ~(1 << LCD_E_PIN);

	} while (readBit(LCD_DATA_PORT_READ,LCD_BUSY_FLAG_POSITION));
	
	address = readBit(LCD_DATA_PORT_READ,LCD_BUSY_FLAG_POSITION);
	address &= ~(1 << LCD_BUSY_FLAG_POSITION);

	//Reset
	LCD_CONTROL_PORT &= ~(1 << LCD_RS_PIN | 1 << LCD_RW_PIN | 1 << LCD_E_PIN);
	
	#if !defined(LCD_USE_4_BIT_MODE) || LCD_USE_4_BIT_MODE != 1
	LCD_DATA_PORT_DIR = (FULL_OUTPUT);
	#else
	writeMaskOutput(LCD_DATA_PORT_DIR, ((1 << LCD_BUSY_FLAG_POSITION) | (1 << LCD_D6) | (1 << LCD_D5) | (1 << LCD_D4)));
	#endif

	return address;
}



/**
* \brief Goes to the position on th LCD passed
* \param uchrLine The line to go to
* \param uchrColumn The column to go to
*/
void LcdGoToPosition(unsigned char uchrLine, unsigned char uchrColumn) 
{
	if(uchrLine > LCD_ROW_COUNT -1) 
	{
		m_uchrCurrentLine = LCD_ROW_COUNT - 1;
	}
	else
	{
		m_uchrCurrentLine = uchrLine;	
	}
	
	if(uchrColumn > LCD_COLUMN_COUNT-1) 
	{
		m_uchrCurrentColumn = LCD_COLUMN_COUNT - 1;
	}
	else
	{
		m_uchrCurrentColumn = uchrColumn;	
	}
	
	
	unsigned char uchrNewAddress = ((m_auchrLineStartValues[m_uchrCurrentLine]) + m_uchrCurrentColumn);
	LCD_set_dd_ram(uchrNewAddress);
}



/**
* \brief Performs the action associated with the command passed. Example: LCD_RETURN_HOME will run the return home command.
* \param cmd The command to perform
*/
void LcdPerformCommand(unsigned char cmd) 
{
	 switch (cmd)
    {
    case LCD_RETURN_HOME://Return home
        m_uchrCurrentColumn = 0;
        m_uchrCurrentLine = 0;
        LcdSendCommand(LCD_RETURN_HOME);
        break;

    case LCD_CR://Carriage return
        m_uchrCurrentColumn = 0;
		LcdGoToPosition(m_uchrCurrentLine, m_uchrCurrentColumn);	
        break;

    
	case LCD_CLEAR_SCREEN:
        m_uchrCurrentColumn = 0;
        m_uchrCurrentLine = 0;
        LcdSendCommand(LCD_CLEAR_SCREEN);
        break;
		
	case LCD_FF:
        m_uchrCurrentColumn = 0;
        m_uchrCurrentLine = 0;
        LcdSendCommand(LCD_CLEAR_SCREEN);
        break;
		
    case LCD_LF: //Line feed \n
		m_uchrCurrentColumn = 0;
        if(m_uchrCurrentLine < LCD_ROW_COUNT-1) {
			m_uchrCurrentLine += 1;
		}
		else {
			m_uchrCurrentLine = 0;
			LcdSendCommand (LCD_CLEAR_SCREEN);
		}
		
		LcdGoToPosition(m_uchrCurrentLine, m_uchrCurrentColumn);
        break;
		
	case LCD_TAB:
		LcdPrintString("    ");
		break;
	
    case LCD_TOP: //Top
        m_uchrCurrentLine = 0;
        LcdGoToPosition(m_uchrCurrentLine, m_uchrCurrentColumn);
        break;

	case LCD_BOTTOM:
		m_uchrCurrentLine = LCD_ROW_COUNT - 1;
        LcdGoToPosition(m_uchrCurrentLine, m_uchrCurrentColumn);
		break;

    case LCD_UP: //Up
        if(m_uchrCurrentLine > 0) {
			m_uchrCurrentLine -= 1;
			LcdGoToPosition(m_uchrCurrentLine, m_uchrCurrentColumn);
		}
        break;

    case LCD_DN: //Down
	
        if(m_uchrCurrentLine < LCD_ROW_COUNT-1) {
	        m_uchrCurrentLine += 1;
	        LcdGoToPosition(m_uchrCurrentLine, m_uchrCurrentColumn);
        }
        break;

    case LCD_BS: //Backspace
		
		if(m_uchrCurrentColumn > 0) {
			m_uchrCurrentColumn -= 1;
			LcdSendCommand(LCD_CURSOR_SHIFT_L);
			LcdPrintChar(' ');
			m_uchrCurrentColumn -= 1;
			LcdSendCommand(LCD_CURSOR_SHIFT_L);
		}
		else if(m_uchrCurrentLine > 0) {
			m_uchrCurrentColumn = LCD_COLUMN_COUNT - 1;
			m_uchrCurrentLine -= 1;
			LcdGoToPosition(m_uchrCurrentLine, m_uchrCurrentColumn);
			LcdPrintChar(' ');
			m_uchrCurrentColumn = LCD_COLUMN_COUNT - 1;
			m_uchrCurrentLine -= 1;
			LcdSendCommand (LCD_CURSOR_SHIFT_L);
		}
		
        break;

    case LCD_RT: //Right
		if(m_uchrCurrentColumn < LCD_COLUMN_COUNT - 1) {
			m_uchrCurrentColumn++;
			LcdSendCommand (LCD_CURSOR_SHIFT_R);
		}
        break;

    case LCD_LFT: //Left
        if(m_uchrCurrentColumn > 0) {
	        m_uchrCurrentColumn--;
			LcdSendCommand (LCD_CURSOR_SHIFT_L);
        }
        break;
		
    default:
        break;
		
		
    }
}



/**
* \brief Sends a byte as a command if under 0x20(' ') or as a data if over
* \param uchrByte The data byte to send
*/
void LcdSendByte(unsigned char uchrByte) 
{
	if(uchrByte < 0x20) {
        LcdPerformCommand(uchrByte);
    }
    else {
		LcdPrintChar(uchrByte);
    }
}



/**
* \brief Sends a byte as a command if under 0x20(' ') or as a data if over and delays for the amount of microseconds passed afterwards
* \param uchrByte The data byte to send
* \param ushtDelayTime The amount of microseconds to delay for
*/
void LcdSendByteDelay(unsigned char uchrByte, unsigned short ushtDelayTime) 
{
	if(uchrByte < 0x20) {
        LcdPerformCommand(uchrByte);
    }
    else {
		LcdPrintChar(uchrByte);
    }
	
	delayForMicroseconds(ushtDelayTime);
}



/**
* \brief Sends a byte as a command if under 0x20(' ') or as a data if over at the position passed
* \param uchrByte The data byte to send
* \param uchrRow The row for the byte to display at
* \param uchrColumn The column for the byte to display at
*/
void LcdSendByteAtPosition(unsigned char uchrByte, unsigned char uchrRow, unsigned char uchrColumn) 
{
	
	LcdGoToPosition(uchrRow, uchrColumn);

	if(uchrByte < 0x20) {
        LcdPerformCommand(uchrByte);
    }
    else {
		LcdPrintChar(uchrByte);
    }
}



/**
* \brief Sends a byte as a command if under 0x20(' ') or as a data if over at the positions passed and delays for the amount of microseconds passed
* \param uchrByte The data byte to send
* \param uchrRow The row for the byte to display at
* \param uchrColumn The column for the byte to display at
* \param ushtDelayTime The amount of microseconds to delay for
*/
void LcdSendByteDelayAtPosition(unsigned char uchrByte, unsigned char uchrRow, unsigned char uchrColumn, unsigned short ushtDelayTime) 
{
	
	LcdGoToPosition(uchrRow, uchrColumn);
	
	if(uchrByte < 0x20) {
        LcdPerformCommand(uchrByte);
    }
    else {
		LcdPrintChar(uchrByte);
    }
	
	delayForMicroseconds(ushtDelayTime);
}



/**
* \brief Prints the passed character verbatim onto the LCD display
* \param uchrChar The character to print
*/
void LcdPrintChar(char uchrChar) 
{
	
	if(m_uchrCurrentColumn > LCD_COLUMN_COUNT-1) {
		if(m_uchrCurrentLine > LCD_ROW_COUNT-1) {
			LcdSendCommand(LCD_CLEAR_SCREEN);
			m_uchrCurrentColumn = 0;
			m_uchrCurrentLine = 0;
		}
		else {
			m_uchrCurrentColumn = 0;
			m_uchrCurrentLine += 1;
		}
	}
	
	LcdGoToPosition(m_uchrCurrentLine, m_uchrCurrentColumn);
	
	LcdSendData(uchrChar);
    
    m_uchrCurrentColumn+=1;
}



/**
* \brief Prints the passed character verbatim onto the LCD display and delays for the amount of microseconds passed
* \param uchrChar The character to print
* \param ushtDelayTime The amount of microseconds to delay for
*/
void LcdPrintCharDelay(char uchrChar, unsigned short ushtDelayTime) 
{
	
	if(m_uchrCurrentColumn > LCD_COLUMN_COUNT-1) {
		if(m_uchrCurrentLine > LCD_ROW_COUNT-1) {
			LcdSendCommand(LCD_CLEAR_SCREEN);
			m_uchrCurrentColumn = 0;
			m_uchrCurrentLine = 0;
		}
		else {
			m_uchrCurrentColumn = 0;
			m_uchrCurrentLine += 1;
		}
	}
	
	LcdGoToPosition(m_uchrCurrentLine, m_uchrCurrentColumn);
    
	
	
	LcdSendData(uchrChar);
	delayForMicroseconds(ushtDelayTime);
    
    m_uchrCurrentColumn+=1;
	
}



/**
* \brief Prints the passed character verbatim onto the LCD display at the position passed
* \param uchrChar The character to print
* \param uchrRow The row for the character to display at
* \param uchrColumn The column for the character to display at
*/
void LcdPrintCharAtPosition(char uchrChar, unsigned char uchrRow, unsigned char uchrColumn) 
{
	if(uchrColumn > LCD_COLUMN_COUNT-1) {
		if(uchrRow > LCD_ROW_COUNT-1) {
			LcdSendCommand(LCD_CLEAR_SCREEN);
			m_uchrCurrentColumn = 0;
			m_uchrCurrentLine = 0;
		}
		else {
			m_uchrCurrentColumn = 0;
			m_uchrCurrentLine += 1;
		}
	}

    
    LcdGoToPosition(uchrRow, uchrColumn);
	
	LcdSendData(uchrChar);
    
    m_uchrCurrentColumn+=1;
}



/**
* \brief Prints the passed character verbatim onto the LCD display at the position passed and delays for the amount of microseconds passed
* \param uchrChar The character to print
* \param uchrRow The row for the character to display at
* \param uchrColumn The column for the character to display at
* \param ushtDelayTime The amount of microseconds to delay for
*/
void LcdPrintCharDelayAtPosition(char uchrChar, unsigned char uchrRow, unsigned char uchrColumn, unsigned short ushtDelayTime) 
{
	if(uchrColumn > LCD_COLUMN_COUNT-1) {
		if(uchrRow > LCD_ROW_COUNT-1) {
			LcdSendCommand(LCD_CLEAR_SCREEN);
			m_uchrCurrentColumn = 0;
			m_uchrCurrentLine = 0;
		}
		else {
			m_uchrCurrentColumn = 0;
			m_uchrCurrentLine += 1;
		}
	}
	LcdGoToPosition(uchrRow, uchrColumn);
	
	LcdSendData(uchrChar);
    
    m_uchrCurrentColumn+=1;
    
	delayForMicroseconds(ushtDelayTime);
}



/**
* \brief Prints a string verbatim onto the display
* \param strToSend The string to send
*/
void LcdPrintString(char* strToSend) 
{
	unsigned char currentByte = 0;

	while(*strToSend)
	{	
		currentByte = (*strToSend++);
        
        
		LcdPrintChar(currentByte);
	}
}



/**
* \brief Prints a string verbatim onto the display and delays for the amount of microseconds passed
* \param strToSend The string to send
* \param ushtDelayTime The amount of microseconds to delay for in between each char
*/
void LcdPrintStringDelay(char* strToSend, unsigned short ushtDelayTime) 
{
	unsigned char currentByte = 0;

	while(*strToSend)
	{
		currentByte = (*strToSend++);
		LcdPrintCharDelay(currentByte, ushtDelayTime);
	}
}



/**
* \brief Prints a string verbatim onto the display at the position passed
* \param strToSend The string to send
* \param uchrRow The row to print at
* 
*/
void LcdPrintStringAtPosition(char* strToSend, unsigned char uchrRow, unsigned char uchrColumn) 
{
	unsigned char currentByte = 0;

	LcdGoToPosition(uchrRow, uchrColumn);

	while(*strToSend)
	{
		currentByte = (*strToSend++);
		LcdPrintChar(currentByte);
	}
}



/**
* \brief Prints a string verbatim onto the display at the position passed and delays for the amount of microseconds passed
* \param strToSend The string to send
* \param strToSend The string to send
* \param uchrRow The row to print at
* \param ushtDelayTime The amount of microseconds to delay for in between each char
*/
void LcdPrintStringDelayAtPosition(char* strToSend, unsigned char uchrRow, unsigned char uchrColumn, unsigned short ushtDelayTime) 
{
	unsigned char currentByte = 0;

	LcdGoToPosition(uchrRow, uchrColumn);

	while(*strToSend)
	{
		currentByte = (*strToSend++);
		LcdPrintCharDelay(currentByte, ushtDelayTime);
	}
}



/**
* \brief Sends a string to the LCD, performs any command characters passed and displays the printable characters passed
* \param strToSend The string to send
*/
void LcdPrint(char* strToSend) 
{
	unsigned char currentByte = 0;
	while(*strToSend)
	{
		currentByte = (*strToSend++);
		LcdSendByte(currentByte);
	}
}



/**
* \brief Sends a string to the LCD, performs any command characters passed and displays the printable characters passed and delays for the amount of microseconds passed
* \param strToSend The string to send
* \param ushtDelayTime The amount of microseconds to delay for in between each char
*/
void LcdPrintDelay(char* strToSend, unsigned short ushtDelayTime) 
{
	unsigned char currentByte = 0;

	while(*strToSend)
	{
		currentByte = (*strToSend++);
		LcdSendByteDelay(currentByte, ushtDelayTime);
	}
}



/**
* \brief Sends a string to the LCD, performs any command characters passed and displays the printable characters passed at the position passed
* \param strToSend The string to send
* \param uchrRow The row to print at
* \param uchrColumn The column to print at
*/
void LcdPrintAtPosition(char* strToSend, unsigned char uchrRow, unsigned char uchrColumn) 
{
	unsigned char currentByte = 0;
	
	LcdGoToPosition(uchrRow, uchrColumn);

	while(*strToSend)
	{
		currentByte = (*strToSend++);
		LcdSendByte(currentByte);
	}
}



/**
* \brief Sends a string to the LCD, performs any command characters passed and displays the printable characters passed at the position passed and delays by the amount of microseconds passed.
* \param strToSend The string to send
* \param uchrRow The row to print at
* \param uchrColumn The column to print at
* \param ushtDelayTime The amount of microseconds to delay for in between each char
*/
void LcdPrintDelayAtPosition(char* strToSend, unsigned char uchrRow, unsigned char uchrColumn, unsigned short ushtDelayTime) 
{
	unsigned char currentByte = 0;
	LcdGoToPosition(uchrRow, uchrColumn);

	
	while(*strToSend)
	{
		currentByte = (*strToSend++);
		LcdSendByteDelay(currentByte, ushtDelayTime);
	}
}



/**
* \brief Prints the value onto the screen, numerically
* \param numVal The value to print numerically
*/
void LcdPrintNumericalByte(uint8_t numVal)
{
	//Variables
	uint8_t firstValue = (numVal / 100);
	uint8_t secondValue = ((numVal / 10) % 10);
	uint8_t thirdValue = ((numVal % 10));
	char strToPrint[3] = {"   "};
	//Form the characters
	if(firstValue > 0)
	{
		firstValue += (0x30);
		secondValue += (0x30);
		strToPrint[0] = (char)firstValue;
		strToPrint[1] = (char)secondValue;
	}
	else if (secondValue > 0)
	{
		secondValue += (0x30);
		strToPrint[1] = (char)secondValue;
	}
	
	//Always print the 3rd value, 0 or not
	thirdValue += 0x30;
	strToPrint[2] = (char)thirdValue;
	
	for(uint8_t i = 0; i < 3; i++)
	{
		LcdPrintChar(strToPrint[i]);	
	}
}



/**
* \brief Prints the value onto the screen, numerically
* \param numVal The value to print numerically
* \param ushtDelayTime The time delay in between characters printed
*/
void LcdPrintNumericalByteDelay(uint8_t numVal, unsigned short ushtDelayTime)
{
	//Variables
	uint8_t firstValue = (numVal / 100);
	uint8_t secondValue = ((numVal / 10) % 10);
	uint8_t thirdValue = ((numVal % 10));
	char strToPrint[3] = {"   "};
	//Form the characters
	if(firstValue > 0)
	{
		firstValue += (0x30);
		secondValue += (0x30);
		strToPrint[0] = (char)firstValue;
		strToPrint[1] = (char)secondValue;
	}
	else if (secondValue > 0)
	{
		secondValue += (0x30);
		strToPrint[1] = (char)secondValue;
	}
	
	//Always print the 3rd value, 0 or not
	thirdValue += 0x30;
	strToPrint[2] = (char)thirdValue;
	
	
	for(uint8_t i = 0; i < 3; i++)
	{
		LcdPrintCharDelay(strToPrint[i],ushtDelayTime);	
	}
}



/**
* \brief Prints the value onto the screen, numerically
* \param numVal The value to print numerically
* \param uchrRow The row to print at
* \param uchrColumn The column to print at
*/
void LcdPrintNumericalByteAtPosition(uint8_t numVal, unsigned char uchrRow, unsigned char uchrColumn)
{
	//Variables
	uint8_t firstValue = (numVal / 100);
	uint8_t secondValue = ((numVal / 10) % 10);
	uint8_t thirdValue = ((numVal % 10));
	char strToPrint[3] = {"   "};
	//Form the characters
	if(firstValue > 0)
	{
		firstValue += (0x30);
		secondValue += (0x30);
		strToPrint[0] = (char)firstValue;
		strToPrint[1] = (char)secondValue;
	}
	else if (secondValue > 0)
	{
		secondValue += (0x30);
		strToPrint[1] = (char)secondValue;
	}
	
	//Always print the 3rd value, 0 or not
	thirdValue += 0x30;
	strToPrint[2] = (char)thirdValue;
	
	LcdGoToPosition(uchrRow, uchrColumn);
	
	for(uint8_t i = 0; i < 3; i++)
	{
		LcdPrintChar(strToPrint[i]);	
	}
}



/**
* \brief Prints the value onto the screen, numerically
* \param numVal The value to print numerically
* \param uchrRow The row to print at
* \param uchrColumn The column to print at
* \param ushtDelayTime The time delay in between characters printed
*/
void LcdPrintNumericalByteDelayAtPosition(uint8_t numVal, unsigned char uchrRow, unsigned char uchrColumn, unsigned short ushtDelayTime)
{
	//Variables
	uint8_t firstValue = (numVal / 100);
	uint8_t secondValue = ((numVal / 10) % 10);
	uint8_t thirdValue = ((numVal % 10));
	char strToPrint[3] = {"   "};
	//Form the characters
	if(firstValue > 0)
	{
		firstValue += (0x30);
		secondValue += (0x30);
		strToPrint[0] = (char)firstValue;
		strToPrint[1] = (char)secondValue;
	}
	else if (secondValue > 0)
	{
		secondValue += (0x30);
		strToPrint[1] = (char)secondValue;
	}
	
	//Always print the 3rd value, 0 or not
	thirdValue += 0x30;
	strToPrint[2] = (char)thirdValue;
	
	LcdGoToPosition(uchrRow, uchrColumn);
	
	for(uint8_t i = 0; i < 3; i++)
	{
		LcdPrintCharDelay(strToPrint[i],ushtDelayTime);	
	}
}



/**
* \brief Prints the value onto the screen, numerically
* \param numVal The value to print numerically
*/
void LcdPrintNumericalShort(uint16_t numVal)
{
	//Variables
	uint8_t firstValue =  (numVal / 10000);
	uint8_t secondValue = ((numVal / 1000) % 10);
	uint8_t thirdValue =  ((numVal % 1000)/100);
	uint8_t fourthValue = ((numVal % 100) / 10);
	uint8_t fifthValue =  ((numVal % 10));
	
	char strToPrint[5] = {"     "};
		
	//Form the characters
	if(firstValue > 0)
	{
		firstValue += (0x30);
		secondValue += (0x30);
		thirdValue += 0x30;
		fourthValue += 0x30;
		strToPrint[0] = (char)firstValue;
		strToPrint[1] = (char)secondValue;
		strToPrint[2] = (char)thirdValue;
		strToPrint[3] = (char)fourthValue;
	}
	else if (secondValue > 0)
	{
		secondValue += (0x30);
		thirdValue += 0x30;
		fourthValue += 0x30;
		strToPrint[1] = (char)secondValue;
		strToPrint[2] = (char)thirdValue;
		strToPrint[3] = (char)fourthValue;
	}
	else if (thirdValue > 0)
	{
		thirdValue += 0x30;
		fourthValue += 0x30;
		strToPrint[2] = (char)thirdValue;
		strToPrint[3] = (char)fourthValue;
	}
	else if(fourthValue > 0)
	{
		fourthValue += 0x30;
		strToPrint[3] = (char)fourthValue;
	}
	
	//Always print the last value, 0 or not
	fifthValue += 0x30;
	strToPrint[4] = (char)fifthValue;
	
	

	for(uint8_t i = 0; i < 5; i++)
	{
		LcdPrintChar(strToPrint[i]);	
	}
}



/**
* \brief Prints the value onto the screen, numerically
* \param numVal The value to print numerically
* \param ushtDelayTime The time delay in between characters printed
*/
void LcdPrintNumericalShortDelay(uint16_t numVal, unsigned short ushtDelayTime)
{

	//Variables
	uint8_t firstValue =  (numVal / 10000);
	uint8_t secondValue = ((numVal / 1000) % 10);
	uint8_t thirdValue =  ((numVal % 1000)/100);
	uint8_t fourthValue = ((numVal % 100) / 10);
	uint8_t fifthValue =  ((numVal % 10));
	
	char strToPrint[5] = {"     "};
	
	//Form the characters
	if(firstValue > 0)
	{
		firstValue += (0x30);
		secondValue += (0x30);
		thirdValue += 0x30;
		fourthValue += 0x30;
		strToPrint[0] = (char)firstValue;
		strToPrint[1] = (char)secondValue;
		strToPrint[2] = (char)thirdValue;
		strToPrint[3] = (char)fourthValue;
	}
	else if (secondValue > 0)
	{
		secondValue += (0x30);
		thirdValue += 0x30;
		fourthValue += 0x30;
		strToPrint[1] = (char)secondValue;
		strToPrint[2] = (char)thirdValue;
		strToPrint[3] = (char)fourthValue;
	}
	else if (thirdValue > 0)
	{
		thirdValue += 0x30;
		fourthValue += 0x30;
		strToPrint[2] = (char)thirdValue;
		strToPrint[3] = (char)fourthValue;
	}
	else if(fourthValue > 0)
	{
		fourthValue += 0x30;
		strToPrint[3] = (char)fourthValue;
	}
	
	//Always print the last value, 0 or not
	fifthValue += 0x30;
	strToPrint[4] = (char)fifthValue;
	
	

	for(uint8_t i = 0; i < 5; i++)
	{
		LcdPrintCharDelay(strToPrint[i],ushtDelayTime);	
	}
}



/**
* \brief Prints the value onto the screen, numerically
* \param numVal The value to print numerically
* \param uchrRow The row to print at
* \param uchrColumn The column to print at
*/
void LcdPrintNumericalShortAtPosition(uint16_t numVal, unsigned char uchrRow, unsigned char uchrColumn)
{
	//Variables
	uint8_t firstValue =  (numVal / 10000);
	uint8_t secondValue = ((numVal / 1000) % 10);
	uint8_t thirdValue =  ((numVal % 1000)/100);
	uint8_t fourthValue = ((numVal % 100) / 10);
	uint8_t fifthValue =  ((numVal % 10));
	
	char strToPrint[5] = {"     "};
	
	//Form the characters
	if(firstValue > 0)
	{
		firstValue += (0x30);
		secondValue += (0x30);
		thirdValue += 0x30;
		fourthValue += 0x30;
		strToPrint[0] = (char)firstValue;
		strToPrint[1] = (char)secondValue;
		strToPrint[2] = (char)thirdValue;
		strToPrint[3] = (char)fourthValue;
	}
	else if (secondValue > 0)
	{
		secondValue += (0x30);
		thirdValue += 0x30;
		fourthValue += 0x30;
		strToPrint[1] = (char)secondValue;
		strToPrint[2] = (char)thirdValue;
		strToPrint[3] = (char)fourthValue;
	}
	else if (thirdValue > 0)
	{
		thirdValue += 0x30;
		fourthValue += 0x30;
		strToPrint[2] = (char)thirdValue;
		strToPrint[3] = (char)fourthValue;
	}
	else if(fourthValue > 0)
	{
		fourthValue += 0x30;
		strToPrint[3] = (char)fourthValue;
	}
	
	//Always print the last value, 0 or not
	fifthValue += 0x30;
	strToPrint[4] = (char)fifthValue;
	
	
	LcdGoToPosition(uchrRow, uchrColumn);
	
	for(uint8_t i = 0; i < 5; i++)
	{
		LcdPrintChar(strToPrint[i]);	
	}
}



/**
* \brief Prints the value onto the screen, numerically
* \param numVal The value to print numerically
* \param uchrRow The row to print at
* \param uchrColumn The column to print at
* \param ushtDelayTime The time delay in between characters printed
*/
void LcdPrintNumericalShortDelayAtPosition(uint16_t numVal, unsigned char uchrRow, unsigned char uchrColumn, unsigned short ushtDelayTime)
{
	//Variables
	uint8_t firstValue =  (numVal / 10000);
	uint8_t secondValue = ((numVal / 1000) % 10);
	uint8_t thirdValue =  ((numVal % 1000)/100);
	uint8_t fourthValue = ((numVal % 100) / 10);
	uint8_t fifthValue =  ((numVal % 10));
	
	char strToPrint[5] = {"     "};
	
	//Form the characters
	if(firstValue > 0)
	{
		firstValue += (0x30);
		secondValue += (0x30);
		thirdValue += 0x30;
		fourthValue += 0x30;
		strToPrint[0] = (char)firstValue;
		strToPrint[1] = (char)secondValue;
		strToPrint[2] = (char)thirdValue;
		strToPrint[3] = (char)fourthValue;
	}
	else if (secondValue > 0)
	{
		secondValue += (0x30);
		thirdValue += 0x30;
		fourthValue += 0x30;
		strToPrint[1] = (char)secondValue;
		strToPrint[2] = (char)thirdValue;
		strToPrint[3] = (char)fourthValue;
	}
	else if (thirdValue > 0)
	{
		thirdValue += 0x30;
		fourthValue += 0x30;
		strToPrint[2] = (char)thirdValue;
		strToPrint[3] = (char)fourthValue;
	}
	else if(fourthValue > 0)
	{
		fourthValue += 0x30;
		strToPrint[3] = (char)fourthValue;
	}
	
	//Always print the last value, 0 or not
	fifthValue += 0x30;
	strToPrint[4] = (char)fifthValue;
	
	LcdGoToPosition(uchrRow, uchrColumn);
	
	for(uint8_t i = 0; i < 5; i++)
	{
		LcdPrintCharDelay(strToPrint[i],ushtDelayTime);	
	}
	
}



/**
* \brief Displays the passed byte value as a hexadecimal string
* \param The byte value to convert to hexadecimal string
*/
void LcdDisplayByteHex(uint8_t byteValue)
{
	//variables
	char displayString[4] = "0x00";
	displayString[2] += (char)((byteValue & 0xF0) >> 4);
	displayString[3] += (char)(byteValue & 0x0F);
	LcdPrintString(displayString);
}



/**
* \brief Displays the binary of the byte value passed
* \param byteValue The value to display as binary
*/
void LcdDisplayByteBinary(uint8_t byteValue)
{
	for(uint8_t i = 0, j = 0; i < 9; i++)
	{
		if(i == 4)
		{
			LcdPrintChar(' ');
		}
		else
		{
			LcdPrintChar(readBit(byteValue,j)+0x30);
			j++;
		}
	}
	
}



#endif