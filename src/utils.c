#include "utils.h"

void ui_rectangle(int x, int y, int w, int h)
{
    gfx_SetColor(16);
    for (int i = 0; i < w; i++)
    {
        if (i == 0 || i == w - 1)
        {
            gfx_VertLine(x + i, y + 1, h - 2);
        }
        else
            gfx_VertLine(x + i, y, h);
    }

    gfx_SetColor(2);

    x++;
    y++;
    w -= 2;
    h -= 2;
    for (int i = 0; i < w; i++)
    {
        if (i == 0 || i == w - 1)
        {
            gfx_VertLine(x + i, y + 1, h - 2);
        }
        else
            gfx_VertLine(x + i, y, h);
    }
}

int Goto_Pos(int start, int end, uint8_t speed)
{
    if (start == end)
        return start;

    /* Checks if the postion is speed distance */
    if (start - end <= speed && start - end >= -(speed))
        return end;

    /* Checks if the position is less than the destination position */
    if (start < end)
    {
        start += speed;
    }
    else if (start > end)
    {
        start -= speed;
    }

    return start;
}

int get_distance(int x1, int y1, int x2, int y2)
{
    // Use the Pythagorean theorem to calculate the distance.
    int dx = x2 - x1;
    int dy = y2 - y1;
    int distance = sqrt(dx * dx + dy * dy);
    
    return distance;
}
