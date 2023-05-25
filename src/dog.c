#include "dog.h"
#include "ducks.h"
#include "ui.h"
#include "menu.h"
#include "gfx/DUCKSPT.h"

struct dog_t dog;

/**
 * Sets the dog animation type
 * (run to the center, jump over the grass, and peek when a duck has been shot)
 */
void dog_SetMode(uint8_t pos)
{
	dog.mode = pos;
	dog.speed = 1;
	dog.tick = 1;

	switch (pos)
	{
	case 1: // Run to the center.
		dog.x = 32;
		dog.y = 160;
		dog.cnum = 1;
		break;

	case 2: // Jump over grass.
		dog.x = 80;
		dog.y = 160;
		break;

	case 3: // peek when duck is shot.
		if (menu.opt == 1)
		{
			dog.cnum = 10;
		}
		else if (menu.opt == 2)
		{
			dog.cnum = 11;
		}

		dog.y = 159;
		if (enemies[DUCK_FALLEN_ID].x < 91)
		{
			dog.x = 91;
		}
		else if (enemies[DUCK_FALLEN_ID].x > 219)
		{
			dog.x = 219;
		}

		if (enemies[DUCK_FALLEN_ID].x < 91 && enemies[DUCK_FALLEN_ID].x > 219)
		{
			dog.x = 143;
		}
		dog.gotoY = dog.y - 20;
		break;
	}
}

static void dog_manage_cnum(void)
{
	switch (dog.cnum)
	{
	case 1:
		dog.cnum = 2;
		break;

	case 2:
		dog.cnum = 3;
		break;

	case 3:
		dog.cnum = 4;
		break;

	case 4:
		dog.cnum = 1;
		break;

	case 5:
		dog.cnum = 6;
		break;

	case 6:
		dog.cnum = 5;
		break;
	}
}

static void dog_animate(void)
{
	if (dog.animate == ANIMATE_TIMER_MAX)
	{
		dog_manage_cnum();
	}

	switch (dog.cnum)
	{
	case 1:
		gfx_TransparentSprite(dog_walk_0, dog.x, dog.y);
		break;

	case 2:
		gfx_TransparentSprite(dog_walk_1, dog.x, dog.y);
		break;

	case 3:
		gfx_TransparentSprite(dog_walk_2, dog.x, dog.y);
		break;

	case 4:
		gfx_TransparentSprite(dog_walk_3, dog.x, dog.y);
		break;

	case 5:
		gfx_TransparentSprite(dog_walk_4, dog.x, dog.y);
		break;

	case 6:
		gfx_TransparentSprite(dog_walk_5, dog.x, dog.y);
		break;

	case 7:
		gfx_TransparentSprite(dog_walk_6, dog.x, dog.y - 8);
		break;

	case 8:
		gfx_TransparentSprite(dog_jump_1, dog.x, dog.y);
		break;

	case 9:
		gfx_TransparentSprite(dog_jump_2, dog.x, dog.y);
		break;

	case 10:
		gfx_TransparentSprite(dog_bird_1, dog.x, dog.y);
		break;

	case 11:
		gfx_TransparentSprite(dog_bird_2, dog.x, dog.y);
		break;
	}
}

/**
 * Draws the dog based on the sprite number. (needs work)
 */
void dog_Render(void)
{
	gfx_sprite_t *back_buff = gfx_MallocSprite(70, 60);
	gfx_GetSprite(back_buff, dog.x - 10, dog.y - 10);

	dog_animate();

	if (dog.mode == 1 && dog.tick == 3)
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
		}

		/* Render the grass block right after the duck  */
		// draw_duck_buffer_layer();
		gfx_TransparentSprite(back_buff, dog.x - 10, dog.y - 10);

		/* reset transparent color */
		gfx_SetTransparentColor(0);
	}

	gfx_Blit(1);
	gfx_Sprite(back_buff, dog.x - 10, dog.y - 10);
	free(back_buff);
}

/**
 * Updates the dog movements based on the dog mode.
 */
void dog_Update(void)
{
	if (dog.animate < ANIMATE_TIMER_MAX)
	{
		dog.animate++;
	}
	else
	{
		dog.animate = 0;
	}

	switch (dog.mode)
	{
	case 1: // run to the center.
		if (dog.tick == 1)
		{
			if (dog.x == 100 / 2)
			{
				dog.cnum = 5;
				dog.animate = ANIMATE_TIMER_MAX;
				for (int i = 0; i < 3; i++)
				{
					dog_Render();
					delay(ANIMATE_TIMER_MAX * 50);
				}
				dog.cnum = 1;
				dog.x++;
				return;
			}
			dog.x = Goto_Pos(dog.x, 100, dog.speed);
			if (dog.x == 100)
			{
				dog.cnum = 7;
				dog.tick++;
			}
		}

		if (dog.tick == 2)
		{
			if (dog.x == 100)
			{
				dog.cnum = 5;
				dog.animate = ANIMATE_TIMER_MAX;
				for (int i = 0; i < 3; i++)
				{
					dog_Render();
					delay(ANIMATE_TIMER_MAX * 50);
				}

				dog.cnum = 7;
				dog_Render();
				delay(ANIMATE_TIMER_MAX * 50);
			}

			dog.cnum = 8;
			dog.x = Goto_Pos(dog.x, 145, dog.speed + 1);
			dog.y = Goto_Pos(dog.y, 115, dog.speed + 1);
			if (dog.y == 115 && dog.x == 145)
				dog.tick++;
		}

		if (dog.tick == 3)
		{
			dog.cnum = 9;
			dog.y = Goto_Pos(dog.y, 160, dog.speed + 2);
			if (dog.y == 160)
				dog.mode = 0;
		}

		break;

	case 2: // Jump over grass.
		if (dog.tick == 1)
		{
			dog.x = Goto_Pos(dog.x, 130, dog.speed);
			if (dog.x == 130)
				dog.tick++;
		}

		if (dog.tick == 2)
		{
			dog.y = Goto_Pos(dog.y, 109, dog.speed);
			if (dog.y == 109)
				dog.tick++;
		}

		if (dog.tick == 3)
		{
			dog.y = Goto_Pos(dog.y, 160, dog.speed);
			if (dog.y == 160)
				dog.mode = 0;
		}

		break;

	case 3: // peek up after bird shot.
		// peek up
		if (dog.tick == 1)
		{
			dog.y = Goto_Pos(dog.y, dog.gotoY, dog.speed);

			if (dog.y == dog.gotoY)
			{
				dog.tick++;
				dog.gotoY = dog.y + 20;
			}
		}

		delay(ANIMATE_TIMER_MAX * 50);

		// Go back down
		if (dog.tick == 2)
		{

			dog.y = Goto_Pos(dog.y, dog.gotoY, dog.speed);

			if (dog.y == dog.gotoY)
				dog.mode = 0;
		}
		// peek back down
		break;
	}
}

/**
 * Draws the dog jumping for the beginning of the game.
 */
void draw_dog_scene(void)
{

	dog_SetMode(1);

	while (dog.mode != 0)
	{
		dog_Render();
		dog_Update();
	}
}
