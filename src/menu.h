#ifndef MENU_H
#define MENU_H

#include <tice.h>
#include <keypadc.h>

/* Main Menu information */
struct menu_t
{
	int opt;
	int enter;
};
extern struct menu_t menu;

/* initialize the menu */
bool init_menu(void);

#endif