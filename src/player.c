#include "player.h"

#include "ducks.h"
#include "dog.h"
#include "menu.h"
#include "gfx/DUCKSPT.h"

struct player_t player;

/**
 * This function is used to control the player's cursor.
 */
bool player_keys(void)
{
	kb_key_t key = kb_Data[7];

	/* Updates the player timer for shooting recoil */
	if (player.timer < 60)
	{
		player.timer++;
	}

	kb_Scan();

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
 * this function is used to kill enemies in this case ducks.
 */
void shoot(void)
{
	gfx_sprite_t *back_buffer;

	if (player.timer < 50)
	{
		/* Return can't shoot just yet! */
		return;
	}
	for (int i = 0; i < enemies_amount; i++)
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

					/* Render the white shot rectangle */
					back_buffer = gfx_MallocSprite(20, 20);
					gfx_GetSprite(back_buffer, player.x - 10, player.y - 10);

					gfx_SetColor(1);
					gfx_FillRectangle(player.x - 10, player.y - 10, 20, 20);

					gfx_Blit(1);

					delay(10);

					gfx_Sprite(back_buffer, player.x - 10, player.y - 10);

					free(back_buffer);

					update_enemies();
				}
			}
		}
	}
}

/**
 * This function is used to draw the player's cursor.
 */
void draw_player(void)
{
	gfx_sprite_t *temp = gfx_MallocSprite(crosshair_width, crosshair_height);
	zx7_Decompress(temp, crosshair_compressed);

	gfx_TransparentSprite(temp, player.x - 12, player.y - 12);

	free(temp);
}