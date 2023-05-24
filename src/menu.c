#include "menu.h"
#include "ui.h"
#include "gfx/DUCKSPT.h"

#include <graphx.h>
#include <keypadc.h>
#include <compression.h>

struct menu_t menu;

/**
 * This function is used to control the menu cursor.
 */
static void menu_keys(sk_key_t key)
{
	switch (key)
	{
	case kb_Up:
		if (menu.opt > 1)
			menu.opt--;
		break;

	case kb_Down:
		if (menu.opt < 3)
			menu.opt++;
		break;
	}

	delay(60);
}

bool init_menu(void)
{
	sk_key_t key;
	gfx_sprite_t *temp_sprite;

	gfx_FillScreen(2); // black
	gfx_SetColor(0);

	menu.opt = 1;

	temp_sprite = gfx_MallocSprite(Title_Menu_width, Title_Menu_height);
	zx7_Decompress(temp_sprite, Title_Menu_compressed);
	gfx_TransparentSprite(temp_sprite, 86, 32);

	// Render the game modes text
	temp_sprite = gfx_MallocSprite(game_types_width, game_types_height);
	zx7_Decompress(temp_sprite, game_types_compressed);
	gfx_TransparentSprite(temp_sprite, 89, 132);

	// Render the game modes
	temp_sprite = gfx_MallocSprite(game_type_text_width, game_type_text_height);
	zx7_Decompress(temp_sprite, game_type_text_compressed);
	gfx_TransparentSprite(temp_sprite, 168, 132);

	// Renders nintendo text
	temp_sprite = gfx_MallocSprite(cr_text_width, cr_text_height);
	zx7_Decompress(temp_sprite, cr_text_compressed);
	gfx_TransparentSprite(temp_sprite, (LCD_WIDTH - cr_text_width) / 2, 214);

	// Show version of program
	show_ver();

	gfx_SetTextFGColor(9); // Green
	gfx_SetTextXY(85, 190);
	gfx_PrintString("TOP  SCORE  =  ");
	gfx_PrintInt(0, 5);

	gfx_SetTextFGColor(1); // White
	gfx_SetTextXY(100, 228);
	gfx_PrintString("Port by Alvajoy123");

	temp_sprite = gfx_MallocSprite(menu_arrow_width, menu_arrow_height);
	zx7_Decompress(temp_sprite, menu_arrow_compressed);

	do
	{
		gfx_SetColor(2); // black
		gfx_FillRectangle(60, 130, 14, 43);

		// keys
		kb_Scan();

		/* Check arrows keys */
		key = kb_Data[7];
		menu_keys(key);

		/* Check if 2nd / Enter was clicked */
		if (kb_Data[1] == kb_2nd || kb_Data[6] == kb_Enter)
			break;

		/* Check if user wants to exit */
		if (kb_Data[6] == kb_Clear)
		{
			free(temp_sprite);
			delay(60);
			return 0;
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

		gfx_Blit(1);
	} while (1);

	/* Free the temp sprite used for rendering */
	free(temp_sprite);

	/* Start the game based on menu option */
	init_duckhunt(menu.opt);
	return 1;
}
