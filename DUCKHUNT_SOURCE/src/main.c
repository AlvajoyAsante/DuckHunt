//By: Alvajoy"Alvajoy"123 

// Keep these headers
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

// Standard headers
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Graphic libs
#include <graphx.h>
#include <keypadc.h>

// my headers
// #include "main.h"
#include "gfx/DUCKSPT.h"


// Variables
struct player_t{
	int x;
	int y;
	int score;
	int speed;
	int bullets;
} player;

struct enemies_t{
	bool active; // is bird dead / alive or not active.
	bool shot;
	int x;
	int y;
	int speed; // predetemind based on  level
	// for flying
	int gotoX;
	int gotoY; 
	int cnum; // costum number
	int angle; // determines sptites
} enemies[10];

struct dog_t{ //dog
	int x;
	int y;
	int gotoX;
	int gotoY;
	int speed;
	int mode;
	int cnum;
} dog;

int ext;
int fallen_id;
int enemies_amount;
kb_key_t key;
int i;
int timers[10];
int amount_fallen, lvl;
gfx_UninitedSprite(sprite_buff, 70, 70);

// Functions
void draw_player(void);
void player_keys(void);
void vars_int(void);
void Debug(void);
void player_keys_other(void);
void draw_scene(void);
void draw_enemies(void);
void shoot(void);
void init_enemies(int amount, int level);
void SetCostume(int pos, int num);
void animate(int pos);
void animate_sprites (int pos);
void set_dog_mode(int pos);
void draw_dog(void);

void main(void){
	// DUCKSPT_init(); // Setup Sprites
	
	gfx_SetPalette(palette, sizeof_palette, 0);
	
	gfx_Begin();
	gfx_SetDraw(1);
	gfx_SetTransparentColor(0xF0);
	
	// var init
	vars_int();
	
	gfx_SetTextFGColor(0);
	
	gfx_FillScreen(0);
	gfx_SetColor(255);
	gfx_Rectangle(31, 7, 258, 225);
	
	while (!ext){
		kb_Scan();
		key = kb_Data[7];
		
		
		
		player_keys();
		gfx_SetColor(0x10);
		gfx_FillRectangle(32, 8, 256, 223);
		
		draw_enemies();
		draw_scene();
		// if (dog.mode <= 3 && dog.mode >= 1) draw_dog();
		Debug();
		draw_player();
		
		gfx_Blit(1);
	}
	free(sprite_buff);
	gfx_Blit(1);
	gfx_End();
} 

void SetCostume(int pos, int num){
	enemies[pos].cnum = num;
}

void animate(int pos){	
	switch (enemies[pos].cnum){
		case 1:
			enemies[pos].cnum = 2;
			break;
			
		case 2:
			enemies[pos].cnum = 3;
			break;
			
		case 3:
			enemies[pos].cnum = 1;
			goto angle;
			break;
			
		case 4:
			enemies[pos].cnum = 5;
			break;
			
		case 5:
			enemies[pos].cnum = 6;
			break;
			
		case 6:
			enemies[pos].cnum = 4;
			goto angle;
			break;
			
		case 7:
			if (timers[pos] >= 10) enemies[pos].cnum = 8;
			break;
		
		case 8:
			enemies[pos].cnum = 9;
			break;
			
		case 9:
			enemies[pos].cnum = 8;
			// goto angle;
			break;
	}
	
	return;
	
angle:
	if (enemies[pos].angle == 1 || enemies[pos].angle == 2){
		SetCostume(pos, 1);
		return;
	}
	
	if (enemies[pos].angle == 3 || enemies[pos].angle == 4){
		SetCostume(pos, 4);
		return;
	}
	
	if (enemies[pos].angle == 0){
		SetCostume(pos, 7);
		return;
	}
	
	return;
}

void animate_sprites(int pos){
	animate(pos);
	
	switch (enemies[pos].cnum){
		case 1:
			if (enemies[i].angle == 2){
				gfx_FlipSpriteY(Duck_A_1, sprite_buff);
				gfx_TransparentSprite(sprite_buff, enemies[i].x, enemies[i].y);
			}else gfx_TransparentSprite(Duck_A_1, enemies[i].x, enemies[i].y);
			break;
			
		case 2:
			if (enemies[i].angle == 2){
				gfx_FlipSpriteY(Duck_A_2, sprite_buff);
				gfx_TransparentSprite(sprite_buff, enemies[i].x, enemies[i].y);
			}else gfx_TransparentSprite(Duck_A_2, enemies[i].x, enemies[i].y);
			break;
			
		case 3:
			if (enemies[i].angle == 2){
				gfx_FlipSpriteY(Duck_A_3, sprite_buff);
				gfx_TransparentSprite(sprite_buff, enemies[i].x, enemies[i].y);
			}else gfx_TransparentSprite(Duck_A_3, enemies[i].x, enemies[i].y);
			break;
			
		case 4:
			if (enemies[i].angle == 4){
				gfx_FlipSpriteY(Duck_B_1, sprite_buff);
				gfx_TransparentSprite(sprite_buff, enemies[i].x, enemies[i].y);
			}else gfx_TransparentSprite(Duck_B_1, enemies[i].x, enemies[i].y);
			break;
			
		case 5:
			if (enemies[i].angle == 4){
				gfx_FlipSpriteY(Duck_B_2, sprite_buff);
				gfx_TransparentSprite(sprite_buff, enemies[i].x, enemies[i].y);
			}else gfx_TransparentSprite(Duck_B_2, enemies[i].x, enemies[i].y);
			break;
			
		case 6:
			if (enemies[i].angle == 4){
				gfx_FlipSpriteY(Duck_B_3, sprite_buff);
				gfx_TransparentSprite(sprite_buff, enemies[i].x, enemies[i].y);
			}else gfx_TransparentSprite(Duck_B_3, enemies[i].x, enemies[i].y);
			break;
			
		case 7:
			gfx_TransparentSprite(Duck_Shot, enemies[i].x, enemies[i].y);
			break;
			
		case 8:
			gfx_TransparentSprite(Duck_Fall_1, enemies[i].x, enemies[i].y);
			break;
			
		case 9:
			gfx_TransparentSprite(Duck_Fall_2, enemies[i].x, enemies[i].y);
			break;
	}
	delay(1);
	return;
}

void set_dog_mode(int pos){
	dog.mode = pos;
	switch(dog.mode){
		case 1:
			if (dog.x != dog.gotoX || dog.y != dog.gotoY) return;
			
			if (dog.x == 141 && dog.y == 189){
				dog.gotoY = dog.y + 50;
				// set_dog_mode(0);
				return;
			}
			
			if (dog.x == 101 && dog.y == 139){
				dog.gotoX = 141;
				dog.gotoY = 189;
				return;
			}
			
			if (dog.x == 91 && dog.y == 160){
				dog.gotoX = 101;
				dog.gotoY = 140;
				return;
			}
			
			dog.x = 32;
			dog.y = 160;
			dog.gotoY = 160;
			dog.gotoX = 91;
		
		break;
		
		case 2:
			dog.x = 80;
			dog.y = 160;
		break;
		
		case 3:
			dog.y = 159;
			if (enemies[fallen_id].x < 91){
				dog.x = 91;
			}else if (enemies[fallen_id].x > 219){
				dog.x = 219;
			}
			
			if (enemies[fallen_id].x < 91 && enemies[fallen_id].x > 219){
				dog.x = 143;
			}
			dog.gotoY = dog.y - 20;
		break;
	}
	
	return;
}

void draw_dog(void){
	if (!dog.mode) return;
	switch (dog.mode){
		case 1: // full run to center
			if (dog.x != dog.gotoX){
				
				if (dog.x < dog.gotoX){
					dog.x += dog.speed;
				}else if (dog.x > dog.gotoX){
					dog.x -= dog.speed;
				}
				
			
			}else set_dog_mode(1);
			
			if (dog.y != dog.gotoY){
				
				if (dog.y < dog.gotoY){
					dog.y += dog.speed;
				}else if (dog.y > dog.gotoY){
					dog.y -= dog.speed;
				}
							
			}else set_dog_mode(1);
			
			break;
		
		case 2: // half run to center
		
			break;
		
		case 3: // peek up after bird shot!!
		
			break;
	}
	
	gfx_SetColor(224);
	gfx_FillRectangle(dog.x, dog.y, 51,43);
}

void shoot(void){
	for (i = 0; i < enemies_amount; i++){
		if (!enemies[i].shot){
			if (enemies[i].x < (player.x - 5) + 10 && enemies[i].x + 33 > player.x - 5){
				if (enemies[i].y < (player.y - 5) + 10 && enemies[i].y + 23 > player.y - 5 ){
					enemies[i].angle = 0;
					enemies[i].gotoY = 180;
					enemies[i].gotoX = enemies[i].x;
					enemies[i].speed = 3;
					enemies[i].shot = 1;
					timers[i] = 0;
					
					gfx_SetColor(255);
					gfx_FillRectangle(player.x - 10, player.y - 10, 20, 20);
					
					gfx_Blit(1);
					return;
				}
			}
		}
	}
	return;
}

void draw_scene(void){
	gfx_SetColor(5);
	gfx_FillRectangle(32, 156, 256, 34);

	gfx_SetColor(7);
	gfx_FillRectangle(32, 190, 256, 41);
}

void draw_enemies(void){
	if (dog.mode <= 2 && dog.mode >= 1) return;
	
	for (i = 0; i < enemies_amount; i++){
		if (enemies[i].active){
			
			if (enemies[i].x != enemies[i].gotoX){
				
				if (enemies[i].x < enemies[i].gotoX){
					enemies[i].x += enemies[i].speed;
					if (enemies[i].angle != 0) enemies[i].angle = 1;
				}else if (enemies[i].x > enemies[i].gotoX){
					enemies[i].x -= enemies[i].speed;
					if (enemies[i].angle != 0)enemies[i].angle = 2;
				}
				
				if (enemies[i].x - enemies[i].gotoX <= enemies[i].speed && enemies[i].x - enemies[i].gotoX >= -(enemies[i].speed)) enemies[i].x = enemies[i].gotoX;
			}else{
				if (enemies[i].angle != 0){
					enemies[i].gotoX = randInt(32, 254);
				}
			}

			if (enemies[i].y != enemies[i].gotoY){
				if (enemies[i].y - enemies[i].gotoY <= enemies[i].speed && enemies[i].y - enemies[i].gotoY >= -(enemies[i].speed)) enemies[i].y = enemies[i].gotoY;
				
				if (enemies[i].cnum != 7){
					if (enemies[i].y < enemies[i].gotoY){
						enemies[i].y += enemies[i].speed;
						if (enemies[i].angle != 0 && enemies[i].angle != 2) enemies[i].angle = 3;
					}else if (enemies[i].y > enemies[i].gotoY){
						enemies[i].y -= enemies[i].speed;
						if (enemies[i].angle != 0 && enemies[i].angle != 1) enemies[i].angle = 4;
					}
				}
			}else{
				if (!enemies[i].angle){ 
					amount_fallen += 1;
					enemies[i].active = 0;
					return;
				}else enemies[i].gotoY = randInt(8, 167);
			}
			
			// draws enemies
			if (timers[i] <= 100) timers[i] += 1;
			animate_sprites(i);
			// gfx_SetColor(10 * enemies[i].cnum);
			// gfx_FillRectangle(enemies[i].x, enemies[i].y, 33, 23);
			// gfx_SetColor(224);
			// gfx_Rectangle(enemies[i].x, enemies[i].y, 33, 23);
			
		}else{	
			if (amount_fallen == enemies_amount){
				init_enemies(2, lvl+1);
			}
		}
	
	}
	return;
}

void draw_player(void){
	// all scope happens here
	
	gfx_SetColor(0);
	gfx_FillRectangle(player.x - 5, player.y - 5, 10, 10);
	
	gfx_SetColor(224);	
	gfx_Circle(player.x, player.y, 8);	
	
	// gfx_Circle(player.x, player.y, 10);	
	// gfx_Circle(player.x, player.y, 9);
	return;
}

void player_keys(void){
	switch (key){
		case kb_Up:
			if (player.y - player.speed > 16){
				player.y -= player.speed;
			}else{
				player.y = 16;
			}
			break;
			
		case kb_Down:
			if (player.y + player.speed < 222){
				player.y += player.speed;
			}else{
				player.y = 222;
			}
			break;				
				
		case kb_Left:
			if (player.x - player.speed > 40){
				player.x -= player.speed;
			}else{
				player.x = 40;
			}
			break;
				
		case kb_Right:
			if (player.x + player.speed < 279){
				player.x += player.speed;
			}else{
				player.x = 279;
			}
			break;
	}
	
	player_keys_other();
	
	// exit key
	if (kb_Data[6] == kb_Clear) ext = 1;
	
	return;
}

void player_keys_other(void){
	if (kb_IsDown(kb_KeyUp) && kb_IsDown(kb_KeyRight)){
		if (player.y - player.speed > 16){
			player.y -= player.speed;
		}else player.y = 16;
		
		
		if (player.x + player.speed < 279){
			player.x += player.speed;
		}else player.x = 279;
	}
		
	if (kb_IsDown(kb_KeyUp) && kb_IsDown(kb_KeyLeft)){
		if (player.y - player.speed > 16){
			player.y -= player.speed;
		}else player.y = 16;
		
		if (player.x - player.speed > 40){
			player.x -= player.speed;
		}else player.x = 40;
	}
		
	if (kb_IsDown(kb_KeyDown) && kb_IsDown(kb_KeyRight)){
		if (player.y + player.speed < 222){
				player.y += player.speed;
		}else player.y = 222;
		
		if (player.x + player.speed < 279){
			player.x += player.speed;
		}else player.x = 279;
	}
		
	if (kb_IsDown(kb_KeyDown) && kb_IsDown(kb_KeyLeft)){
		if (player.y + player.speed < 222){
				player.y += player.speed;
		}else player.y = 222;
		
		if (player.x - player.speed > 40){
			player.x -= player.speed;
		}else player.x = 40;
	}
	
	if (kb_Data[1] == kb_2nd) shoot();
}

void init_enemies(int amount, int level){
	enemies_amount = amount;
	lvl = level;
	for (i = 0; i < enemies_amount; i++){
		enemies[i].active = 1;
		enemies[i].x = randInt(32, 254);
		if (enemies[i].x + 33 >= 287) enemies[i].x = 287 - (enemies[i].gotoX + 34);
		enemies[i].y = 167;
		enemies[i].angle = 1;
		enemies[i].gotoX = randInt(32, 254);
		enemies[i].gotoY = randInt(8, 167);
		enemies[i].shot = 0;
		amount_fallen = 0;
		
		SetCostume(i, 1);
		switch (level){
			case 1:
				enemies[i].speed = 1;
				break;
				
			case 2:
				enemies[i].speed = 1;
				break;
				
			case 3:
				enemies[i].speed = 2;
				break;			
				
			case 4:
				enemies[i].speed = 2;
				break;
				
			case 5:
				enemies[i].speed = 3;
				break;
				
			case 6:
				enemies[i].speed = 3;
				break;
				
			case 7:
				enemies[i].speed = 4;
				break;
				
			case 8:
				enemies[i].speed = 4;
				break;
				
			case 9:
				enemies[i].speed = 5;
				break;
				
			case 10:
				enemies[i].speed = 5;
				break;
				
			case 11:
				enemies[i].speed = 6;
				break;
				
			case 12:
				enemies[i].speed = 6;
				break;
			
			case 13:
				enemies[i].speed = 7;
				break;
				
			case 14:
				enemies[i].speed = 7;
				break;
				
			case 15:
				enemies[i].speed = 8;
				break;
				
			case 16:
				enemies[i].speed = 8;
				break;
				
		}
		
		if (level > 17) enemies[i].speed = randInt(8,10);
	}
	
	return;
}

// routines below!!
void vars_int(void){
	player.x = 320/2;
	player.y = 240/2;
	player.score = 0;
	player.speed = 5;
	lvl = 1;
	
	set_dog_mode(0);// walk and jumb in the center!!
	dog.speed = 1;
	
	// for (i = 0; i < 1; i++){
		// enemies[i].active = 1;
		// enemies[i].x = randInt(0, 320);
		// enemies[i].y = 210;
		// enemies[i].gotoX = randInt(0, 320);
		// enemies[i].gotoY = randInt(0, 210);
		// enemies[i].speed = 1; //randInt(1, 5);
	// }
	
	init_enemies(2, 2);

	// exit = 0;
	return;
}

void Debug(void){
	gfx_SetColor(255);
	gfx_FillRectangle(278, 0, 320 - 279, 32);
	
	gfx_SetTextXY(280, 0);
	gfx_PrintString("x:");	
	gfx_PrintInt(dog.x - 5, 3);
	
	gfx_SetTextXY(280, 10);
	gfx_PrintString("dy:");	
	gfx_PrintInt(dog.y - 5, 2);
	
	gfx_SetTextXY(280, 20);
	gfx_PrintString("a:");	
	gfx_PrintInt(lvl, 2);
	
	// gfx_Blit(1);
	return;
}