#include "DUCKSPT.h"
#include <fileioc.h>

#define DUCKSPT_HEADER_SIZE 0

unsigned char *DUCKSPT_appvar[10] =
{
    (unsigned char*)0,
    (unsigned char*)16,
    (unsigned char*)1004,
    (unsigned char*)1686,
    (unsigned char*)2504,
    (unsigned char*)3343,
    (unsigned char*)4305,
    (unsigned char*)5082,
    (unsigned char*)5983,
    (unsigned char*)6543,
};

unsigned char DUCKSPT_init(void)
{
    unsigned int data, i;
    ti_var_t appvar;

    ti_CloseAll();

    appvar = ti_Open("DUCKSPT", "r");
    if (appvar == 0)
    {
        return 0;
    }

    data = (unsigned int)ti_GetDataPtr(appvar) - (unsigned int)DUCKSPT_appvar[0] + DUCKSPT_HEADER_SIZE;
    for (i = 0; i < 10; i++)
    {
        DUCKSPT_appvar[i] += data;
    }

    ti_CloseAll();

    return 1;
}

