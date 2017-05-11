/* Asteroids model */
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "model.h"
#include "utils.h"
#include "asteroids.h"
#include "controller.h"


/* If you want to initialise a linked list:
    You'll have to replace node_t with the right type

typedef struct node {
    some data per node
    struct node *next;
} node_t;
const size_t MAXSize = 10;
node_t data[MAXSize];
node_t *initialise()
{
    int c;
    for(c=0 ; c<(MAXSize-1) ; c++){
        data[c].next = &data[c+1];
    }
    data[c].next = NULL;
    return data;
}
*/

double sFrontX, sFrontY, sLeftX, sLeftY, sRightX, sRightY;
int length = 20;
float angle = 0.0;
float veloX, veloY;
float angleChange = 0.05;
int shieldState = 2;


void shipThrust() {
	veloX = (10 * cos(angle));
	veloY = (10 * sin(angle));
	
	if (joystickUp == true) {
		shipCentX += (veloX /20);
		shipCentY += (veloY /20);
	}		
}

void shipTurn() {
	sFrontX = length * cos (angle);
	sFrontY = length * sin (angle);
	sLeftX = length * cos (3.83972); /// change these tings
	sLeftY = length * sin (3.83972);
	sRightX = length * cos (2.44346);
	sRightY = length * sin (2.44346);
	
	shipFrontX = sFrontX + shipCentX;
	shipFrontY = sFrontY + shipCentY;
	shipLeftX = sLeftX + shipLeftX;
	shipLeftY = sLeftY + shipLeftY; 
	shipRightX = sRightX + shipRightX;
	shipRightY = sRightY + shipRightY;
	
	if (angle > (2 * pi)) {
		angle = (2* pi) - 0.1;
	}	
	if (joystickLeft == true) {
		angle += angleChange; 
	}
	if (joystickRight == true) {
		angle -= angleChange;
	}
	if (joystickDown == true) {
		joystickLeft = false; 
		joystickRight = false;
		joystickUp = false;
		joystickDown = false; 
	}
	
}

void shipWrap() {
	if (shipCentY - 15 > 272) {
		shipCentY = 25;
	}
	if (shipCentX - 7 > 487) {
		shipCentX = 8;
	}
	if (shipCentY + 10 < 19) {
		shipCentY = 285;
	}
	if (shipCentX + 7 < 0) {
		shipCentX = 486;
	}	
}

void shipShield() {
	if ((shieldState = >0) && (asteroidX == shipCentX && asteroidY == shipCentY) ) {
		shieldState--;
	} else if ((shieldState ==0) && (asteroidX == shipCentX && asteroidY == shipCentY)) {
		lives--;
	} shieldState = 2;
}	


	
void physics(void){
	shipShield();
	shipThrust();
	shipWrap();
		   
}

