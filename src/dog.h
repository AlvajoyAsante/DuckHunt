#ifndef DOG_H
#define DOG_H

#include <tice.h>
#include <graphx.h>

/* Dog modes */
enum DOG_ACTIONS
{
	DOG_HIDDEN = 0,
	DOG_RUN_TO_CENTER = 1,
	DOG_PEEK_UP = 2,
	DOG_LAUGH = 3
};

/* Dog infomation */
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

	gfx_sprite_t *back_buffer;
};
extern struct dog_t dog;

/**
 * @brief Render the dog animation =
 *
 */
void dog_Render(void);

/**
 * @brief Update the dog animation
 *
 */
void dog_Update(void);

/**
 * @brief Sets the dog animation
 *
 * @param mode DogMode enum
 */
void dog_SetMode(uint8_t mode);

/**
 * @brief Loops and draws dog scene base on set mode
 *
 */
void draw_dog_scene(void);

/**
 * @brief Draw the dog buffer layer
 *
 */
void draw_dog_buffer_layer(void);

/**
 * @brief Get the dog buffer layer
 *
 */
void get_dog_buffer_layer(void);

#endif