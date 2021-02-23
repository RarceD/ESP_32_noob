#ifndef PINOUT
#define PINOUT
#define UUID_LEN 37
#define LED 4
#define LED_WIFI 2
#define BUTTON_RESET 22

/*encode reading:
    GND
    +
    SW -> The push button, when push go to low.
    DT -> delay between CLK
    CLK ->

*/

#define ENCODER_SW 25
#define ENCODER_DT 32
#define ENCODER_CLK 33

#define DEBOUNCED_TIME 300

typedef struct
{
  char uuid_[UUID_LEN];
} Entity;

typedef struct
{
  uint8_t interval;
  uint8_t startDay;
  uint8_t wateringDay;
  uint16_t waterPercent;
  uint8_t start[6][2];
  uint16_t irrigTime[128];
} program;

typedef struct //If I recevived a stop command in the web I have to know what to stop
{
  bool valves[128];
  bool programs[6];
} active_to_stop;

typedef struct
{
  bool manual_web;
  bool active[10];
  uint8_t number_timers;
  uint8_t valve_number[10];
  uint32_t millix[10];
  uint32_t times[10];
} stopManualWeb;

Entity sys;
program prog[6];
active_to_stop active;
stopManualWeb stop_man_web; //MAX 10 valves open at the same time


#endif
