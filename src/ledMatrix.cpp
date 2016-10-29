#include "ledMatrix.h"

// Constructor
ledMatrix::ledMatrix(byte data, byte latch, byte clock)
{
	dataPin = data;
	latchPin = latch;
	clockPin = clock;
	
	pinMode(dataPin, OUTPUT);
	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	
	// Initiation of the MAX7219
	writeReg(REG_SCANLIMIT, 0x07);
	writeReg(REG_SHUTDOWN, 0x01);   	// not in shutdown mode
	writeReg(REG_INTENSITY, 0x07);		// brightness from 0x00 to 0x0F
	writeReg(REG_DISPLAYTEST, 0x00);	// test mode off
	writeReg(REG_DECODEMODE, 0x00);		// using an LED matrix (no decode)
	flush();
}

// LOW LEVEL - Put a byte in a register
void ledMatrix::writeReg(byte reg, byte data)
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, reg); 		// specify which register..
  shiftOut(dataPin, clockPin, MSBFIRST, data);		// ..to put data in
  digitalWrite(latchPin,HIGH); 
}

/* HIGH LEVEL */
void ledMatrix::flush()
{
	for (byte k = 1; k <= 8; k++) { 	
		writeReg(k, 0);			// empty registers (1 to 8)
		status[k-1] = 0;		// empty status matrix (0 to 7)
	}
}

void ledMatrix::dot(byte row, byte col)
{
	// Check if proper values
	if (!(row < 1 || row > 8 || col < 1 || col > 8))
	{
		status[row-1] |= (1 << (col-1));
	}
}

void ledMatrix::load()
{
	for(byte reg = 0; reg < 8; reg++)
	{
		/*byte val = 0;
		for(byte row = 0; row < 8; row++)
		{
			if (status[reg][row])	// If present
				val |= (1 << row);	// set the corrisponding bit to 1
		}*/
		writeReg(reg+1, status[reg]);
	}
}

void ledMatrix::setBrightness(byte value)
{
	// Check if proper values
	if(value >= 0 && value <= 15)
		writeReg(REG_INTENSITY, value);
}
