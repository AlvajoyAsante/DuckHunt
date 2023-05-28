#include "save.h"
#include "ui.h"
#include "player.h"

/**
 * @brief initialize game settings
 *
 */
static void init_settings(void)
{
    game.high_score = 12000; 
    game.start = game.amount_fallen = game.fallen_id = game.enemies_amount = game.advance_amount = game.total_hits = 0;
    reset_duck_hits();
}

void save_game(void)
{
    uint8_t slot;

    /* is the current score less than high score then return */
    if (player.score <= GAME_HIGH_SCORE)
    {
        return;
    }
    else
    {
        GAME_HIGH_SCORE = player.score;
    }

    /* Open appvar and save data */
    slot = ti_Open(SAVE_APPVAR_NAME, "w");
    ti_Write(&game, sizeof(struct game_t), 1, slot);
    ti_Close(slot);
}

bool load_game(void)
{
    uint8_t slot;

    /* Check if file exist and load data */
    if ((slot = ti_Open(SAVE_APPVAR_NAME, "r")) != 0)
    {
        if (ti_Read(&game, sizeof(struct game_t), 1, slot))
        {
            /* Reset other data beside high-score */
            game.start = game.amount_fallen = game.fallen_id = game.enemies_amount = game.advance_amount = game.total_hits = 0;
        }

        ti_Close(slot);

        return 1;
    }
    else
    {
        /* File does not exist */
        init_settings();
    }

    return 0;
}