#include "save.h"
#include "ui.h"
#include "player.h"

static void init_settings(void)
{
}

void save_game(void)
{
    uint8_t var;

    /* is the current score less than high score then leave */
    if (player.score <= GAME_HIGH_SCORE)
    return;

    /* High score is bigger than expected then save it */

    

}

void load_game(void)
{
    uint8_t var;



}