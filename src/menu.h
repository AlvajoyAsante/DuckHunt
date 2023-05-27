#ifndef MENU_H
#define MENU_H

#define COPYRIGHT_TEXT "1984  NINT ENDO  CO., LT D."

#include <tice.h>
#include <keypadc.h>

/* Main Menu information */
struct menu_t
{
	int opt;
};
extern struct menu_t menu;

/**
 * @brief Render Menu and get user input
 *
 * @return true: user want to play
 * @return false: user does not want to play
 */
bool init_menu(void);

#endif