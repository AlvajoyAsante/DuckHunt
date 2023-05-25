#ifndef UI_H
#define UI_H

#define DUCKHUNT_VERSION "PRE-ALPHA"
#define ANIMATE_TIMER_MAX 4

#define DUCK_FALLEN_AMOUNT game.amount_fallen
#define DUCK_FALLEN_ID game.fallen_id
#define DUCK_AMOUNT game.enemies_amount
#define GAME_HIGH_SCORE game.high_score

#include <tice.h>
#include <graphx.h>
#include <compression.h>

struct game_t
{
    int amount_fallen;
    int fallen_id;
    int enemies_amount;
    int high_score;
};
extern struct game_t game;

void update_scene(void);
void draw_scene(void);
void init_duckhunt(uint8_t type);

void get_buffer_layer(void);
void draw_buffer_layer(void);
void draw_duck_buffer_layer(void);
void free_buffer_layer(void);

#endif