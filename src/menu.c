#include "menu.h"
#include "ui.h"
#include "gfx/DUCKSPT.h"

#include <graphx.h>
#include <keypadc.h>
#include <compression.h>

struct menu_t menu;

bool init_menu(void)
{
	gfx_sprite_t *temp_sprite;
	sk_key_t key;


	/* Setting up menu GUI */
	gfx_FillScreen(2); // Black

	menu.opt = 1;

	/* Render Game Title */
	temp_sprite = gfx_MallocSprite(Title_Menu_width, Title_Menu_height);
	zx7_Decompress(temp_sprite, Title_Menu_compressed);
	gfx_TransparentSprite(temp_sprite, 86, 32);
	free(temp_sprite);

	/* Render Game Modes */
	gfx_SetTextFGColor(6); // Orange
	gfx_SetTextXY(89, 133);
	gfx_PrintString("GAME  A     1  DUCK");
	gfx_SetTextXY(89, 149);
	gfx_PrintString("GAME  B     2  DUCK");
	gfx_SetTextXY(89, 164);
	gfx_PrintString("GAME  C     CLAY  SHOOTING");

	/* Render Highscore */
	gfx_SetTextFGColor(16); // Green
	gfx_SetTextXY(85, 190);
	gfx_PrintString("TOP  SCORE  =  ");
	gfx_PrintInt(game.high_score, 5);

	/* Render Nintendo Copyright */
	temp_sprite = gfx_MallocSprite(cr_symbol_width, cr_symbol_height);
	zx7_Decompress(temp_sprite, cr_symbol_compressed);
	gfx_TransparentSprite(temp_sprite, (LCD_WIDTH - (gfx_GetStringWidth(COPYRIGHT_TEXT) + cr_symbol_width)) / 2, 213);
	free(temp_sprite);

	gfx_SetTextScale(1, 1);
	gfx_SetTextFGColor(1); // White
	gfx_SetTextXY((LCD_WIDTH - (gfx_GetStringWidth(COPYRIGHT_TEXT) - (cr_symbol_width + 4))) / 2, 214);
	gfx_PrintString(COPYRIGHT_TEXT);

	/* Render Version Number */
	gfx_SetTextScale(1, 1);
	gfx_SetTextFGColor(1); // White
	gfx_SetTextXY((LCD_WIDTH - gfx_GetStringWidth(DUCKHUNT_VERSION)) / 2, 228);
	gfx_PrintString(DUCKHUNT_VERSION);

	/* Decompress Cursor */
	temp_sprite = gfx_MallocSprite(menu_arrow_width, menu_arrow_height);
	zx7_Decompress(temp_sprite, menu_arrow_compressed);

	/* Loop to manage user input */
	while (1)
	{
		/* Clear cursor position */
		gfx_SetColor(2); // black
		gfx_FillRectangle(60, 130, 14, 43);

		/* Scan and manage keys */
		kb_Scan();
		key = kb_Data[7];

		switch (key)
		{
		case kb_Up:
			if (menu.opt > 1)
			{
				menu.opt--;
			}

			delay(65);
			break;

		case kb_Down:
			if (menu.opt < 3)
			{
				menu.opt++;
			}

			delay(65);
			break;
		}

		/* Check if [2nd], [Enter] was clicked */
		if (kb_Data[1] == kb_2nd || kb_Data[6] == kb_Enter)
			break;

		/* Check if user wants to exit */
		if (kb_Data[1] == kb_Del)
		{
			free(temp_sprite);
			delay(60);

			/* Return false if user does not want to play */
			return false;
		}

		/* Render arrow sprite based on menu position */
		switch (menu.opt)
		{
		case 1:
			gfx_TransparentSprite(temp_sprite, 61, 131);
			break;

		case 2:
			gfx_TransparentSprite(temp_sprite, 61, 145);
			break;

		case 3:
			gfx_TransparentSprite(temp_sprite, 61, 161);
			break;
		}

		// ################

		gfx_Blit(1);

		// ###############
	}

	/* Free the temp sprite used for rendering */
	free(temp_sprite);

	/* Start the game based on menu option */
	init_duckhunt(menu.opt);

	/* Return true if use want to play*/
	return true;
}
