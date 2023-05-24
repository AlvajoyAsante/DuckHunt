#include "DUCKSPT.h"
#include <fileioc.h>

#define DUCKSPT_HEADER_SIZE 0

unsigned char *DUCKSPT_appvar[69] =
{
    (unsigned char*)0,
    (unsigned char*)60,
    (unsigned char*)1782,
    (unsigned char*)4024,
    (unsigned char*)5706,
    (unsigned char*)6764,
    (unsigned char*)7926,
    (unsigned char*)9088,
    (unsigned char*)11290,
    (unsigned char*)13485,
    (unsigned char*)15607,
    (unsigned char*)17802,
    (unsigned char*)20004,
    (unsigned char*)22126,
    (unsigned char*)24672,
    (unsigned char*)25660,
    (unsigned char*)26648,
    (unsigned char*)27636,
    (unsigned char*)28630,
    (unsigned char*)29624,
    (unsigned char*)30618,
    (unsigned char*)31178,
    (unsigned char*)31738,
    (unsigned char*)32860,
    (unsigned char*)33982,
    (unsigned char*)35104,
    (unsigned char*)36005,
    (unsigned char*)36993,
    (unsigned char*)37981,
    (unsigned char*)38969,
    (unsigned char*)39963,
    (unsigned char*)40957,
    (unsigned char*)41951,
    (unsigned char*)42511,
    (unsigned char*)43071,
    (unsigned char*)44193,
    (unsigned char*)45315,
    (unsigned char*)46437,
    (unsigned char*)47338,
    (unsigned char*)48326,
    (unsigned char*)49314,
    (unsigned char*)50302,
    (unsigned char*)51296,
    (unsigned char*)52290,
    (unsigned char*)53284,
    (unsigned char*)53844,
    (unsigned char*)54404,
    (unsigned char*)55526,
    (unsigned char*)56648,
    (unsigned char*)57770,
    (unsigned char*)58671,
    (unsigned char*)58829,
    (unsigned char*)59637,
    (unsigned char*)60404,
    (unsigned char*)60427,
    (unsigned char*)60445,
    (unsigned char*)60504,
    (unsigned char*)61180,
    (unsigned char*)61548,
    (unsigned char*)61610,
    (unsigned char*)61686,
    (unsigned char*)61812,
    (unsigned char*)61922,
    (unsigned char*)62017,
    (unsigned char*)62110,
    (unsigned char*)62397,
    (unsigned char*)62679,
    (unsigned char*)62851,
    (unsigned char*)62887,
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

