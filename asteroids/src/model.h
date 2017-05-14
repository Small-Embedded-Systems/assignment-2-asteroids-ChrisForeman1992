/* Asteroids Model */
struct point {
    float x,y;
};
typedef struct point coordinate_t;
typedef struct point vector_t;

/* Some insitial struct types if you want to usd them */
struct ship {
    coordinate_t p;
    vector_t     v;
};

typedef struct asteroid_t {
		coordinate_t p;
		vector_t v;
    struct asteroid_t* next;
} asteroid_t;

typedef struct missile_t {
    coordinate_t p;
		vector_t v;
		int age;
    struct missile_t* next;
} missile_t;



void newMissile(missile_t *head);
void newRock(asteroid_t *head);

void physics(void);
