#include "DUCKSPT.h"
#include <fileioc.h>

#define DUCKSPT_HEADER_SIZE 0

unsigned char *DUCKSPT_appvar[69] =
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
    (unsigned char*)58821,
    (unsigned char*)59629,
    (unsigned char*)60396,
    (unsigned char*)60419,
    (unsigned char*)60442,
    (unsigned char*)60457,
    (unsigned char*)60475,
    (unsigned char*)60534,
    (unsigned char*)61210,
    (unsigned char*)61578,
    (unsigned char*)61640,
    (unsigned char*)61716,
    (unsigned char*)61842,
    (unsigned char*)61906,
    (unsigned char*)62001,
    (unsigned char*)62094,
    (unsigned char*)62122,
    (unsigned char*)62158,
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
    for (i = 0; i < 69; i++)
    {
        DUCKSPT_appvar[i] += data;
    }

    ti_Close(appvar);

    return 1;
}

