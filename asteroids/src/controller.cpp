/* Controller */

/* C libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>


/* hardware platform libraries */
#include <mbed.h>

/* asteroids */
#include "model.h"
#include "asteroids.h"
#include <display.h>

/* Joystick 5-way switch
*/
typedef enum {JLT = 0, JRT, JUP, JDN, JCR} btnId_t;
static DigitalIn jsBtns[] = {P5_0, P5_4, P5_2, P5_1, P5_3}; // LFT, RGHT, UP, DWN, CTR
bool jsPrsdAndRlsd(btnId_t b);
bool joystickLeft;
bool joystickRight;
bool joystickUp;
bool joystickDown;
bool joystickCenter;
Display *graphics = Display::theDisplay();


void controls(void){
	
	if (jsPrsdAndRlsd(JLT)) {
		joystickRight = false; 
		joystickLeft = true; 
		graphics->setCursor(150,150);
		graphics->printf("LEFT PRESSED");
	}
	if (jsPrsdAndRlsd(JRT)) {
		joystickLeft = false; 
		joystickRight = true; 
		graphics->setCursor(150,170);
		graphics->printf("RIGHT PRESSED");
	}	
	if (jsPrsdAndRlsd(JUP)) {
		joystickDown = false; 
		joystickUp = true; 
		graphics->setCursor(150,190);
		graphics->printf("UP PRESSED");
	}	
 	if (jsPrsdAndRlsd(JDN)) {
		joystickUp = false; 
		joystickDown = true; 
		graphics->setCursor(150,210);
		graphics->printf("DOWN PRESSED");		
	}
	if (jsPrsdAndRlsd(JCR)) {
		joystickCenter = true; 
		graphics->setCursor(150,230);
		graphics->printf("CENTER PRESSED");		
	}	
}


bool jsPrsdAndRlsd(btnId_t b) {
bool result = false;
uint32_t state;
static uint32_t savedState[4] = {1,1,1,1};
        //initially all 1s: nothing pressed
state = jsBtns[b].read();
  if ((savedState[b] == 0) && (state == 1)) {
result = true;
}
savedState[b] = state;
return result;
}
