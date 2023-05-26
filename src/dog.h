#ifndef DOG_H
#define DOG_H

#include <tice.h>
#include <graphx.h>

enum DogMode
{
	DOG_HIDDEN = 0,
	DOG_RUN_TO_CENTER = 1,
	DOG_PEEK_UP = 2
};

struct dog_t
{
	// dog position
	int x;
	int y;

	// used for movement animations
	int gotoX;
	int gotoY;

	// speed of movement
	int speed;

	// animation mode
	int mode;

	// costume number
	int cnum;

	// tick
	int tick;

	// animation timer
	int animate;
};
extern struct dog_t dog;

// sets dog mode.
void dog_SetMode(uint8_t mode);

// renders dog mode
void dog_Render(void);

// updates render
void dog_Update(void);

// draws dog walking to the center.
void draw_dog_scene(void);

#endif