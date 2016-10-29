/* Code for max7219 from maxim, adapted from the previous version
 * to control one LED matrix. 
 * Chip info at http://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf
______________________________________

 Code History:
 --------------

The orginal code was written for the Wiring board by:
 * Nicholas Zambetti and Dave Mellis /Interaction Design Institute Ivrea /Dec 2004
 * http://www.potemkin.org/uploads/Wiring/MAX7219.txt

First modification by:
 * Marcus Hannerstig/  K3, malmï¿½ hï¿½gskola /2006
 * http://www.xlab.se | http://arduino.berlios.de

The previous version is by:
 * tomek ness /FH-Potsdam / Feb 2007
 * http://design.fh-potsdam.de/ 

 * @acknowledgements: eric f. 

This code is by:
 * Luca Mattii / Apr 2014
 * https://www.glgprograms.it

 --------------

*/

#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include <Arduino.h>

// define max7219 registers
#define REG_NOOP        0x00
#define REG_DECODEMODE  0x09
#define REG_INTENSITY   0x0A
#define REG_SCANLIMIT   0x0B
#define REG_SHUTDOWN    0x0C
#define REG_DISPLAYTEST 0x0F

class ledMatrix {
  byte dataPin;
  byte latchPin;
  byte clockPin;
  byte status[8];		// status of the 64 LEDs: status[i] is the i-th row
  
public:
  ledMatrix(byte data, byte latch, byte clock);	// Constructor
  void writeReg(byte reg, byte data);			// Write data into the chip register reg
  void dot(byte row, byte col);					// Turn on the specified LED
  void load();									// Load status matrix into the chip registers
  void flush();									// Set to 0 the LEDs registers and status matrix
  void setBrightness(byte value);				// Set LEDs brightness (0-15)
};

#endif
