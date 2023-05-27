#ifndef UI_H
#define UI_H

#define DUCKHUNT_VERSION "PRE-ALPHA"
#define ANIMATE_TIMER_MAX 4

#define DUCK_FALLEN_AMOUNT game.amount_fallen
#define DUCK_FALLEN_ID game.fallen_id
#define DUCK_AMOUNT game.enemies_amount
#define GAME_HIGH_SCORE game.high_score
#define GAME_ADVANCE_THRESHOLD game.advance_amount
#define GAME_TOTAL_HITS game.total_hits

#include <tice.h>
#include <graphx.h>
#include <compression.h>

struct game_t
{
    bool start;
    int amount_fallen;
    int fallen_id;
    int enemies_amount;
    int high_score;
    int advance_amount;
    bool duck_hits[10];
    int total_hits;
};
extern struct game_t game;

void update_scene(void);

void draw_scene(void);

void init_duckhunt(uint8_t type);

void reset_duck_hits(void);

int get_duck_hits_amount(void);

void get_buffer_layer(void);

void draw_buffer_layer(void);

void draw_duck_buffer_layer(void);

void ui_rectangle(int x, int y, int w, int h);

#endif