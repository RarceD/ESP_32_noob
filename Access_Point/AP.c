#include "AP.h"

void modified_struct(light_open_info *lamp, uint8_t hola)
{
    lamp->starts[1] = ++hola;
    lamp->week_day[1] = ++hola;
    lamp->starts[1] = ++hola;
}