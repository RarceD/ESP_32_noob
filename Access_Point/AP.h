//This is just for testing the struct manipulation:
#include <stdio.h>
#include <stdint.h>

#define MAX_INFO_AP 20
typedef struct
{
    uint8_t starts[MAX_INFO_AP];
    uint8_t time[MAX_INFO_AP];
    uint8_t week_day[MAX_INFO_AP];

} light_open_info;

void modified_struct(light_open_info *lamp, uint8_t hola);
