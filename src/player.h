#ifndef PLAYER_H
#define PLAYER_H

#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <compression.h>

/* Variables */
struct player_t {
	int x;
	int y;

	int score;
	
	int speed;
	
	int bullets;
	int level;

	gfx_sprite_t *back_buffer;

	uint8_t timer;
};
extern struct player_t player;


/* player keys + shooting */
void draw_player(void);
bool player_keys(void);

#endif