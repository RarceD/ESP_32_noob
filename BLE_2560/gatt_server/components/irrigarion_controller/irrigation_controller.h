#ifndef IRRIGATION_CONTROLLER
#define IRRIGATION_CONTROLLER

#include <stdint.h>

#define MAX_NUMBER_PROGRAM 4
#define MAX_NUMBER_VALVES 8

typedef struct
{
    uint8_t water_percentage; //0 - 10 -20 -  400%
    uint8_t start_hour[MAX_NUMBER_PROGRAM]; //0-24 h
    uint8_t start_min[MAX_NUMBER_PROGRAM]; //0-59 min
    uint8_t time_hour[MAX_NUMBER_VALVES]; //0 min a 12 min
    uint8_t time_min[MAX_NUMBER_VALVES]; //0 min a 60 min

} Irrigation_program;

void irrig_controller_init_data();
void irrig_controller_save_data();

#endif
