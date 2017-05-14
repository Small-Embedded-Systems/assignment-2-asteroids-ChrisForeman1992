/* Game state */

extern float elapsed_time; /* time this ship has been active */
extern int score;        /* total score so far */
extern int lives;        /* lives remaining */
extern int shield; 				 /* shield remaining */

extern double shipCentX, shipCentY, shipFrontX, shipFrontY, shipLeftX, shipLeftY, shipRightX, shipRightY; 	/* properties of ship*/

extern struct ship player;


extern const float Dt; /* Time step for physics, needed for consistent motion */


extern struct asteroid_t *asteroids; /* array of asteroids / pointer to linked-list */
extern struct missile_t *missiles;  /* array of missiles / pointer to linked-list */

extern int asteroidCount; 
extern int missileCount;
extern int frames;
extern bool paused;
