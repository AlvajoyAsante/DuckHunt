/*
 *--------------------------------------
 * Program Name: DUCKHUNT
 * Author: Alvajoy 'Alvajoy123' Asante
 * License: GNU 3
 * Description: A NES clone of Duck Hunt
 *--------------------------------------
 */

#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <fileioc.h>

#include "ducks.h"
#include "dog.h"
#include "menu.h"
#include "ui.h"
#include "save.h"
#include "player.h"
#include "gfx/DUCKSPT.h"

int main(void)
{
	/* Seed Random */
	srand(rtc_Time());

	/* Check for the sprite appvar */
	if (!DUCKSPT_init())
	{
		os_ClrHome();
		os_PutStrFull("Missing 'DUCKSPT' File!");
		os_NewLine();
		os_PutStrFull("Press any key to exit.");
		while (!os_GetCSC())
			;
		goto end;
	}

	/* Loading Game Data */
	load_game();

	/* Begin Canvas */
	gfx_Begin();

	/* Canvas Setup */
	gfx_SetPalette(palette, sizeof_palette, 0);
	gfx_SetDrawBuffer();
	gfx_SetTransparentColor(0);
	gfx_SetTextFGColor(2); // black

menu:
	/* Render menu and check if user want to exit */
	if (!init_menu())
		goto end;

	/* Game play begins here */
	draw_scene();

	do
	{
		/* Grabbing Buffer Layer of the scene*/
		get_buffer_layer();

		/* Render layer */
		draw_enemies();
		draw_player();

		// #################

		gfx_Blit(1);

		// #################

		/* Updating layer */
		update_scene();
		draw_buffer_layer();
		update_enemies();
	} while (player_keys());

	delay(100);

	/* Saving Game Data */
	save_game();

	goto menu;

end:
	gfx_End();
	return 1;
}