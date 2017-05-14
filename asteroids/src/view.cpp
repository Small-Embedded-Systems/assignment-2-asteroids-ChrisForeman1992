/* Asteroids view*/
/* C libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
/* hardware platform libraries */
#include <display.h>
#include <mbed.h>
/* Main game elements */
#include "asteroids.h"
#include "model.h"
#include "utils.h"
#include "controller.h"
#include "objects.h"

Display *graphics = Display::theDisplay();
const colour_t background = rgb(0, 0, 0); /* Black background */

/* Double buffering functions */
void init_DBuffer(void){  
	 /* Initialise the LCD driver to use second frame in buffer */
    uint16_t *bufferbase = graphics->getFb();
    uint16_t *nextbuffer = bufferbase+ (480*272);
    LPC_LCD->UPBASE = (uint32_t)nextbuffer;
}
/* Swaps frames used by the LCD driver and the graphics object */
void swap_DBuffer(void){   
    uint16_t *buffer = graphics->getFb();
    graphics->setFb( (uint16_t*) LPC_LCD->UPBASE);
    LPC_LCD->UPBASE = (uint32_t)buffer;
}

/* Fills the screen with background and prints all UI information relating to game state*/
void drawUI() {
	graphics->fillScreen(background);
	graphics->setTextColor(WHITE);
	graphics->setCursor(260,2);
	graphics->printf("Score: %i" , score);
	graphics->setCursor(110,2);
	graphics->printf("SHIELD: %i" , shield);
	graphics->setCursor(2,2);
	graphics->printf("Lives: %i" , lives);	

}

/* Fills background over game elements and displays game over message, score and prompts player to restart*/
void gameOver(void){
	swap_DBuffer();
	graphics->fillScreen(background);
	graphics->setTextSize(3);
	graphics->setCursor(160, 56);
	graphics->printf("GAME OVER!");
	graphics->setCursor(160, 126);
	graphics->printf("SCORE: %i", score);
	graphics->setCursor(90, 196);
	graphics->printf("CENTER TO RESTART");
	graphics->setTextSize(1);
	init_DBuffer();
}

/* Draws the various lines that make up the ship, this is coloured green*/
void drawShip() {
	graphics->drawLine(shipFrontX, shipFrontY, shipRightX, shipRightY, GREEN);
	graphics->drawLine(shipRightX, shipRightY, shipCentX, shipCentY, GREEN);
	graphics->drawLine(shipLeftX, shipLeftY, shipCentX, shipCentY, GREEN);
	graphics->drawLine(shipLeftX, shipLeftY, shipFrontX, shipFrontY, GREEN);
}

/* Draws the asteroid Bitmap image */
void drawAsteroids(asteroid_t *head) {
	asteroid_t* current = head;
	while (current != NULL) {
		graphics->drawBitmap(current->p.x, current->p.y, asteroidBits, 16,16, WHITE);
		current = current->next;
  }
}

/* Draws the missile Bitmap image */
void drawMissiles(missile_t *head) {
	missile_t* current = head;
	while (current != NULL) {
		graphics->drawBitmap(current->p.x,current->p.y ,missileBits, 2, 2, WHITE);
		current = current->next;
  }
}

/* Increments the score based on the ticker every time draw() is called*/
void incrementScore() {
	score++;
}

/* Calls frequently used view functions - drawing UI, ship, asteroids, missiles and increments score and swaps DBuffer*/
void draw(void){
	drawUI();
	drawShip();
	drawAsteroids(asteroids);   
	drawMissiles(missiles);
	incrementScore();
	swap_DBuffer();
}
