#include "dog.h"
#include "ducks.h"
#include "ui.h"
#include "utils.h"
#include "menu.h"
#include "gfx/DUCKSPT.h"

struct dog_t dog;

/**
 * Sets the dog animation type
 * (run to the center, jump over the grass, and peek when a duck has been shot)
 */
void dog_SetMode(uint8_t mode)
{
	dog.mode = mode;
	dog.speed = 1;
	dog.tick = 1;
	dog.animate = 0;
	dog.back_buffer = NULL;

	switch (mode)
	{
	case DOG_RUN_TO_CENTER:
		dog.x = 32;
		dog.y = 160;
		dog.cnum = 1;
		break;

	case DOG_PEEK_UP:
		if (menu.option == 1)
		{
			dog.cnum = 10;
		}
		else if (menu.option == 2)
		{
			dog.cnum = 11;
		}

		dog.y = 159;

		if (enemies[DUCK_FALLEN_ID].x > 231)
		{
			dog.x = 231;
		}
		else
		{
			dog.x = enemies[DUCK_FALLEN_ID].x;
		}

		dog.gotoY = dog.y - 30;

		break;

	case DOG_LAUGH:
		/* Set the costume to laugh */
		dog.cnum = 12;

		/* place the dog under the grass */
		dog.y = 159;

		/* Prepare to move via gotoY */
		dog.gotoY = dog.y - 30;

		/* Set the position of the dog in the center */
		dog.x = (LCD_WIDTH - dog_laugh_1_width) / 2;
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

	case 12:
		dog.cnum = 13;
		break;

	case 13:
		dog.cnum = 12;
		break;
	}
}

static void dog_animate(void)
{
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

	case 12:
		gfx_TransparentSprite(dog_laugh_1, dog.x, dog.y);
		break;

	case 13:
		gfx_TransparentSprite(dog_laugh_2, dog.x, dog.y);
		break;
	}

	if (dog.animate == TIMER_ANIMATE_MAX || dog.mode == DOG_LAUGH)
	{
		dog_manage_cnum();
	}
}

static void draw_back(void)
{
	gfx_sprite_t *temp = NULL;

	// tree
	temp = gfx_MallocSprite(bg_tree_width, bg_tree_height);
	zx7_Decompress(temp, bg_tree_compressed);
	gfx_TransparentSprite(temp, 44, 39);
	free(temp);

	// bush
	temp = gfx_MallocSprite(bg_bush_width, bg_bush_height);
	zx7_Decompress(temp, bg_bush_compressed);
	gfx_TransparentSprite(temp, 218, 132);
	free(temp);
}

static void draw_grass(void)
{
	gfx_sprite_t *temp = NULL;

	// Grass
	temp = gfx_MallocSprite(bg_ground_width, bg_ground_height);
	zx7_Decompress(temp, bg_ground_compressed);
	gfx_TransparentSprite(temp, 32, 156);
	free(temp);

	// bullet board
	temp = gfx_MallocSprite(bullet_board_width, bullet_board_height);
	zx7_Decompress(temp, bullet_board_compressed);
	gfx_TransparentSprite(temp, 52, 209);
	free(temp);

	// kill board
	temp = gfx_MallocSprite(kill_board_width, kill_board_height);
	zx7_Decompress(temp, kill_board_compressed);
	gfx_TransparentSprite(temp, 92, 209);
	free(temp);

	// score board
	temp = gfx_MallocSprite(score_board_width, score_board_height);
	zx7_Decompress(temp, score_board_compressed);
	gfx_TransparentSprite(temp, 220, 209);
	free(temp);

	// Print Score Board Information
	update_scene();
}

/**
 * Draws the dog based on the sprite number. (needs work)
 */
void dog_Render(void)
{
	if (dog.mode == DOG_PEEK_UP)
	{
		draw_back();
	}

	/* Draw the Sprite of the dog */
	dog_animate();

	if ((dog.mode == DOG_RUN_TO_CENTER && dog.tick == 3) || dog.mode == DOG_LAUGH)
	{
		/* Set the transparent color of the duck based on the player game mode (aka menu.option) */
		switch (menu.option)
		{
		case 1:
			gfx_SetTransparentColor(4);
			break;

		case 2:
			gfx_SetTransparentColor(5);
			break;
		}

		/* Render the grass block right after the duck  */
		// draw_dog_buffer_layer();
		if (dog.back_buffer != NULL)
			gfx_TransparentSprite(dog.back_buffer, dog.x - 10, dog.y - 10);

		/* reset transparent color */
		gfx_SetTransparentColor(0);
	}

	if (dog.mode == DOG_PEEK_UP)
	{
		draw_grass();
	}
}

/**
 * Updates the dog movements based on the dog mode.
 */
void dog_Update(void)
{
	switch (dog.mode)
	{
	case DOG_RUN_TO_CENTER:
		if (dog.tick == 1)
		{
			if (dog.x == 100 / 2)
			{
				dog.cnum = 5;
				dog.animate = TIMER_ANIMATE_MAX;
				for (int i = 0; i < 3; i++)
				{
					get_dog_buffer_layer();
					dog_Render();
					// ###############
					gfx_Blit(1);
					// ###############
					draw_dog_buffer_layer();
					delay(TIMER_ANIMATE_MAX * 50);
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
				dog.animate = TIMER_ANIMATE_MAX;
				for (int i = 0; i < 3; i++)
				{
					get_dog_buffer_layer();
					dog_Render();
					// ###############
					gfx_Blit(1);
					// ###############
					draw_dog_buffer_layer();
					delay(TIMER_ANIMATE_MAX * 50);
				}

				dog.cnum = 7;
				get_dog_buffer_layer();
				dog_Render();
				// ###############
				gfx_Blit(1);
				// ###############
				draw_dog_buffer_layer();
				delay(TIMER_ANIMATE_MAX * 50);
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
				dog.mode = DOG_HIDDEN;
		}

		break;

	case DOG_PEEK_UP:
	case DOG_LAUGH:
		/* Peek Up */
		if (dog.tick == 1)
		{
			/* Check if the code is equal to it final gotoY position */
			if (dog.y == dog.gotoY)
			{
				/* Animate the dog laughing  */
				if (dog.mode == DOG_LAUGH)
				{
					/* Check if you can still animate `issue # 4` */
					if (dog.animate < TIMER_ANIMATE_MAX)
						break;
				}

				dog.tick++;
				dog.gotoY = dog.y + 30;

				/* Pause when the dog reaches the top */
				if (dog.mode == DOG_PEEK_UP)
				{
					delay(TIMER_ANIMATE_MAX * 50);
				}
			}

			/* Different Speeds for dog modes */
			if (dog.mode == DOG_PEEK_UP) { 
				dog.y = Goto_Pos(dog.y, dog.gotoY, dog.speed + 2);
			} else { 
				dog.y = Goto_Pos(dog.y, dog.gotoY, dog.speed);
			}
			
		}

		/* Peek Down */
		if (dog.tick == 2)
		{
			if (dog.y == dog.gotoY)
				dog.mode = DOG_HIDDEN;

			dog.y = Goto_Pos(dog.y, dog.gotoY, dog.speed + 2);
		}
		break;
	}

	if (dog.animate < TIMER_ANIMATE_MAX)
	{
		dog.animate++;
	}
	else
	{
		dog.animate = 0;
	}
}

/**
 * Draws the dog jumping for the beginning of the game.
 */
void draw_dog_scene(void)
{
	do
	{
		get_dog_buffer_layer();
		dog_Render();

		// ###############
		gfx_Blit(1);
		// ###############

		draw_dog_buffer_layer();
		dog_Update();
	} while (dog.mode != DOG_HIDDEN);
}

void get_dog_buffer_layer(void)
{
	if (dog.back_buffer == NULL)
		dog.back_buffer = gfx_MallocSprite(70, 60);

	gfx_GetSprite(dog.back_buffer, dog.x - 10, dog.y - 10);
}

void draw_dog_buffer_layer(void)
{
	if (dog.back_buffer != NULL)
	{
		/* Render player back buffer*/
		gfx_Sprite(dog.back_buffer, dog.x - 10, dog.y - 10);

		/* Free the back buffer */
		free(dog.back_buffer);
	}

	dog.back_buffer = NULL;
}