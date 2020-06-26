//This is just for testing the struct manipulation:
#include <stdio.h>
#include <stdint.h>

#define max_info_AP 20
typedef struct
{
    uint8_t open_starts[max_info_AP];
    uint8_t open_time[max_info_AP];
    
} light_info;

void modified_struct(light_info *lamp, uint8_t hola);


int main()
{
    light_info lamp;
    lamp.open_starts[1] = 22;
    printf("%i",lamp.open_starts[1]);
    modified_struct(&lamp, 24);
    printf("%i",lamp.open_starts[1]);

    return 0;
}

void modified_struct(light_info *lamp, uint8_t hola)
{
    lamp->open_starts[1] = hola;
}
