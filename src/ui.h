#ifndef UI_H
#define UI_H

#define DUCKHUNT_VERSION "PRE-ALPHA"
#define TIMER_ANIMATE_MAX 4

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

/* routines */
/**
 * @brief Renders a traditional rectangle from the game
 *
 * @param x X-Position
 * @param y Y-Position
 * @param w Width
 * @param h Height
 */
void ui_rectangle(int x, int y, int w, int h);

/**
 * @brief This function returns the next position of a point based on the given start, end, and speed.
 *        Note: This is used in recursion!
 *
 * @param start Starting position
 * @param end Ending Position
 * @param speed Speed of object
 * @return int next position
 */
int Goto_Pos(int start, int end, uint8_t speed);

#endif