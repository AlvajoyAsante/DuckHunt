#ifndef UTILS_H
#define UTILS_H

#include <tice.h>
#include <math.h>
#include <graphx.h>

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

/**
 * @brief This function calculates the distance between two points.
 *
 * @param x1:  The x-coordinate of the first point.
 * @param y1: The y-coordinate of the first point.
 * @param x2: The x-coordinate of the second point.
 * @param y2: The y-coordinate of the second point.
 * @return int: The distance between the two points.
 */
int get_distance(int x1, int y1, int x2, int y2);

#endif