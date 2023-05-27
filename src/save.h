#ifndef SAVE_H
#define SAVE_H

#include <tice.h>
#include <fileioc.h>

#define SAVE_APPVAR_NAME "DCKSAVE"

/**
 * @brief Saves game data to SAVE_APPVAR_NAME
 * 
 */
void save_game(void);

/**
 * @brief Loads game data from SAVE_APPVAR_NAME
 * 
 * @return true the data from the SAVE_APPVAR_NAME was loaded
 * @return false the data from the SAVE_APPVAR_NAME wasn't loaded
 */
bool load_game(void);

#endif