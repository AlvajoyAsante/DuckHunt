#include "ui.h"
#include "ducks.h"
#include "menu.h"
#include "dog.h"
#include "player.h"
#include "gfx/DUCKSPT.h"

struct game_t game;

static void flyaway_scene(void)
{
	gfx_sprite_t *temp = gfx_MallocSprite(fly_away_width, fly_away_height);
	gfx_sprite_t *back_buff = gfx_MallocSprite(fly_away_width, fly_away_height);

	gfx_GetSprite(back_buff, 124, 103);

	zx7_Decompress(temp, fly_away_compressed);
	gfx_TransparentSprite(temp, 124, 103);
	free(temp);

	gfx_Blit(1);

	gfx_Sprite(back_buff, 124, 103);
	free(back_buff);
}

static void pause_scene(void)
{
	gfx_sprite_t *temp = gfx_MallocSprite(pause_width, pause_height);
	gfx_sprite_t *back_buff = gfx_MallocSprite(pause_width, pause_height);

	gfx_GetSprite(back_buff, 135, 88);

	/* Pretend this is the dog */
	/* gfx_SetColor(1); // White
	gfx_FillRectangle(135, 88, 49, 33); */

	zx7_Decompress(temp, pause_compressed);
	gfx_TransparentSprite(temp, 135, 88);
	free(temp);

	gfx_Blit(1);

	delay(60);

	while (!os_GetCSC())
		;

	delay(60);

	gfx_Sprite(back_buff, 135, 88);
	free(back_buff);
}

void update_scene(void)
{
	gfx_sprite_t *temp;

	gfx_SetColor(2); // Black
	gfx_FillRectangle(57, 212, 20, 7);

	// Draw Bullets
	for (int i = 0; i < player.bullets; i++)
	{
		temp = gfx_MallocSprite(bullet_width, bullet_height);
		zx7_Decompress(temp, bullet_compressed);
		gfx_TransparentSprite(temp, 57 + (i * (4 + 4)), 212);
		free(temp);
	}

	/* Hit Panel */

	temp = gfx_MallocSprite(panel_icon_1_width, panel_icon_1_height);

	for (int i = 0; i < 10; i++)
	{
		if (menu.option < 3)
		{
			if (game.duck_hits[i])
			{
				zx7_Decompress(temp, panel_icon_2_compressed);
			}
			else
			{
				zx7_Decompress(temp, panel_icon_1_compressed);
			}

			gfx_TransparentSprite(temp, 127 + (i * (panel_icon_1_width + 1)), 213);

			/* Blinking */
			if (dog.mode != DOG_RUN_TO_CENTER && game.start == true)
			{
				if (get_duck_hits_amount() == i)
				{
					if (randInt(0, 1))
					{
						gfx_SetColor(2);
						gfx_FillRectangle(127 + (i * (8)), 213, 7, 7);
					}
				}
			}
		}
		else
		{
			if (game.duck_hits[i])
			{
				// zx7_Decompress(temp, panel_icon_2_compressed);
				gfx_SetColor(16);
			}
			else
			{
				// zx7_Decompress(temp, panel_icon_1_compressed);
				gfx_SetColor(1);
			}

			gfx_FillRectangle(127 + (i * (panel_icon_1_width + 1)), 213, 7, 7);

			if (game.start == true)
			{
				if (get_duck_hits_amount() == i)
				{
					if (randInt(0, 1))
					{
						gfx_SetColor(2);
						gfx_FillRectangle(127 + (i * (8)), 213, 7, 7);
					}
				}
			}
		}
	}

	free(temp);

	/* Advanced amount */
	if (player.round >= 1 && player.round <= 10)
	{
		GAME_ADVANCE_THRESHOLD = 6;
	}
	else if (player.round >= 11 && player.round <= 12)
	{
		GAME_ADVANCE_THRESHOLD = 7;
	}
	else if (player.round >= 13 && player.round <= 14)
	{
		GAME_ADVANCE_THRESHOLD = 8;
	}
	else if (player.round >= 15 && player.round <= 19)
	{
		GAME_ADVANCE_THRESHOLD = 9;
	}
	else
	{
		GAME_ADVANCE_THRESHOLD = 10;
	}

	// gfx_SetColor(6);

	temp = gfx_MallocSprite(panel_icon_3_width, panel_icon_3_height);
	zx7_Decompress(temp, panel_icon_3_compressed);

	for (int i = 0; i < GAME_ADVANCE_THRESHOLD; i++)
	{
		gfx_TransparentSprite(temp, 127 + (i * (panel_icon_3_width + 1)), 221);
		// gfx_FillRectangle(127 + (i * (7 + 1)), 221, 7, 7);
	}

	free(temp);

	// Draw Score

	/* Fill the area up */
	gfx_SetColor(2); // Black
	gfx_FillRectangle(223, 211, 47, 8);

	/* Print the Score */
	gfx_SetTextFGColor(1);
	gfx_SetTextXY(223, 211);
	gfx_PrintInt(player.score, 6);

	// Draw Round

	/* gfx_SetColor(2); // Black
	gfx_FillRectangle(253, 11, 32, 8); */

	gfx_SetTextFGColor(16);
	gfx_SetTextBGColor(2);
	gfx_SetTextXY(253, 11);
	gfx_PrintString("R=");
	gfx_PrintInt(player.round, 0);

	if (menu.option < 3)
	{
		if (player.bullets == 0)
		{
			// Check if there are any birds on scene
			if (DUCK_FALLEN_AMOUNT != DUCK_AMOUNT)
			{
				flyaway_scene();
			}
		}
	}
	else
	{
	}

	if (kb_Data[1] == kb_Mode)
	{
		pause_scene();
	}
}

static int count_digits(int number)
{
	int count = 0;
	while (number > 0)
	{
		number /= 10;
		count++;
	}
	return count;
}

/**
 * This is used to draw the scene for the game.
 * It depends on the me variable (menu.option).
 */
void draw_scene(void)
{
	gfx_sprite_t *back_buffer, *temp;

	game.start = false;

	gfx_FillScreen(2); // BLACK

	gfx_SetColor(1); // WHITE
	gfx_Rectangle(31, 7, 258, 225);

	// Renders Sky
	switch (menu.option)
	{
	case 1:
		gfx_SetColor(4);
		gfx_FillRectangle(32, 8, 256, 223);
		break;

	case 2:
		gfx_SetColor(5);
		gfx_FillRectangle(32, 8, 256, 223);
		break;

	case 3:
		gfx_SetColor(3);
		gfx_FillRectangle(32, 8, 256, 223);
		break;
	}

	if (menu.option < 3)
	{ // Game A & Game B
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

		// ground
		gfx_SetColor(6);
		gfx_FillRectangle(32, 190, 256, 41);

		temp = gfx_MallocSprite(bg_ground_width, bg_ground_height);
		zx7_Decompress(temp, bg_ground_compressed);
		gfx_TransparentSprite(temp, 32, 156);
		free(temp);

		back_buffer = gfx_MallocSprite(1, bg_ground_height);
		gfx_GetSprite(back_buffer, 286, 156);
		gfx_Sprite(back_buffer, 287, 156);
		free(back_buffer);

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

		// Print Round Number
		gfx_sprite_t *back_buff = gfx_MallocSprite(fly_away_width, fly_away_height * 2);

		gfx_GetSprite(back_buff, (LCD_WIDTH - fly_away_width) / 2, 103);

		ui_rectangle((LCD_WIDTH - fly_away_width) / 2, 103, fly_away_width, fly_away_height * 2);

		gfx_SetTextFGColor(1);
		gfx_SetTextXY((LCD_WIDTH - gfx_GetStringWidth("ROUND")) / 2, 110);
		gfx_PrintString("ROUND");

		gfx_SetTextXY((LCD_WIDTH - (8 * count_digits(player.round))) / 2, 123);
		gfx_PrintInt(player.round, 0);

		gfx_Blit(1);

		delay(1000);

		/* Print round number back buffer */
		gfx_Sprite(back_buff, (LCD_WIDTH - fly_away_width) / 2, 103);
		free(back_buff);

		// Render dog
		dog_SetMode(DOG_RUN_TO_CENTER);
		draw_dog_scene();
	}
	else
	{ // Game C

		temp = gfx_MallocSprite(c_mountain_width, c_mountain_height);
		zx7_Decompress(temp, c_mountain_compressed);
		gfx_TransparentSprite(temp, 32, 95);
		free(temp);

		temp = gfx_MallocSprite(c_ground_width, c_ground_height);
		zx7_Decompress(temp, c_ground_compressed);
		gfx_TransparentSprite(temp, 32, 140);
		free(temp);

		gfx_SetColor(16); // Green
		gfx_FillRectangle(32, 183, c_panel_width, c_panel_height);

		temp = gfx_MallocSprite(c_panel_width, c_panel_height);
		zx7_Decompress(temp, c_panel_compressed);
		gfx_TransparentSprite(temp, 32, 183);
		free(temp);

		back_buffer = gfx_MallocSprite(1, c_panel_height + c_ground_height + c_mountain_height);
		gfx_GetSprite(back_buffer, 286, 95);
		gfx_Sprite(back_buffer, 287, 95);
		free(back_buffer);

		gfx_SetColor(7); // Gray
		gfx_FillRectangle(32, 191, 256, 40);

		// bullet board
		temp = gfx_MallocSprite(bullet_board_width, bullet_board_height);
		zx7_Decompress(temp, bullet_board_compressed);
		gfx_TransparentSprite(temp, 52, 201);
		free(temp);

		// kill board
		temp = gfx_MallocSprite(kill_board_width, kill_board_height);
		zx7_Decompress(temp, kill_board_compressed);
		gfx_TransparentSprite(temp, 92, 201);
		free(temp);

		// score board
		temp = gfx_MallocSprite(score_board_width, score_board_height);
		zx7_Decompress(temp, score_board_compressed);
		gfx_TransparentSprite(temp, 220, 201);
		free(temp);

		// Print Score Board Information
		update_scene();
	}

	game.start = true;

	gfx_Blit(1);
}

/**
 * This is used to innit the game and setup and variables.
 */
void init_duckhunt(void)
{
	/* Initialize the player position */
	player.x = 320 / 2;
	player.y = 240 / 2;
	player.score = 0;
	player.speed = 5;
	player.level = 1;
	player.round = 1;
	player.bullets = 3;

	/* HUD setup */
	reset_duck_hits();

	/* Dog setup */
	dog_SetMode(DOG_HIDDEN);

	/* Setup the enemies */
	DUCK_FALLEN_AMOUNT = 0;
	GAME_TOTAL_HITS = 0;

	switch (menu.option)
	{
	case 1:
		init_enemies(1);
		break;

	case 2:
	case 3:
		init_enemies(2);
		break;
	}
}

void reset_duck_hits(void)
{
	for (int i = 0; i < 10; i++)
		game.duck_hits[i] = 0;
}

int get_duck_hits_amount(void)
{
	int tick = 0;

	for (int i = 0; i < 10; i++)
	{
		if (game.duck_hits[i] == 1)
		{
			tick++;
		}
	}

	return tick;
}

// New functions to help with rendering.
/**
 * This function grabs buffer sprite.
 */
void get_buffer_layer(void)
{
	/* Allocate space for back buffer */
	player.back_buffer = gfx_MallocSprite(crosshair_width, crosshair_height);

	/* Grab player back buffer */
	gfx_GetSprite(player.back_buffer, player.x - 12, player.y - 12);

	for (int i = 0; i < DUCK_AMOUNT; i++)
	{
		/* Allocate space for back buffer */
		enemies[i].back_buffer = gfx_MallocSprite(38, 38);

		/* Grab duck back buffer */
		gfx_GetSprite(enemies[i].back_buffer, enemies[i].x - 1, enemies[i].y - 1);
	}
}

/**
 * @brief Free the sprite from buffers
 *
 */
static void free_buffer_layer(void)
{
	/* Free player back buffer */
	free(player.back_buffer);

	/* Free duck back buffer */
	for (int i = 0; i < DUCK_AMOUNT; i++)
	{
		free(enemies[i].back_buffer);
	}
}

/**
 * This draws any sprite buffered from "get_buffer_layer"
 */
void draw_buffer_layer(void)
{
	/* Render player back buffer*/
	gfx_Sprite(player.back_buffer, player.x - 12, player.y - 12);

	/* Render duck back buffer */
	draw_duck_buffer_layer();

	free_buffer_layer();
}

void draw_duck_buffer_layer(void)
{
	for (int i = 0; i < DUCK_AMOUNT; i++)
	{
		gfx_TransparentSprite(enemies[i].back_buffer, enemies[i].x - 1, enemies[i].y - 1);
	}
}

void ui_rectangle(int x, int y, int w, int h)
{
	gfx_SetColor(16);
	for (int i = 0; i < w; i++)
	{
		if (i == 0 || i == w - 1)
		{
			gfx_VertLine(x + i, y + 1, h - 2);
		}
		else
			gfx_VertLine(x + i, y, h);
	}

	gfx_SetColor(2);

	x++;
	y++;
	w -= 2;
	h -= 2;
	for (int i = 0; i < w; i++)
	{
		if (i == 0 || i == w - 1)
		{
			gfx_VertLine(x + i, y + 1, h - 2);
		}
		else
			gfx_VertLine(x + i, y, h);
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
int Goto_Pos(int start, int end, uint8_t speed)
{
	/* Checks if the start position does not eqaul to the desitionation position */
	if (start != end)
	{
		/* Checks if the postion is speed distance */
		if (start - end <= speed && start - end >= -(speed))
			return end;

		/* Checks if the position is less than the destination position */
		if (start < end)
		{
			start += speed;
		}
		else if (start > end) // Checks if the position is greater than position.
		{
			start -= speed;
		}

		return start;
	}
	else
	{
		return start;
	}
}