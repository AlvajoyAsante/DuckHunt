#include "ducks.h"
#include "ui.h"
#include "dog.h"
#include "menu.h"
#include "player.h"
#include "gfx/DUCKSPT.h"

struct enemies_t enemies[5];
int enemies_amount;
int timers[5];
int amount_fallen;
int fallen_id;

/* Duck Animations */
static void animate(uint8_t pos)
{
	/* Check and updates constume numbers based on current costume */
	switch (enemies[pos].cnum)
	{
		/* Duck A's happen here */
	case 1: // If Costume is 1 change it at the right time to 2
		if (enemies[pos].animate >= DUCK_ANIMATE_TIMER_MAX)
			enemies[pos].cnum = 2;
		break;

	case 2: // If Costume is 2 change it at the right time to 3
		if (enemies[pos].animate >= DUCK_ANIMATE_TIMER_MAX)
			enemies[pos].cnum = 3;
		break;

	case 3: // If Costume is 3 change to 1 and update angle
		enemies[pos].cnum = 1;
		goto angle;
		break;

		/* Duck B's happen here */
	case 4: // If Costume is 4 change it at the right time to 5
		if (enemies[pos].animate >= DUCK_ANIMATE_TIMER_MAX)
			enemies[pos].cnum = 5;
		break;

	case 5: // If Costume is 5 change it at the right time to 6
		if (enemies[pos].animate >= DUCK_ANIMATE_TIMER_MAX)
			enemies[pos].cnum = 6;
		break;

	case 6: // If Costume is 6 change to 4 and update angle
		enemies[pos].cnum = 4;
		goto angle;
		break;

	case 7: // If Costume is 7 (Shot) then wait 10 milsec and change to 8
		if (timers[pos] >= DUCK_ANIMATE_TIMER_MAX * 3)
			enemies[pos].cnum = 8;
		break;

	case 8: // If Costume is 8 change it at the right time to 9
		if (enemies[pos].animate >= DUCK_ANIMATE_TIMER_MAX)
			enemies[pos].cnum = 9;
		break;

	case 9: // If Costume is 9 change it at the right time to 8
		if (enemies[pos].animate >= DUCK_ANIMATE_TIMER_MAX)
			enemies[pos].cnum = 8;
		break;
	}
	return;

angle:
	/* Checks if duck is moving left or right */
	if (enemies[pos].angle == 1 || enemies[pos].angle == 2)
	{
		enemies[pos].cnum = 1;
		return;
	}

	/* Checks if duck is move up or down */
	if (enemies[pos].angle == 3 || enemies[pos].angle == 4)
	{
		enemies[pos].cnum = 4;
		return;
	}

	/* Check duck was shot */
	if (enemies[pos].angle == 0)
	{
		enemies[pos].cnum = 7;
		return;
	}
}

/* Manages the animations of every duck  */
void animate_sprites(uint8_t pos)
{
	gfx_sprite_t *temp_buffer;
	gfx_sprite_t *sprite_buff = gfx_MallocSprite(40, 40);

	// Animate ducks based
	animate(pos);

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

		if (enemies[pos].angle == 2)
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

		if (enemies[pos].angle == 2)
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

		if (enemies[pos].angle == 2)
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

		if (enemies[pos].angle == 4)
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

		if (enemies[pos].angle == 4)
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

		if (enemies[pos].angle == 4)
		{
			gfx_TransparentSprite(gfx_FlipSpriteY(temp_buffer, sprite_buff), enemies[pos].x, enemies[pos].y);
		}
		else
		{
			gfx_TransparentSprite(temp_buffer, enemies[pos].x, enemies[pos].y);
		}

		break;

	case 7: // Shot Duck

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
	}

	// free(temp_buffer);
	free(sprite_buff);
}

void update_enemies(void)
{
	for (int i = 0; i < enemies_amount; i++)
	{
		if (enemies[i].active)
		{
			/* Checks if the X position of duck is at its dest point */
			if (enemies[i].x != enemies[i].gotoX)
			{

				if (enemies[i].x < enemies[i].gotoX)
				{
					enemies[i].x += enemies[i].speed;
					if (enemies[i].angle != 0)
						enemies[i].angle = 1; // Face right
				}
				else if (enemies[i].x > enemies[i].gotoX)
				{
					enemies[i].x -= enemies[i].speed;
					if (enemies[i].angle != 0)
						enemies[i].angle = 2; // Face Left
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
				if (enemies[i].angle != 0)
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
						if (enemies[i].angle != 0 && enemies[i].angle != 2)
							enemies[i].angle = 3;
					}
					else if (enemies[i].y > enemies[i].gotoY) // Check if the Y position is above the dest position
					{
						/* Update the Y position based on speed */
						enemies[i].y -= enemies[i].speed;

						/* Update angle if not equal to 0 or 1 */
						if (enemies[i].angle != 0 && enemies[i].angle != 1)
							enemies[i].angle = 4;
					}
				}
			}
			else
			{
				/* Check if the bird is falling */
				if (enemies[i].angle == 0)
				{
					amount_fallen++;
					enemies[i].active = 0;
					return;
				}
				else
				{
					enemies[i].gotoY = Set_Goto_Y();
				}
			}

			/* General timer */
			if (timers[i] < DUCK_ANIMATE_TIMER_MAX * 3)
			{
				timers[i]++; // Update the timer
			}
			else
			{
				timers[i] = 0; // Reset the timer
			}

			/* Animation timer */
			if (enemies[i].animate < DUCK_ANIMATE_TIMER_MAX)
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
			if ((amount_fallen % enemies_amount) == 0)
			{
				if (menu.opt <= 2) // init a new levevl
					init_enemies(menu.opt, player.level++);
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
	for (int i = 0; i < enemies_amount; i++)
	{
		/* Checks if the duck is active */
		if (enemies[i].active)
		{
			/* Animate the duck sprites */
			animate_sprites(i);

			/* Render the grass if the duck is a certain */
			if (enemies[i].y > 134)
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

void init_enemies(uint8_t amount, uint8_t level)
{
	enemies_amount = amount;

	for (int i = 0; i < enemies_amount; i++)
	{
		/* bool to check if active and not shot */
		enemies[i].active = 1;

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
		enemies[i].shot = 0;
		enemies[i].angle = 1; // flying angle

		/* Set Duck speed based on input level */
		switch (level)
		{
		case 1:
		case 2:
			enemies[i].speed = 1;
			break;

		case 3:
		case 4:
			enemies[i].speed = 2;
			break;

		case 5:
		case 6:
			enemies[i].speed = 3;
			break;

		case 7:
		case 8:
			enemies[i].speed = 4;
			break;

		case 9:
		case 10:
			enemies[i].speed = 5;
			break;

		case 11:
		case 12:
			enemies[i].speed = 6;
			break;

		case 13:
		case 14:
			enemies[i].speed = 7;
			break;

		case 15:
		case 16:
			enemies[i].speed = 8;
			break;

		default:
			enemies[i].speed = randInt(8, 10);
			break;
		}

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
	}

	/* Set amount of shot ducks to zero */
	amount_fallen = 0;
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