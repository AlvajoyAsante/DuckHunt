#ifndef DUCKS_H
#define DUCKS_H

#include <tice.h>
#include <graphx.h>

/* Actions of the ducks */
enum DUCK_ACTIONS
{
	DUCK_SHOT = 1,
	DUCK_FLYAWAY = 2,
	DUCK_FORCED_FLYAWAY = 3
};

/* Enemies information */
struct enemies_t
{
	// position of duck
	int x;
	int y;

	// is bird dead / alive or not active.
	bool active;
	bool shot;
	bool fly_away;

	// Determines the amount of points
	int points;

	// predetermined based on  level
	int speed;

	// used for movement (animations)
	int gotoX;
	int gotoY;

	// custom number
	int cnum;

	// determines sprites angle
	int angle;

	// "mode" of enemies
	int type;

	// animation timer
	int animate;

	gfx_sprite_t *back_buffer;
};
extern struct enemies_t enemies[2];

/**
 * @brief Renders enemies information
 *
 */
void draw_enemies(void);

/**
 * @brief Updates enemies information
 *
 */
void update_enemies(void);

/**
 * @brief Initialise enemies
 *
 * @param amount amount of enemies you want to Initialise
 */
void init_enemies(uint8_t amount);

/**
 * @brief Draw the duck buffer layer
 *
 */
void draw_duck_buffer_layer(void);

/**
 * @brief Get the duck buffer layer
 *
 */
void get_duck_buffer_layer(void);

#endif