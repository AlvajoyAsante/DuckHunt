#include "DUCKSPT.h"
#include <fileioc.h>

#define DUCKSPT_HEADER_SIZE 0

unsigned char *DUCKSPT_appvar[75] =
{
    (unsigned char*)0,
    (unsigned char*)52,
    (unsigned char*)1774,
    (unsigned char*)4016,
    (unsigned char*)5698,
    (unsigned char*)6756,
    (unsigned char*)7918,
    (unsigned char*)9080,
    (unsigned char*)11282,
    (unsigned char*)13477,
    (unsigned char*)15599,
    (unsigned char*)17794,
    (unsigned char*)19996,
    (unsigned char*)22118,
    (unsigned char*)24664,
    (unsigned char*)25652,
    (unsigned char*)26640,
    (unsigned char*)27628,
    (unsigned char*)28622,
    (unsigned char*)29616,
    (unsigned char*)30610,
    (unsigned char*)31170,
    (unsigned char*)31730,
    (unsigned char*)32852,
    (unsigned char*)33974,
    (unsigned char*)35096,
    (unsigned char*)35997,
    (unsigned char*)36985,
    (unsigned char*)37973,
    (unsigned char*)38961,
    (unsigned char*)39955,
    (unsigned char*)40949,
    (unsigned char*)41943,
    (unsigned char*)42503,
    (unsigned char*)43063,
    (unsigned char*)44185,
    (unsigned char*)45307,
    (unsigned char*)46429,
    (unsigned char*)47330,
    (unsigned char*)48318,
    (unsigned char*)49306,
    (unsigned char*)50294,
    (unsigned char*)51288,
    (unsigned char*)52282,
    (unsigned char*)53276,
    (unsigned char*)53836,
    (unsigned char*)54396,
    (unsigned char*)55518,
    (unsigned char*)56640,
    (unsigned char*)57762,
    (unsigned char*)58663,
    (unsigned char*)58921,
    (unsigned char*)59179,
    (unsigned char*)59437,
    (unsigned char*)59695,
    (unsigned char*)59853,
    (unsigned char*)60661,
    (unsigned char*)61428,
    (unsigned char*)61451,
    (unsigned char*)61474,
    (unsigned char*)61489,
    (unsigned char*)61514,
    (unsigned char*)61534,
    (unsigned char*)61552,
    (unsigned char*)61611,
    (unsigned char*)62287,
    (unsigned char*)62655,
    (unsigned char*)62717,
    (unsigned char*)62793,
    (unsigned char*)62919,
    (unsigned char*)62983,
    (unsigned char*)63078,
    (unsigned char*)63171,
    (unsigned char*)63199,
    (unsigned char*)63235,
};

unsigned char DUCKSPT_init(void)
{
    unsigned int data, i;
    uint8_t appvar;

    appvar = ti_Open("DUCKSPT", "r");
    if (appvar == 0)
    {
        return 0;
    }

    data = (unsigned int)ti_GetDataPtr(appvar) - (unsigned int)DUCKSPT_appvar[0] + DUCKSPT_HEADER_SIZE;
    for (i = 0; i < 75; i++)
    {
        DUCKSPT_appvar[i] += data;
    }

    ti_Close(appvar);

    return 1;
}

