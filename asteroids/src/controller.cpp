/* Controller */
/* C libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
/* hardware platform libraries */
#include <mbed.h>
/* Main game elements */
#include "model.h"
#include "asteroids.h"
#include "objects.h"

/* Joystick 5-way switch */
typedef enum {JLT = 0, JRT, JUP, JDN, JCR} btnId_t;
static DigitalIn jsBtns[] = {P5_0, P5_4, P5_2, P5_1, P5_3}; // LFT, RGHT, UP, DWN, CTR
bool jsPrsdAndRlsd(btnId_t b);
bool joystickLeft;
bool joystickRight;
bool joystickUp;
bool joystickDown;
bool joystickCenter;

/* User controls including game start, ship movement and rocket firing */
void controls(void){	
	if (jsPrsdAndRlsd(JLT)) {
		joystickRight = false; 
		joystickLeft = true; 
	} 	
	if (jsPrsdAndRlsd(JRT)) {
		joystickLeft = false; 
		joystickRight = true; 
	} 	
	if (jsPrsdAndRlsd(JUP)) {
	  joystickUp = true; 
		joystickDown = false; 
		joystickLeft = false; 
		joystickRight = false;
	} 	
 	if (jsPrsdAndRlsd(JDN)) {
		joystickUp = false; 
		joystickDown = true; 
		}	
	if (jsPrsdAndRlsd(JCR)) {		
		newMissile(missiles);
	}	
}

/* Causes the game to restart on user pressing center button when lives are equal to 0*/
	bool (restartGame(void)) {
		if (lives ==0 && jsPrsdAndRlsd(JCR)) {
			return true;
	}
			return false;
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
