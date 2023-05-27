#ifndef PLAYER_H
#define PLAYER_H

#define TIMER_RECOIL_MAX 30

#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <compression.h>

/* Player information */
struct player_t
{
	// Player position
	int x;
	int y;

	// Player Overall Score
	int score;

	// Player Movement Speed
	int speed;

	// Player Bullet amount
	int bullets;

	// Player Level and round information
	int level;
	int round;

	// Player Rendering information
	gfx_sprite_t *back_buffer;
	uint8_t timer;
};
extern struct player_t player;

/**
 * @brief Checks for user keys
 *
 * @return true user does not want to exit
 * @return false user wants to exit
 */
bool player_keys(void);

/**
 * @brief Renders player cursor
 *
 */
void draw_player(void);

#endif