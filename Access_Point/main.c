//This is just for testing the struct manipulation:
#include <stdio.h>
#include <stdint.h>
#include "AP.h"

//For compile: 'gcc main.c AP.c'

int main()
{
    light_open_info lamp;
    lamp.starts[1] = 22;
    printf("%i\n", lamp.starts[1]);
    modified_struct(&lamp, 24);
    printf("%i", lamp.starts[1]);
    return 0;
}
