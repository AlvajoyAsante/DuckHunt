#ifndef UI_H
#define UI_H

#define DUCKHUNT_VERSION "PRE-ALPHA"
#define TIMER_ANIMATE_MAX 4

#define GAME_CANVAS_X_MIN 32
#define GAME_CANVAS_X_MAX 287
#define GAME_CANVAS_Y_MIN 8
#define GAME_CANVAS_Y_MAX 230

#define DUCK_FALLEN_AMOUNT game.amount_fallen
#define DUCK_FALLEN_ID game.fallen_id
#define DUCK_AMOUNT game.enemies_amount
#define GAME_HIGH_SCORE game.high_score
#define GAME_ADVANCE_THRESHOLD game.advance_amount
#define GAME_TOTAL_HITS game.total_hits

#include <tice.h>
#include <graphx.h>
#include <compression.h>

/* Game Information */
struct game_t
{
    // Determines wethier the game started
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
    bool duck_hits[10];

    // total hit attempts
    int total_hits;
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
void reset_duck_hits(void);

/**
 * @brief Get the duck hits amount in `game.duck_hits`
 *
 * @return int amount in of true in boolean array game.duck_hits
 */
int get_duck_hits_amount(void);

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

/**
 * @brief Renders buffer layer of the enemies
 *
 */
void draw_duck_buffer_layer(void);

#endif