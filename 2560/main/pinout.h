#ifndef PINOUT
#define PINOUT


#define UUID_LEN 37
#define LED 4
#define LED_WIFI 2
#define BUTTON_RESET 22

/*encode reading:
    SW -> The push button, when push go to low.
    DT -> delay between CLK
    CLK -> The interrupt pin*/

#define ENCODER_SW 25
#define ENCODER_DT 32
#define ENCODER_CLK 33
#define DEBOUNCED_TIME 300

volatile bool isr_encoder_flag;
void IRAM_ATTR isr()
{
    isr_encoder_flag = true;
}

typedef struct
{
  char uuid_[UUID_LEN];
} Entity;



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

active_to_stop active;
stopManualWeb stop_man_web; //MAX 10 valves open at the same time


#endif
