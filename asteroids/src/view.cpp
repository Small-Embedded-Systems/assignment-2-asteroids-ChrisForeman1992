/* Asteroids view
*/

/* C libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

/* hardware platform libraries */
#include <display.h>
#include <mbed.h>

#include "asteroids.h"
#include "model.h"
#include "utils.h"
#include "objects.h"

Display *graphics = Display::theDisplay();

const colour_t background = rgb(0,51,102); /* Midnight Blue */


/*const coordinate_t shape[] = {
    {10,0}, {-5,5}, {-5,-5}
}; */

/* double buffering functions */
void init_DBuffer(void)
{   /* initialise the LCD driver to use second frame in buffer */
    uint16_t *bufferbase = graphics->getFb();
    uint16_t *nextbuffer = bufferbase+ (480*272);
    LPC_LCD->UPBASE = (uint32_t)nextbuffer;
}

void swap_DBuffer(void)
{   /* swaps frames used by the LCD driver and the graphics object */
    uint16_t *buffer = graphics->getFb();
    graphics->setFb( (uint16_t*) LPC_LCD->UPBASE);
    LPC_LCD->UPBASE = (uint32_t)buffer;
}

void drawInfo() {
	graphics->setTextColor(YELLOW);
	graphics->setCursor(400,2);
	graphics->printf("Score ");
	graphics->setCursor(210,2);
	graphics->printf("ASTEROIDS");
	graphics->setCursor(2,2);
	graphics->printf("ye");
	for (int i=1; i<=lives; i++){
	graphics->fillTriangle(i*20 ,10, (i*20)-5, 25, (i*20)+5, 25, YELLOW);
	}


}


void drawShip() {
	graphics->drawLine(shipFrontX, shipFrontY, shipRightX, shipRightY, BLUE);
	graphics->drawLine(shipRightX, shipRightY, shipCentX, shipCentY, RED);
	graphics->drawLine(shipLeftX, shipLeftY, shipCentX, shipCentY, MAGENTA);
	graphics->drawLine(shipLeftX, shipLeftY, shipFrontX, shipFrontY, YELLOW);
}




void draw(void)
{
		
    graphics->fillScreen(background);
		drawInfo();
    drawShip();
    swap_DBuffer();
}
