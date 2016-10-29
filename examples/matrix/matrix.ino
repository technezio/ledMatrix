#include <ledMatrix.h>

ledMatrix myMatrix(2, 3, 4);    // Data, Latch, Clock

void setup()
{
  myMatrix.setBrightness(10);   // LEDs brightness from 0 to 15
  
  myMatrix.flush();             // Turn off all LEDs

  myMatrix.dot(2,5);        	// First decide which LEDs to turn on
  myMatrix.dot(1,8);
  myMatrix.dot(4,4);
  myMatrix.dot(6,7);
  myMatrix.load();          	// Turn on them all
}

void loop()
{
  
}

