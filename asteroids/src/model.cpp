/* Asteroids model */
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
/* Main game elements */
#include "model.h"
#include "utils.h"
#include "asteroids.h"
#include "controller.h"
#include "objects.h"
/* Variables relating to the game physics*/
double sFrontX, sFrontY, sLeftX, sLeftY, sRightX, sRightY;
int length = 15;
float angle = 0.0;
float veloX, veloY;
float angleChange = 0.025;
float PI = 3.14159; 

/* Causes the ship to move forward relative to the angle it is facing on joystick input*/
void shipThrust() {
	veloX = (10 * cos(angle));
	veloY = (10 * sin(angle));
	
	if (joystickUp == true) {
		shipCentX += (veloX /20);
		shipCentY += (veloY /20);
	}		
} 

/* Causes the ship to rotate, straighten out and stop based on joystick input */ 
void shipTurn() {
	sFrontX = length * cos (angle);
	sFrontY = length * sin (angle);
	sLeftX = length * cos (angle + 3.83972); 
	sLeftY = length * sin (angle + 3.83972);
	sRightX = length * cos (angle + 2.44346);
	sRightY = length * sin (angle + 2.44346);
	
	shipFrontX = sFrontX + shipCentX;
	shipFrontY = sFrontY + shipCentY;
	shipLeftX = sLeftX + shipCentX;
	shipLeftY = sLeftY + shipCentY; 	
	shipRightX = sRightX + shipCentX;
	shipRightY = sRightY + shipCentY;
	
	if (angle > 2 * PI) {
		angle = 0.1;
	}	
	if (angle < 0) {
		angle = (2* PI) - 0.1;		
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

/* Causes ship to wrap around to other side of playing area when it goes out of bounds */
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
/* Keeps spawning new asteroids from the linked list as long as conditions are met*/
void newAsteroid(asteroid_t* head) {
	if(frames % 150 == 0 && asteroidCount < 8) {
    asteroid_t* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = (asteroid_t*)malloc(sizeof(asteroid_t));
    current->next->p.x = randrange(16, 465); current->next->p.y =  randrange(16, 257);
		current->next->v.x = randrange(-1, 2); current->next->v.y = randrange(-1, 2);
		if(current->next->v.x == 0 && current->next->v.y == 0)
			current->next->v.x = 1; current->next->v.y = 1;
		current->next->next = NULL;
		asteroidCount++;
	}
}

/* Manages movement of asteroids including wrapping around the screen, directional movement and deletion on collision*/
void updateAsteroids(asteroid_t* head) {
	asteroid_t* current = head;
		if(current != NULL) {
			current->p.x += current->v.x;current->p.y += current->v.y;
			if(current->p.x > 496) {
				current->p.x = -16;
			}
			if(current->p.x < -16) {
				current->p.x = 496;
			}
			if(current->p.y > 290) {
				current->p.y = -20;
			}
			if(current->p.y < -20) {
				current->p.y = 290;
			}
			if(current->p.x <= shipCentX && current->p.x >= shipCentX - 15 && current->p.y >= shipCentY - 15 && current->p.y <= shipCentY + 15 && (shield <=0)) {
				current->p.x = randrange(16, 465);current->p.y =  randrange(16, 257);
				lives--;		
				shield = 2;
			} else if(current->p.x <= shipCentX && current->p.x >= shipCentX - 15 && current->p.y >= shipCentY - 15 && current->p.y <= shipCentY + 15 && (shield >0)) {
				current->p.x = randrange(16, 465);current->p.y =  randrange(16, 257);
				shield--;				
			} 			
			current = current->next;
			updateAsteroids(current);
	}
}
 /* Creates a new missile front the front of the ship*/
void newMissile(missile_t* head) {
	missile_t* current = head;
	while (current->next != NULL) {
			current = current->next;
	}	
	current->next = (missile_t*)malloc(sizeof(missile_t));
	current->next->p.x = shipFrontX; current->next->p.y =  shipFrontY;
	current->next->v.x = veloX/1.5; current->next->v.y = veloY/1.5;
	current->next->age = frames;
	current->next->next = NULL;
	missileCount++;
}
/* Determines the movement of fired missile*/
void updateMissiles(missile_t* head) {
	missile_t *current = head;
	while(current != NULL) {
		current->p.x += current->v.x;current->p.y += current->v.y;
		current = current->next;
	}
} 

/* Calls frequently used physics-related functions*/
void physics(void){
	updateMissiles(missiles);
	shipThrust();
	shipTurn();
	shipWrap();
	newAsteroid(asteroids);	
	updateAsteroids(asteroids);
}

