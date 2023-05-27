#include <stdbool.h>
#include "ducks.h"
#include "ui.h"
#include "dog.h"
#include "menu.h"
#include "player.h"
#include "gfx/DUCKSPT.h"

enum DUCK_ANGLE
{
	DUCK_FALLING = 0,
	FACE_RIGHT = 1,
	FACE_LEFT = 2,
	FACE_UP_RIGHT = 3,
	FACE_UP_LEFT = 4
};

struct enemies_t enemies[5];

/* Duck Animations */
static void animate(uint8_t pos)
{

	if (enemies[pos].cnum == 3 || enemies[pos].cnum == 6)
	{
		goto angle;
	}

	/* Check and updates constume numbers based on current costume */
	switch (enemies[pos].cnum)
	{
		/* Duck A's happen here */
	case 1: // If Costume is 1 change it at the right time to 2
		enemies[pos].cnum = 2;
		break;

	case 2: // If Costume is 2 change it at the right time to 3
		enemies[pos].cnum = 3;
		break;

	case 3: // If Costume is 3 change to 1 and update angle
		enemies[pos].cnum = 1;
		break;

		/* Duck B's happen here */
	case 4: // If Costume is 4 change it at the right time to 5
		enemies[pos].cnum = 5;
		break;

	case 5: // If Costume is 5 change it at the right time to 6
		enemies[pos].cnum = 6;
		break;

	case 6: // If Costume is 6 change to 4 and update angle
		enemies[pos].cnum = 4;
		break;

		/* Duck Shot */
	case 7: // If Costume is 7 (Shot) then wait 10 milsec and change to 8
		enemies[pos].cnum = 8;
		break;

		/* Duck Falling */
	case 8: // If Costume is 8 change it at the right time to 9
		enemies[pos].cnum = 9;
		break;

	case 9: // If Costume is 9 change it at the right time to 8
		enemies[pos].cnum = 8;
		break;

		/* Duck Flying Away */
	case 10: // If Costume is 10 change it at the right time to 11
		enemies[pos].cnum = 11;
		break;
	case 11: // If Costume is 11 change it at the right time to 12
		enemies[pos].cnum = 12;
		break;
	case 12: // If Costume is 12 change it at the right time to 10
		enemies[pos].cnum = 10;
		break;
	}

	return;

angle:
	/* Checks if duck is moving left or right */
	if (enemies[pos].angle == FACE_RIGHT || enemies[pos].angle == FACE_LEFT)
	{
		enemies[pos].cnum = 1;
		return;
	}

	/* Checks if duck is move up or down */
	if (enemies[pos].angle == FACE_UP_RIGHT || enemies[pos].angle == FACE_UP_LEFT)
	{
		enemies[pos].cnum = 4;
		return;
	}

	/* Check duck was shot or is flying away */
	if (enemies[pos].angle == DUCK_FALLING)
	{
		if (enemies[pos].shot)
		{
			enemies[pos].cnum = 7; // Set to shot sprite
		}
		else if (enemies[pos].fly_away)
		{
			enemies[pos].cnum = 10; // Set to Flying away sprite
		}

		return;
	}
}

/* Manages the animations of every duck  */
void animate_sprites(uint8_t pos)
{
	gfx_sprite_t *temp_buffer;
	gfx_sprite_t *sprite_buff = gfx_MallocSprite(40, 40);

	if (enemies[pos].animate >= ANIMATE_TIMER_MAX)
	{
		animate(pos);
	}

	/* Render ducks based on sprites */
	switch (enemies[pos].cnum)
	{
	case 1: // Duck Spite A_1

		switch (enemies[pos].type)
		{ // based on speeed
		case 1:
			temp_buffer = Duck_A_1;
			break;

		case 2:
			temp_buffer = Duckb_A_1;
			break;

		case 3:
			temp_buffer = Duckc_A_1;
			break;
		}

		if (enemies[pos].angle == FACE_LEFT)
		{
			gfx_TransparentSprite(gfx_FlipSpriteY(temp_buffer, sprite_buff), enemies[pos].x, enemies[pos].y);
		}
		else
		{
			gfx_TransparentSprite(temp_buffer, enemies[pos].x, enemies[pos].y);
		}

		break;

	case 2: // Duck Spite A_2

		switch (enemies[pos].type)
		{ // based on speeed
		case 1:
			temp_buffer = Duck_A_2;
			break;

		case 2:
			temp_buffer = Duckb_A_2;
			break;

		case 3:
			temp_buffer = Duckc_A_2;
			break;
		}

		if (enemies[pos].angle == FACE_LEFT)
		{
			gfx_TransparentSprite(gfx_FlipSpriteY(temp_buffer, sprite_buff), enemies[pos].x, enemies[pos].y);
		}
		else
		{
			gfx_TransparentSprite(temp_buffer, enemies[pos].x, enemies[pos].y);
		}

		break;

	case 3: // Duck Spite A_3

		switch (enemies[pos].type)
		{ // based on speeed
		case 1:
			temp_buffer = Duck_A_3;
			break;

		case 2:
			temp_buffer = Duckb_A_3;
			break;

		case 3:
			temp_buffer = Duckc_A_3;
			break;
		}

		if (enemies[pos].angle == FACE_LEFT)
		{
			gfx_TransparentSprite(gfx_FlipSpriteY(temp_buffer, sprite_buff), enemies[pos].x, enemies[pos].y);
		}
		else
			gfx_TransparentSprite(temp_buffer, enemies[pos].x, enemies[pos].y);
		break;

	case 4: // Duck Spite B_1

		switch (enemies[pos].type)
		{ // based on speeed
		case 1:
			temp_buffer = Duck_B_1;
			break;

		case 2:
			temp_buffer = Duckb_B_1;
			break;

		case 3:
			temp_buffer = Duckc_B_1;
			break;
		}

		if (enemies[pos].angle == FACE_UP_LEFT)
		{
			gfx_TransparentSprite(gfx_FlipSpriteY(temp_buffer, sprite_buff), enemies[pos].x, enemies[pos].y);
		}
		else
			gfx_TransparentSprite(temp_buffer, enemies[pos].x, enemies[pos].y);
		break;

	case 5: // Duck Spite B_2

		switch (enemies[pos].type)
		{ // based on speeed
		case 1:
			temp_buffer = Duck_B_2;
			break;

		case 2:
			temp_buffer = Duckb_B_2;
			break;

		case 3:
			temp_buffer = Duckc_B_2;
			break;
		}

		if (enemies[pos].angle == FACE_UP_LEFT)
		{
			gfx_TransparentSprite(gfx_FlipSpriteY(temp_buffer, sprite_buff), enemies[pos].x, enemies[pos].y);
		}
		else
		{
			gfx_TransparentSprite(temp_buffer, enemies[pos].x, enemies[pos].y);
		}

		break;

	case 6: // Duck Spite B_3

		switch (enemies[pos].type)
		{ // based on speeed
		case 1:
			temp_buffer = Duck_B_3;
			break;

		case 2:
			temp_buffer = Duckb_B_3;
			break;

		case 3:
			temp_buffer = Duckc_B_3;
			break;
		}

		if (enemies[pos].angle == FACE_UP_LEFT)
		{
			gfx_TransparentSprite(gfx_FlipSpriteY(temp_buffer, sprite_buff), enemies[pos].x, enemies[pos].y);
		}
		else
		{
			gfx_TransparentSprite(temp_buffer, enemies[pos].x, enemies[pos].y);
		}

		break;

	/* Shot duck */
	case 7:

		switch (enemies[pos].type)
		{ // based on speeed
		case 1:
			temp_buffer = Duck_Shot;
			break;

		case 2:
			temp_buffer = Duckb_Shot;
			break;

		case 3:
			temp_buffer = Duckc_Shot;
			break;
		}

		gfx_TransparentSprite(temp_buffer, enemies[pos].x, enemies[pos].y);
		break;

	/* Ducks falling */
	case 8: // Falling Duck 2

		switch (enemies[pos].type)
		{ // based on speeed
		case 1:
			temp_buffer = Duck_Fall_2;
			break;

		case 2:
			temp_buffer = Duckb_Fall_2;
			break;

		case 3:
			temp_buffer = Duckc_Fall_2;
			break;
		}

		gfx_TransparentSprite(temp_buffer, enemies[pos].x, enemies[pos].y);
		break;

	case 9: // Falling Duck 1

		switch (enemies[pos].type)
		{ // based on speeed
		case 1:
			temp_buffer = Duck_Fall_1;
			break;

		case 2:
			temp_buffer = Duckb_Fall_1;
			break;

		case 3:
			temp_buffer = Duckc_Fall_1;
			break;
		}

		gfx_TransparentSprite(temp_buffer, enemies[pos].x, enemies[pos].y);
		break;

	/* Ducks Flying away */
	case 10:
		switch (enemies[pos].type)
		{ // based on speeed
		case 1:
			temp_buffer = Duck_Flyaway_1;
			break;

		case 2:
			temp_buffer = Duckb_Flyaway_1;
			break;

		case 3:
			temp_buffer = Duckc_Flyaway_1;
			break;
		}

		gfx_TransparentSprite(temp_buffer, enemies[pos].x, enemies[pos].y);
		break;

	case 11:
		switch (enemies[pos].type)
		{ // based on speeed
		case 1:
			temp_buffer = Duck_Flyaway_2;
			break;

		case 2:
			temp_buffer = Duckb_Flyaway_2;
			break;

		case 3:
			temp_buffer = Duckc_Flyaway_2;
			break;
		}

		gfx_TransparentSprite(temp_buffer, enemies[pos].x, enemies[pos].y);
		break;

	case 12:
		switch (enemies[pos].type)
		{ // based on speeed
		case 1:
			temp_buffer = Duck_Flyaway_3;
			break;

		case 2:
			temp_buffer = Duckb_Flyaway_3;
			break;

		case 3:
			temp_buffer = Duckc_Flyaway_3;
			break;
		}

		gfx_TransparentSprite(temp_buffer, enemies[pos].x, enemies[pos].y);
		break;
	}

	// free(temp_buffer);
	free(sprite_buff);
}

void update_enemies(void)
{
	for (int i = 0; i < DUCK_AMOUNT; i++)
	{
		if (enemies[i].active)
		{
			if (player.bullets < 1)
			{
				if (!enemies[i].shot)
				{
					enemies[i].angle = DUCK_FALLING;
					enemies[i].gotoY = -20;
					enemies[i].gotoX = enemies[i].x;
					enemies[i].speed = 4;
					enemies[i].fly_away = 1;
					if (enemies[i].cnum < 10)
					{
						enemies[i].cnum = 10;
						game.duck_hits[get_duck_hits_amount()] = 0;
					}
				}
			}

			/* Checks if the X position of duck is at its dest point */
			if (enemies[i].x != enemies[i].gotoX)
			{

				if (enemies[i].x < enemies[i].gotoX)
				{
					enemies[i].x += enemies[i].speed;
					if (enemies[i].angle != DUCK_FALLING)
						enemies[i].angle = FACE_RIGHT;
				}
				else if (enemies[i].x > enemies[i].gotoX)
				{
					enemies[i].x -= enemies[i].speed;
					if (enemies[i].angle != DUCK_FALLING)
						enemies[i].angle = FACE_LEFT;
				}

				/* Check if the positin is in the radius of dest point */
				if (enemies[i].x - enemies[i].gotoX <= enemies[i].speed && enemies[i].x - enemies[i].gotoX >= -(enemies[i].speed))
				{
					enemies[i].x = enemies[i].gotoX;
				}
			}
			else
			{
				/* if at it's destination then set a new got X */
				if (enemies[i].angle != DUCK_FALLING)
				{
					enemies[i].gotoX = Set_Goto_X();
				}
			}

			/* Checks if the Y position of duck is at its dest point */
			if (enemies[i].y != enemies[i].gotoY)
			{
				/* Check is the y position is in radius of the destination postion */
				if (enemies[i].y - enemies[i].gotoY <= enemies[i].speed && enemies[i].y - enemies[i].gotoY >= -(enemies[i].speed))
					enemies[i].y = enemies[i].gotoY;

				/* if the duck is custom number is not  on falling duck sprite */
				if (enemies[i].cnum != 7)
				{
					/* Check if the Y position is below the dest Y position  */
					if (enemies[i].y < enemies[i].gotoY)
					{
						/* Update the Y position based on speed */
						enemies[i].y += enemies[i].speed;

						/* Update angle if not equal to 0 or 2 */
						if (enemies[i].angle != DUCK_FALLING && enemies[i].angle != FACE_LEFT)
							enemies[i].angle = 3;
					}
					else if (enemies[i].y > enemies[i].gotoY) // Check if the Y position is above the dest position
					{
						/* Update the Y position based on speed */
						enemies[i].y -= enemies[i].speed;

						/* Update angle if not equal to 0 or 1 */
						if (enemies[i].angle != DUCK_FALLING && enemies[i].angle != FACE_RIGHT)
							enemies[i].angle = 4;
					}
				}
			}
			else
			{
				/* Check if the bird is falling */
				if (enemies[i].angle == DUCK_FALLING)
				{
					DUCK_FALLEN_ID = i;
					enemies[i].active = false;
					return;
				}
				else
				{
					enemies[i].gotoY = Set_Goto_Y();
				}
			}

			/* Animation timer */
			if (enemies[i].animate < ANIMATE_TIMER_MAX)
			{
				enemies[i].animate++; // Update the timer
			}
			else
			{
				enemies[i].animate = 0; // Reset the timer
			}
		}
		else
		{
			/* Checks if the all ducks have fallen */
			if ((DUCK_FALLEN_AMOUNT % DUCK_AMOUNT) == 0)
			{

				if (menu.opt < 3)
				{
					if (GAME_TOTAL_HITS < 9)
					{
						GAME_TOTAL_HITS += menu.opt;
					}
					else
					{
						if (get_duck_hits_amount() >= GAME_ADVANCE_THRESHOLD)
						{
							// Manage the game
							player.round++;

							GAME_TOTAL_HITS = 0;

							/* Reset The data */
							player.bullets = 3; // Reset Bullets

							reset_duck_hits();

							draw_scene();
							return;
						}
						else
						{
							// Game Over
							gfx_End();
							exit(1);
						}
					}

					if (DUCK_FALLEN_AMOUNT == DUCK_AMOUNT)
					{
						dog_SetMode(DOG_PEEK_UP); // Pop
						draw_dog_scene();
					}

					init_enemies(menu.opt);
				}
				else
				{
				}

				player.bullets = 3; // Reset Bullets

				DUCK_FALLEN_AMOUNT = 0; // Reset Fallen Amount

				return;
			}
			else
			{
				continue;
			}
		}
	}
}

/* Draws every duck sprite based on its animation # */
void draw_enemies(void)
{
	/* Draws and updates all the ducks */
	for (int i = 0; i < DUCK_AMOUNT; i++)
	{
		/* Checks if the duck is active */
		if (enemies[i].active)
		{
			/* Animate the duck sprites */
			animate_sprites(i);

			/* Render the grass if the duck is a certain */
			if (enemies[i].y >= 134 || enemies[i].y <= 8)
			{
				/* Set the transparent color of the duck based on the player game mode (aka menu.opt) */
				switch (menu.opt)
				{
				case 1:
					gfx_SetTransparentColor(4);
					break;

				case 2:
					gfx_SetTransparentColor(5);
					break;

				case 3:
					gfx_SetTransparentColor(3);
					break;
				}

				/* Render the grass block right after the duck  */
				draw_duck_buffer_layer();

				/* reset transparent color */
				gfx_SetTransparentColor(0);
			}
		}
	}
}

/* routines below!! */
/**
 * @brief this function returns position of a point based on the given position
 *
 * @param pos postion
 * @param Dpos desition position
 * @param speed speed of obeject movement
 * @return int the next step in-order to move on
 */
int Goto_Pos(int pos, int Dpos, uint8_t speed)
{
	/* Checks if the start position does not eqaul to the desitionation position */
	if (pos != Dpos)
	{
		/* Checks if the postion is speed distance */
		if (pos - Dpos <= speed && pos - Dpos >= -(speed))
			return Dpos;

		/* Checks if the position is less than the destination position */
		if (pos < Dpos)
		{
			pos += speed;
		}
		else if (pos > Dpos) // Checks if the position is greater than position.
		{
			pos -= speed;
		}

		return pos;
	}
	else
	{
		return pos;
	}
}

void init_enemies(uint8_t amount)
{
	uint8_t speed = 0;

	/* Set amount of shot ducks to zero */
	DUCK_FALLEN_AMOUNT = 0;

	DUCK_AMOUNT = amount;

	for (int i = 0; i < DUCK_AMOUNT; i++)
	{
		/* bool to check if active and not shot */
		enemies[i].active = true;

		/* Costume Number for animation */
		enemies[i].cnum = 1;

		/* Setting the a random X position */
		enemies[i].x = randInt(32, 254);

		/* Check if the random generaotated position going to go over canvas (xpos + width_of_sprite) */
		if (enemies[i].x + 33 >= 287)
			enemies[i].x = 287 - (enemies[i].gotoX + 34);

		/* Set the base level y position */
		enemies[i].y = 167;

		/* Randomly Set the fly position */
		enemies[i].gotoX = Set_Goto_X();
		enemies[i].gotoY = Set_Goto_Y();

		/* Reset the if shot and flying angle */
		enemies[i].shot = false;
		enemies[i].angle = FACE_RIGHT; // flying angle

		/* Set Duck speed based on input level */

		/* Advanced amount */
		if (player.round >= 1 && player.round <= 10)
		{
			speed = randInt(1, 2);
		}
		else if (player.round >= 11 && player.round <= 12)
		{
			speed = randInt(2, 4);
		}
		else if (player.round >= 13 && player.round <= 14)
		{
			speed = randInt(3, 6);
		}
		else if (player.round >= 15 && player.round <= 19)
		{
			speed = randInt(3, 8);
		}
		else
		{
			speed = randInt(5, 8);
		}

		enemies[i].speed = speed;

		/* Sets the duck type based on the set speed */
		if (enemies[i].speed <= 3)
		{
			enemies[i].type = 1;
		}
		else if (enemies[i].speed > 3 && enemies[i].speed <= 6)
		{
			enemies[i].type = 2;
		}
		else if (enemies[i].speed > 6)
		{
			enemies[i].type = 3;
		}

		/* Setting Up the pionts */
		switch (enemies[i].type)
		{
		case 1:
			enemies[i].points = 500;
			break;

		case 2:
			enemies[i].points = 1000;
			break;

		case 3:
			enemies[i].points = 1500;
			break;
		}
	}
}

int Set_Goto_Y(void)
{ // for game A and B
	if (randInt(0, 1))
	{
		return 8;
	}
	else
	{
		return 167 - 35;
	}
}

int Set_Goto_X(void)
{
	if (randInt(0, 1))
	{
		return 33;
	}
	else
	{
		return 254;
	}
}
