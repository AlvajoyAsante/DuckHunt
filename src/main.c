/*
 *--------------------------------------
 * Program Name: DUCKHUNT
 * Author: Alvajoy 'Alvajoy Asante' 123
 * License: GNU 3
 * Description: A CLONE OF POPULAR NES GAME "DUCKHUNT".
 * Notes: "Please ask for permission before any use of Authors code"
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
#include "player.h"
#include "gfx/DUCKSPT.h"

int main(void)
{
	srand(rtc_Time());
	// Checks for Sprite app var and if not detected it returns quickly.
	if (DUCKSPT_init() == 0)
		return 1;

	gfx_Begin();

	// Sets the custom palette of the sprite appvar
	gfx_SetPalette(palette, sizeof_palette, 0);

	gfx_SetDrawBuffer();

	gfx_SetTransparentColor(0); // Hot pink color
	gfx_SetTextFGColor(2);		// black

menu:

	if (!init_menu())
		goto end; // If there was a force exit while on menu it will exit.

	/* Game play begins here */
	draw_scene(); // Draws Scene for the game mode

	// Draw dog scene here
	draw_dog_scene();

	while (player_keys())
	{
		get_buffer_layer();

		draw_enemies();
		draw_player();

		gfx_Blit(1);

		update_scene();

		draw_buffer_layer();

		update_enemies();
	}

	delay(100);

	goto menu;

end:
	gfx_End();
	return 1;
}