#ifndef UI_H
#define UI_H

#define DUCKHUNT_VERSION "PRE-ALPHA"
#define TIMER_ANIMATE_MAX 4

/* Canvas Information */
#define GAME_CANVAS_X_MIN 32
#define GAME_CANVAS_X_MAX 287
#define GAME_CANVAS_Y_MIN 8
#define GAME_CANVAS_Y_MAX 230

/* Game Information */
#define DUCK_FALLEN_AMOUNT game.amount_fallen
#define DUCK_FALLEN_ID game.fallen_id
#define DUCK_AMOUNT game.enemies_amount
#define GAME_HIGH_SCORE game.high_score
#define GAME_ADVANCE_THRESHOLD game.advance_amount
#define GAME_TOTAL_HITS game.total_hits

/* Fly Away Information */
#define DUCK_FLYAWAY_TIMER game.force_flyaway_timer
#define DUCK_FLYAWAY_MAX  900

#include <tice.h>
#include <graphx.h>
#include <compression.h>

/* Game Information */
struct game_t
{
    // Determines wether the game started
    bool start;

    // Amount of enemies fallen
    int amount_fallen;

    // Last fallen enemy array index
    int fallen_id;

    // Amount of enemies in game
    int enemies_amount;

    // Overall game high score
    int high_score;

    // amount of duck killed to advance to the next round
    int advance_amount;

    // Enemy hit tracker use HUD
    int duck_hits[10];

    // total hit attempts
    int total_hits;

    // Duck Fly away timer
    int force_flyaway_timer;

    bool forced_flyaway;
};
extern struct game_t game;

/* Rendering Screen */
/**
 * @brief Initialise the Game based on menu option
 *
 */
void init_duckhunt(void);

/**
 * @brief Update the data on the screen
 *
 */
void update_scene(void);

/**
 * @brief Render the scene based on the menu option
 *
 */
void draw_scene(void);

/* HUD Management */
/**
 * @brief Reset the duck hits on HUD
 *
 */
void reset_hud_hits(void);

/**
 * @brief Gets the current position of the duck hits panel
 *
 * @return int amount in of true in boolean array game.duck_hits
 */
int get_hud_hits_position(void);

/**
 * @brief Get the total shot ducks in hits hud
 * 
 * @return int total
 */
int get_hud_hits_shot(void);

/**
 * @brief Bubble sort the hits panel from smallest to greatest.
 * 
 */
void bubble_sort_hits_panel(void);


/* Buffer Layer Management */
/**
 * @brief Get the buffer layer of player, and enemies
 *
 */
void get_buffer_layer(void);

/**
 * @brief Renders the buffer layers of player, and enemies
 *
 */
void draw_buffer_layer(void);

#endif