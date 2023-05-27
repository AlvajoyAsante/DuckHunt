#ifndef PLAYER_H
#define PLAYER_H

#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <compression.h>

/* Player information */
struct player_t
{
	int x;
	int y;

	int score;

	int speed;

	int bullets;
	int level;
	int round;

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