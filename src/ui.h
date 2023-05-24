#ifndef UI_H
#define UI_H

#include <tice.h>
#include <graphx.h>
#include <compression.h>

#define DUCKHUNT_VERSION "PRE-ALPHA"

void draw_scene(void);
void init_duckhunt(uint8_t type);
void show_ver(void);

void get_buffer_layer(void);
void draw_buffer_layer(void);
void draw_duck_buffer_layer(void);
void free_buffer_layer(void);


#endif