#include "player.h"
#include "ui.h"
#include "ducks.h"
#include "dog.h"
#include "menu.h"
#include "gfx/DUCKSPT.h"

struct player_t player;

static int returnReward(int pos)
{
	int rewards[][5] = {
		{500, 800, 1000, 1000, 1000},		 // Duck A
		{1000, 1600, 2000, 2000, 2000},		 // Duck B
		{1500, 2400, 3000, 3000, 3000},		 // Duck C
		{10000, 10000, 15000, 20000, 30000}, // Clay
	};

	int level;

	/* Set level index */
	if (player.level >= 1 && player.level <= 5)
	{
		level = 0;
	}
	else if (player.level >= 6 && player.level <= 10)
	{
		level = 1;
	}
	else if (player.level >= 11 && player.level <= 15)
	{
		level = 2;
	}
	else if (player.level >= 16 && player.level <= 20)
	{
		level = 3;
	}
	else
	{
		level = 4;
	}

	/* Return the reward */
	return rewards[(enemies[pos].type) - 1][level];
}

/**
 * this function is used to kill enemies in this case ducks.
 */
static void shoot(void)
{
	gfx_sprite_t *back_buffer;

	/* Return can't shoot just yet! */
	if (player.timer < 30)
		return;

	/* Check if there is bullets to shoot */
	if (player.bullets > 0)
	{
		player.bullets--;
	}
	else
	{
		return;
	}

	for (int i = 0; i < DUCK_AMOUNT; i++)
	{

		if (enemies[i].active && !enemies[i].shot)
		{
			/* Reset the shooting timer */
			player.timer = 0;

			if (enemies[i].x < (player.x - 5) + 10 && enemies[i].x + 33 > player.x - 5)
			{
				if (enemies[i].y < (player.y - 5) + 10 && enemies[i].y + 23 > player.y - 5)
				{

					/* Prime the duck for shooting */
					enemies[i].angle = 0;
					enemies[i].gotoY = 140;
					enemies[i].gotoX = enemies[i].x;
					enemies[i].speed = 4;
					enemies[i].shot = 1;
					enemies[i].cnum = 7; // shot
					enemies[i].animate = ANIMATE_TIMER_MAX;

					/* Determine Score */
					player.score += returnReward(i);

					/* Register Hit duck */
					game.duck_hits[GAME_TOTAL_HITS + i] = 1;
					
					DUCK_FALLEN_AMOUNT++;
					

					update_enemies();

					
				}
			}
		}
	}

	/* Render the white shot rectangle */
	back_buffer = gfx_MallocSprite(20, 20);
	gfx_GetSprite(back_buffer, player.x - 10, player.y - 10);

	gfx_SetColor(1);
	gfx_FillRectangle(player.x - 10, player.y - 10, 20, 20);

	gfx_Blit(1);

	delay(30);

	gfx_Sprite(back_buffer, player.x - 10, player.y - 10);

	free(back_buffer);
}

/**
 * This function is used to control the player's cursor.
 */
bool player_keys(void)
{
	kb_key_t key = kb_Data[7];

	kb_Scan();

	/* Updates the player timer for shooting recoil */
	if (player.timer < 50)
	{
		player.timer++;
	}

	/* Check for exit */
	if (kb_Data[6] == kb_Clear)
		return 0;

	/* if there is nothing in dog.mode then user can mover the cusor. */

	if (kb_Data[1] == kb_2nd)
	{
		shoot();
		return 1;
	}

	switch (key)
	{
	case kb_Up:
		if (player.y - player.speed >= 16)
		{
			player.y -= player.speed;
		}
		else
		{
			player.y = 16;
		}
		break;

	case kb_Down:
		if (player.y + player.speed <= 155)
		{
			player.y += player.speed;
		}
		else
		{
			player.y = 155;
		}
		break;

	case kb_Left:
		if (player.x - player.speed >= 40)
		{
			player.x -= player.speed;
		}
		else
		{
			player.x = 40;
		}
		break;

	case kb_Right:
		if (player.x + player.speed <= 279)
		{
			player.x += player.speed;
		}
		else
		{
			player.x = 279;
		}
		break;
	}

	if (kb_IsDown(kb_KeyUp) && kb_IsDown(kb_KeyRight))
	{
		if (player.y - player.speed >= 16)
		{
			player.y -= player.speed;
		}
		else
			player.y = 16;

		if (player.x + player.speed <= 279)
		{
			player.x += player.speed;
		}
		else
			player.x = 279;

		return 1;
	}

	if (kb_IsDown(kb_KeyUp) && kb_IsDown(kb_KeyLeft))
	{
		if (player.y - player.speed >= 16)
		{
			player.y -= player.speed;
		}
		else
			player.y = 16;

		if (player.x - player.speed >= 40)
		{
			player.x -= player.speed;
		}
		else
			player.x = 40;

		return 1;
	}

	if (kb_IsDown(kb_KeyDown) && kb_IsDown(kb_KeyRight))
	{
		if (player.y + player.speed <= 155)
		{
			player.y += player.speed;
		}
		else
			player.y = 155;

		if (player.x + player.speed <= 279)
		{
			player.x += player.speed;
		}
		else
			player.x = 279;

		return 1;
	}

	if (kb_IsDown(kb_KeyDown) && kb_IsDown(kb_KeyLeft))
	{
		if (player.y + player.speed <= 155)
		{
			player.y += player.speed;
		}
		else
			player.y = 155;

		if (player.x - player.speed >= 40)
		{
			player.x -= player.speed;
		}
		else
			player.x = 40;

		return 1;
	}

	return 1;
}

/**
 * This function is used to draw the player's cursor.
 */
void draw_player(void)
{

	gfx_sprite_t *temp;

	if (player.bullets > 0)
	{
		temp = gfx_MallocSprite(crosshair_width, crosshair_height);
		zx7_Decompress(temp, crosshair_compressed);

		gfx_TransparentSprite(temp, player.x - 12, player.y - 12);

		free(temp);
	}
}