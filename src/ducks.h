#ifndef DUCKS_H
#define DUCKS_H

#define DUCK_ANIMATE_TIMER_MAX 4

#include <tice.h>
#include <graphx.h>

extern int timers[5];
extern int amount_fallen;
extern int fallen_id;
extern int enemies_amount;

struct enemies_t
{
	// position of duck
	int x;
	int y;

	// is bird dead / alive or not active.
	bool active;
	bool shot;

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
extern struct enemies_t enemies[5];

void SetCostume(uint8_t pos, uint8_t num);

void draw_enemies(void);
void update_enemies(void);

void animate_sprites(uint8_t pos);

void init_enemies(uint8_t amount, uint8_t level);

int Goto_Pos(int pos, int Dpos, uint8_t speed);
int Set_Goto_Y(void);
int Set_Goto_X(void);

#endif