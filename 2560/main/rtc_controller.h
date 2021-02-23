#ifndef RTC_CONTROLLER
#define RTC_CONTROLLER

#include "pinout.h"
#include "secrets.h"
typedef struct
{
    bool open;
    uint8_t interval;
    uint8_t startDay;
    uint8_t wateringDay;
    uint16_t waterPercent;
    uint8_t start[6][2];
    uint16_t irrigTime[14];
} program;

program prog[6];

void check_schedule_on()
{
    int hour = 0;
    int weekday = 0;
    int minute = 0;
    // pg_time_check(&hour, &minute, &weekday);
    LOG(hour);
    LOG(":");
    LOG(minute);
    LOG(" - day: ");
    LOGLN(weekday);
    for (int index_prog = 0; index_prog < 6; index_prog++)
    {
        //check if the program is open I will have to close:
        if (prog[index_prog].open)
        {

        }
        //if not open I will check if it time to:
        else
        {
            for (int index_start = 0; index_start < 6; index_start++)
                if (prog[index_prog].start[index_start][0] == hour)
                    if (prog[index_prog].start[index_start][1] == minute)
                    {
                        LOG("Start program ");
                        char program_letters[] = {'A', 'B', 'C', 'D', 'E', 'F'};
                        LOGLN(program_letters[index_prog]);
                        prog[index_prog].open = true;
                        // if (hour != 0)
                        // json_program_action(true, program_letters[index_prog]);
                    }
        }
    }
}

void check_schedule_off()
{
    for (int index_prog = 0; index_prog < 6; index_prog++)
    {
    }
}

#endif RTC_CONTROLLER
