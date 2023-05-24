#include "dog.h"
#include "ducks.h"
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
		break;

	case 2: // Jump over grass.
		dog.x = 80;
		dog.y = 160;
		break;

	case 3: // peek when duck is shot.
		dog.y = 159;
		if (enemies[fallen_id].x < 91)
		{
			dog.x = 91;
		}
		else if (enemies[fallen_id].x > 219)
		{
			dog.x = 219;
		}

		if (enemies[fallen_id].x < 91 && enemies[fallen_id].x > 219)
		{
			dog.x = 143;
		}
		dog.gotoY = dog.y - 20;
		break;
	}
}

/**
 * Draws the dog based on the sprite number. (needs work)
 */
void dog_Render(void)
{
	gfx_sprite_t *back_buff = gfx_MallocSprite(51, 43);
	gfx_GetSprite(back_buff, dog.x, dog.y);

	/* Pretend this is the dog */
	gfx_SetColor(0xFF);
	gfx_FillRectangle(dog.x, dog.y, 51, 43);

	gfx_Blit(1);
	gfx_Sprite(back_buff, dog.x, dog.y);
	free(back_buff);
}

/**
 * Updates the dog movements based on the dog mode.
 */
void dog_Update(void)
{
	switch (dog.mode)
	{
	case 1: // run to the center.
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
				dog.tick++;
		}

		// Go back down
		if (dog.tick == 2)
		{
			dog.gotoY = dog.y + 20;
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
