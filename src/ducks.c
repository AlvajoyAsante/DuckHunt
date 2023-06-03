#include <stdbool.h>
#include "ducks.h"
#include "ui.h"
#include "utils.h"
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
static int Set_Goto_Y(void)
{
	if (menu.option < 3)
	{
		if (randInt(0, 1))
		{
			return 8;
		}
		else
		{
			return 167 - 35;
		}
	}
	else
	{
		// Game C
		return randInt(GAME_CANVAS_Y_MIN + 30, (GAME_CANVAS_Y_MIN + 30) + 10);
	}
}

static int Set_Goto_X(void)
{
	if (menu.option < 3)
	{
		// Game A

		if (randInt(0, 1))
		{
			return 33;
		}
		else
		{
			return 254;
		}
	}
	else
	{
		// Game C
		return randInt(GAME_CANVAS_X_MIN, GAME_CANVAS_X_MAX);
	}
}

static void enemies_manage_cnum(uint8_t pos)
{
	int distance = get_distance(enemies[pos].x, enemies[pos].y, enemies[pos].gotoX, enemies[pos].gotoY);

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

	case 13:
		if (distance < 50)
			enemies[pos].cnum = 14;
		break;

	case 14:
		if (distance < 30)
			enemies[pos].cnum = 15;
		break;

		/* case 15:
			// This case is not need but here for visuals
			if (distance < 10)
			enemies[pos].cnum = 13;
			break; */
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
static void enemies_render_sprites(uint8_t pos)
{
	gfx_sprite_t *temp_buffer;
	gfx_sprite_t *sprite_buff = gfx_MallocSprite(40, 40);

	if (enemies[pos].animate >= TIMER_ANIMATE_MAX)
	{
		enemies_manage_cnum(pos);
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

	case 13:
		gfx_TransparentSprite(Clay_1, enemies[pos].x, enemies[pos].y);
		break;

	case 14:
		gfx_TransparentSprite(Clay_2, enemies[pos].x, enemies[pos].y);
		break;

	case 15:
		gfx_TransparentSprite(Clay_3, enemies[pos].x, enemies[pos].y);
		break;
	}

	free(sprite_buff);
}

static int get_active_enemies(void)
{
	int tick = 0;
	for (int i = 0; i < DUCK_AMOUNT; i++)
	{
		if (enemies[i].active)
		{
			tick++;
		}
	}
	return tick;
}

static int get_inactive_enemies(void)
{
	int tick = 0;
	for (int i = 0; i < DUCK_AMOUNT; i++)
	{
		if (!enemies[i].active)
		{
			tick++;
		}
	}
	return tick;
}

static int get_inactive_shot_enemies(void)
{
	int tick = 0;
	for (int i = 0; i < DUCK_AMOUNT; i++)
	{
		if (!enemies[i].active && enemies[i].shot == true)
		{
			tick++;
		}
	}
	return tick;
}

void update_enemies(void)
{
	uint8_t speed;

	if (menu.option < 3)
	{
		if (DUCK_FLYAWAY_TIMER == DUCK_FLYAWAY_MAX)
		{
			if (dog.mode != DOG_LAUGH)
			{
				dog_SetMode(DOG_LAUGH);
			}

			draw_dog_buffer_layer();
			dog_Update();

			if (dog.mode == DOG_HIDDEN)
			{
				DUCK_FLYAWAY_TIMER = 0;
			}
		}
		else
		{
			DUCK_FLYAWAY_TIMER++;
		}
	}

	for (int i = 0; i < DUCK_AMOUNT; i++)
	{
		if (enemies[i].active)
		{
			if (menu.option < 3)
			{
				// Game A and B

				/* Check if the player hasn't shot */
				if (DUCK_FLYAWAY_TIMER == DUCK_FLYAWAY_MAX)
				{
					enemies[i].angle = DUCK_FALLING;
					enemies[i].gotoX = enemies[i].x;
					enemies[i].gotoY = -20;
					enemies[i].speed = 4;
					enemies[i].fly_away = true;

					if (enemies[i].cnum < 10)
					{
						game.duck_hits[get_duck_hits_amount()] = DUCK_FORCED_FLYAWAY;
						enemies[i].cnum = 10;
						GAME_TOTAL_HITS++;
					}
				}

				/* If there zero bullets left */
				if (!player.bullets)
				{
					/* Check if the duck is not shot  */
					if (!enemies[i].shot)
					{
						enemies[i].angle = DUCK_FALLING;
						enemies[i].gotoX = enemies[i].x;
						enemies[i].gotoY = -20;
						enemies[i].speed = 4;
						enemies[i].fly_away = true;

						/* Set the costume to 10 */
						if (enemies[i].cnum < 10)
						{
							game.duck_hits[get_duck_hits_amount()] = DUCK_FLYAWAY;
							enemies[i].cnum = 10;
							GAME_TOTAL_HITS++;
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
					/* Check if the bird is falling or flying away  */
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
			}
			else
			{
				// Game C Updating

				/* Updating the X position */
				if (enemies[i].x != enemies[i].gotoX)
				{
					speed = abs(enemies[i].gotoX - enemies[i].x) / (enemies[i].speed + 5);

					if (enemies[i].x < enemies[i].gotoX)
					{
						enemies[i].x += speed;
					}
					else
					{
						enemies[i].x -= speed;
					}
				}
				else
				{
				}

				/* Updating the Y position  */
				if (enemies[i].y != enemies[i].gotoY)
				{
					speed = abs(enemies[i].gotoY - enemies[i].y) / (enemies[i].speed + 5);

					if (enemies[i].y < enemies[i].gotoY)
					{
						enemies[i].y += speed;
					}
					else
					{
						enemies[i].y -= speed;
					}
				}
				else
				{
				}
			}

			/* Animation timer */
			if (enemies[i].animate < TIMER_ANIMATE_MAX)
			{
				enemies[i].animate++; // Update the timer
			}
			else
			{
				enemies[i].animate = 0; // Reset the timer
			}
		}
	}

	/* Checks if the all ducks have fallen */
	if (get_inactive_enemies() == DUCK_AMOUNT)
	{
		if (DUCK_FLYAWAY_TIMER == DUCK_FLYAWAY_MAX)
		{
			return;
		}

		if (menu.option < 3)
		{
			/* Check if player has ran through 10 ducks */
			if (GAME_TOTAL_HITS > 9)
			{
				bubble_sort_hit_panel();

				if (get_duck_hits_amount() >= GAME_ADVANCE_THRESHOLD)
				{
					/* Reset bullets and increase rounds */
					player.bullets = 3;
					player.round++;

					/* Reset hit ducks on HUD */
					reset_duck_hits();

					/* Draw dog scene again */
					draw_scene();

					/* Init new ducks to fly */
					GAME_TOTAL_HITS = 0;
					init_enemies(menu.option);
					return;
				}
				else
				{
					/* Temporary Game Over Screen */
					gfx_End();
					exit(1);
				}
			}

			if (get_inactive_shot_enemies() == DUCK_AMOUNT)
			{
				dog_SetMode(DOG_PEEK_UP); // Pop up
				draw_dog_scene();
			}

			init_enemies(menu.option);
		}
		else
		{
			// GAME C
		}

		player.bullets = 3; // Reset Bullets

		DUCK_FALLEN_AMOUNT = 0; // Reset Fallen Amount

		return;
	}
}

/* Draws every duck sprite based on its animation # */
void draw_enemies(void)
{
	if (menu.option < 3 && DUCK_FLYAWAY_TIMER == DUCK_FLYAWAY_MAX)
	{
		if (dog.mode == DOG_LAUGH)
		{
			get_dog_buffer_layer();
			dog_Render();
		}
	}

	/* Draws and updates all the ducks */
	for (int i = 0; i < DUCK_AMOUNT; i++)
	{
		/* Checks if the duck is active */
		if (enemies[i].active)
		{

			/* Animate the duck sprites */
			enemies_render_sprites(i);

			if (menu.option < 3)
			{
				// Game A and B
				/* Set the transparent color of the duck based on the player game mode (aka menu.option) */
				switch (menu.option)
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
				if (enemies[i].back_buffer != NULL)
					gfx_TransparentSprite(enemies[i].back_buffer, enemies[i].x - 1, enemies[i].y - 1);

				/* reset transparent color */
				gfx_SetTransparentColor(0);
			}
			else
			{
				// Game C
				// gfx_SetColor(0);
				// gfx_Line(enemies[i].x, enemies[i].y, enemies[i].gotoX, enemies[i].gotoY);
			}
		}
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

		enemies[i].back_buffer = NULL;

		/* Setting duck speed */
		if (player.round >= 1 && player.round <= 10)
		{
			speed = randInt(1, 3);
		}
		else if (player.round >= 11 && player.round <= 12)
		{
			speed = randInt(2, 5);
		}
		else if (player.round >= 13 && player.round <= 14)
		{
			speed = randInt(3, 6);
		}
		else if (player.round >= 15 && player.round <= 19)
		{
			speed = randInt(4, 7);
		}
		else
		{
			speed = randInt(5, 8);
		}

		enemies[i].speed = speed;

		if (menu.option < 3)
		{
			// Game A and B
			/* Costume Number for animation */
			enemies[i].cnum = 1;

			/* Set the base level y position */
			enemies[i].y = 167;

			/* Setting the a random X position */
			enemies[i].x = randInt(32, 254);

			/* Check if the random generaotated position going to go over canvas (xpos + width_of_sprite) */
			if (enemies[i].x + 33 >= 287)
				enemies[i].x = 287 - (enemies[i].gotoX + 34);

			/* Randomly Set the fly position */
			enemies[i].gotoX = Set_Goto_X();
			enemies[i].gotoY = Set_Goto_Y();

			/* Reset the if shot and flying angle */
			enemies[i].shot = false;
			enemies[i].angle = FACE_RIGHT; // flying angle

			/* Sets the duck type */
			enemies[i].type = randInt(1, 3);
		}
		else
		{
			// Game C
			enemies[i].type = 4;

			/* Costume Number for animation */
			enemies[i].cnum = 13;

			/* Set the base level y position */
			enemies[i].y = 167;

			/* Setting the a random X position */
			enemies[i].x = randInt(32, 254);

			/* Check if the random generaotated position going to go over canvas (xpos + width_of_sprite) */
			if (enemies[i].x + 16 >= GAME_CANVAS_X_MAX)
				enemies[i].x = GAME_CANVAS_X_MAX - (enemies[i].gotoX + 16);

			/* Randomly Set the fly position */
			enemies[i].gotoX = Set_Goto_X();

			enemies[i].gotoY = randInt(48, 91);
		}
	}
}

void add_enemies(void)
{
	uint8_t speed = 0;

	if (get_active_enemies() == DUCK_AMOUNT)
	{
		return;
	}

	for (int i = get_active_enemies(); i < DUCK_AMOUNT; i++)
	{
		/* bool to check if active and not shot */
		enemies[i].active = true;

		/* Setting duck speed */
		if (player.round >= 1 && player.round <= 10)
		{
			speed = randInt(1, 3);
		}
		else if (player.round >= 11 && player.round <= 12)
		{
			speed = randInt(2, 5);
		}
		else if (player.round >= 13 && player.round <= 14)
		{
			speed = randInt(3, 6);
		}
		else if (player.round >= 15 && player.round <= 19)
		{
			speed = randInt(4, 7);
		}
		else
		{
			speed = randInt(5, 8);
		}

		enemies[i].speed = speed;

		if (menu.option < 3)
		{
			// Game A and B
			/* Costume Number for animation */
			enemies[i].cnum = 1;

			/* Set the base level y position */
			enemies[i].y = 167;

			/* Setting the a random X position */
			enemies[i].x = randInt(32, 254);

			/* Check if the random generaotated position going to go over canvas (xpos + width_of_sprite) */
			if (enemies[i].x + 33 >= 287)
				enemies[i].x = 287 - (enemies[i].gotoX + 34);

			/* Randomly Set the fly position */
			enemies[i].gotoX = Set_Goto_X();
			enemies[i].gotoY = Set_Goto_Y();

			/* Reset the if shot and flying angle */
			enemies[i].shot = false;
			enemies[i].angle = FACE_RIGHT; // flying angle

			/* Sets the duck type */
			enemies[i].type = randInt(1, 3);
		}
		else
		{
			// Game C
			/* Costume Number for animation */
			enemies[i].cnum = 13;

			/* Set the base level y position */
			enemies[i].y = 167;

			/* Setting the a random X position */
			enemies[i].x = randInt(32, 254);

			/* Check if the random generaotated position going to go over canvas (xpos + width_of_sprite) */
			if (enemies[i].x + 16 >= GAME_CANVAS_X_MAX)
				enemies[i].x = GAME_CANVAS_X_MAX - (enemies[i].gotoX + 16);

			/* Randomly Set the fly position */
			enemies[i].gotoX = Set_Goto_X();

			enemies[i].gotoY = randInt(48, 91);
		}
	}
}

void get_duck_buffer_layer(void)
{
	for (int i = 0; i < DUCK_AMOUNT; i++)
	{
		if (enemies[i].back_buffer == NULL)
		{
			enemies[i].back_buffer = gfx_MallocSprite(38, 38);
		}

		gfx_GetSprite(enemies[i].back_buffer, enemies[i].x - 1, enemies[i].y - 1);
	}
}

void draw_duck_buffer_layer(void)
{
	/* Draw the ducks */
	for (int i = 0; i < DUCK_AMOUNT; i++)
	{
		if (enemies[i].back_buffer != NULL)
		{
			gfx_TransparentSprite(enemies[i].back_buffer, enemies[i].x - 1, enemies[i].y - 1);
			free(enemies[i].back_buffer);
		}

		enemies[i].back_buffer = NULL;
	}
}