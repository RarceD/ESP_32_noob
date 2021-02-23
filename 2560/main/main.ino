#define MQTT_MAX_PACKET_SIZE 7084
#include "secrets.h"
#include "periodic_task.h"
#include "wifi_config.h"
#include "pinout.h"
#include "mqtt_interections.h"
volatile bool interrupt_flag_right;
volatile bool interrupt_flag_left;

volatile bool debounced = false;

void IRAM_ATTR isr()
{
    interrupt_flag_right = true;
}

void setup()
{
    Serial.begin(115200);
    //Initialize all the controller peripherals:
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);
    pinMode(LED_WIFI, OUTPUT);
    strcpy(sys.uuid_, UUID);
    // auto_wifi_connect();
    // init_mqtt();
    config_timer();
    digitalWrite(LED_WIFI, HIGH);
    digitalWrite(LED, LOW);

    //Define the rotatory encoder:
    pinMode(ENCODER_CLK, INPUT);
    pinMode(ENCODER_DT, INPUT);
    pinMode(ENCODER_SW, INPUT);
    attachInterrupt(ENCODER_DT, isr, FALLING);

    uint32_t debounced_timer = 0;
    bool led_off = false;
    uint32_t test_timer = millis();
    while (true)
    {
        if (xSemaphoreTake(timer_mqtt, 0) == pdTRUE)
        {
            digitalWrite(LED, HIGH);
            uint32_t isrCount = 0, isrTime = 0;
            // Read the interrupt count and time
            portENTER_CRITICAL(&timerMux);
            isrCount = isrCounter;
            isrTime = lastIsrAt;
            portEXIT_CRITICAL(&timerMux);
            LOG("Counter ISR:");
            LOGLN(isrCount);
            led_off = true;
            // LOGLN(sys.selector_auto);
            // if (isrCount % 2 == 0)
            //     refresh_msg(isrTime);
        }
        if (led_off && millis() - lastIsrAt >= 800)
        {
            led_off = false;
            // digitalWrite(LED, LOW);
        }
        if (millis() - test_timer >= 1000)
        {
            test_timer = millis();
            // LOGLN(interrupt_counter);
        }
        if (interrupt_flag_right)
        {
            if (millis() - debounced_timer >= DEBOUNCED_TIME)
            {
                digitalWrite(LED, LOW);
                delay(2);
                digitalWrite(LED, HIGH);
                if (digitalRead(ENCODER_CLK) == LOW)
                    LOGLN("DERECHA");
                else
                    LOGLN("IZQUIERDA");
                debounced_timer = millis();
            }
            interrupt_flag_right = false;
        }
        if (digitalRead(ENCODER_SW) == LOW)
        {
            LOGLN("PUSH");
            delay(DEBOUNCED_TIME);
        }
    }

    // reconnect();
    // client.loop();

    //     //Handler timers to publish:
    //     // Check if the manual timer has finish:
    //     if (millis() - millix >= 50000)
    //     {
    //         //Second I check if there is any manual open valve ON in order to close
    //         if (stop_man_web.manual_web)
    //         {
    //             for (uint8_t t = 0; t < 10; t++)
    //                 if (stop_man_web.active[t])
    //                 {
    //                     LOGLN("CHECK");
    //                     if (millis() - stop_man_web.millix[t] >= stop_man_web.times[t] - 10000)
    //                     {
    //                         LOGLN("I close the manual valve with my timer");
    //                         LOGLN(stop_man_web.valve_number[t]);
    //                         pg_serial_action_valve(0, stop_man_web.valve_number[t], 0, 0);
    //                         //Save the valve number:
    //                         stop_man_web.valve_number[t] = 0;
    //                         //Th current time on timer 0
    //                         stop_man_web.millix[t] = 0;
    //                         //The time in ms to stop the valve
    //                         stop_man_web.times[t] = 0;
    //                         //The flag of the valve in the struct:
    //                         stop_man_web.active[t] = false;
    //                         if (stop_man_web.number_timers > 0)
    //                             stop_man_web.number_timers--;
    //                         else
    //                             stop_man_web.manual_web = false;
    //                     }
    //                 }
    //         }
    //         //Check if auto program has start any program:
    //         int hour = 0;
    //         int weekday = 0;
    //         int minute = 0;
    //         pg_time_check(&hour, &minute, &weekday);
    //         LOG(hour);
    //         LOG(":");
    //         LOG(minute);
    //         LOG(" - day: ");
    //         LOGLN(weekday);
    //         for (int index_prog = 0; index_prog < 6; index_prog++)
    //             for (int index_start = 0; index_start < 6; index_start++)
    //                 if (prog[index_prog].start[index_start][0] == hour)
    //                     if (prog[index_prog].start[index_start][1] == minute)
    //                     {
    //                         LOG("Start program ");
    //                         LOGLN(index_prog);
    //                         char program_letters[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    //                         if (hour != 0)
    //                             json_program_action(true, program_letters[index_prog]);
    //                     }
    //         millix = millis();
    //     }
    // }
}
void loop()
{
}
