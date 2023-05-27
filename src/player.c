#include "player.h"
#include "ui.h"
#include "ducks.h"
#include "dog.h"
#include "menu.h"
#include "gfx/DUCKSPT.h"

struct player_t player;

/**
 * @brief Render reward if duck shot
 *
 * @param enemy_id index of enemy shot
 * @return int reward of duck
 */
static int returnReward(int enemy_id)
{
	int level;
	int rewards[][5] = {
		{500, 800, 1000, 1000, 1000},		 // Duck A
		{1000, 1600, 2000, 2000, 2000},		 // Duck B
		{1500, 2400, 3000, 3000, 3000},		 // Duck C
		{10000, 10000, 15000, 20000, 30000}, // Clay
	};

	/* Set level index */
	if (player.round >= 1 && player.round <= 5)
	{
		level = 0;
	}
	else if (player.round >= 6 && player.round <= 10)
	{
		level = 1;
	}
	else if (player.round >= 11 && player.round <= 15)
	{
		level = 2;
	}
	else if (player.round >= 16 && player.round <= 20)
	{
		level = 3;
	}
	else
	{
		level = 4;
	}

	/* Return the reward */
	return rewards[(enemies[enemy_id].type) - 1][level];
}

/**
 * @brief Renders shoot and checks if enemies have been shot
 *
 */
static void shoot(void)
{
	gfx_sprite_t *back_buffer;

	/* Return can't shoot just yet! */
	if (player.timer < TIMER_RECOIL_MAX)
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

	/* Check if ducks overlaps cursor  */
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
					enemies[i].shot = true;
					enemies[i].cnum = 7; // costume shot
					enemies[i].animate = 0;

					/* Determine Score */
					player.score += returnReward(i);

					/* Register Hit duck */
					game.duck_hits[get_duck_hits_amount()] = 1;

					DUCK_FALLEN_AMOUNT++;
					GAME_TOTAL_HITS++;
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

bool player_keys(void)
{
	kb_key_t key = kb_Data[7];

	kb_Scan();

	/* Updates the player timer for shooting recoil */
	if (player.timer < TIMER_RECOIL_MAX)
	{
		player.timer++;
	}

	/* Check for exit */
	if (kb_Data[1] == kb_Del)
		return 0;

	/* if there is nothing in dog.mode then user can mover the cursor. */

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

void draw_player(void)
{
	gfx_sprite_t *temp;

	/* Checks if the player has bullets */
	if (player.bullets > 0)
	{
		/* Render crosshair cursor */
		temp = gfx_MallocSprite(crosshair_width, crosshair_height);
		zx7_Decompress(temp, crosshair_compressed);

		gfx_TransparentSprite(temp, player.x - 12, player.y - 12);

		free(temp);
	}
}