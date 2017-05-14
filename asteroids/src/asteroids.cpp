/* Asteroids	
	 Semester 2 -- Small Embedded Systems	
	 Christopher Foreman */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
/* hardware platform libraries */
#include <display.h>
#include <mbed.h>
/* Main game elements */
#include "model.h"
#include "view.h"
#include "controller.h"
#include "utils.h"

/* Game state variables*/
float elapsed_time; 
int score =0;
int lives =3;
int shield =2;
struct ship player;
int frames;
int asteroidCount;
int missileCount;
asteroid_t * asteroids;
missile_t * missiles;

/* Ship properties */
double shipCentX = 200;
double shipCentY = 100;
double shipFrontX = shipCentX;
double shipFrontY = shipCentY - 6;
double shipLeftX = shipCentX - 4;
double shipLeftY = shipCentY + 4;
double shipRightX = shipCentX + 4;
double shipRightY = shipCentY + 4;

/* Tickers */
float Dt = 0.01f;
Ticker model, view, controller;

/* Initialises asteroid and missile linked lists*/
void initialise() {
		asteroids = static_cast<asteroid_t*>(malloc(sizeof(asteroid_t)));
		asteroids->next = NULL;	
		missiles = static_cast<missile_t*>(malloc(sizeof(missile_t)));
		missiles->next = NULL;
}
/* Calls initialiser for linked list, buffer and attaches required tickers*/
int main() {
		initialise();
    init_DBuffer();
		view.attach(draw, 0.05);
    model.attach(physics, Dt);
    controller.attach( controls, 0.1); 
/* Causes the game to display a game over screen when lives reach 0, from this the player can choose to restart*/
		while(true) {
		if(lives == 0){
			model.detach();
			view.detach();
			controller.detach();
			gameOver();
/*Resets game variables and redraws elements when game is restarted from the game over screen */			
			if(restartGame()) {
				score = 0;
				lives = 3;
				shield = 2;
				view.attach(draw, 0.05);
				model.attach(physics, Dt);
				controller.attach(controls, 0.1);		
				draw();
			}
		}
	}    
}
