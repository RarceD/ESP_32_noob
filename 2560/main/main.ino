#define MQTT_MAX_PACKET_SIZE 7084
#include "secrets.h"
#include "periodic_task.h"
#include "wifi_config.h"
#include "pinout.h"
#include "mqtt_interections.h"


void setup()
{
    Serial.begin(115200);
    pinMode(LED, OUTPUT);
    pinMode(LED_WIFI, OUTPUT);
    digitalWrite(LED, HIGH);
    strcpy(sys.uuid_, UUID);
    auto_wifi_connect();
    init_mqtt();
    config_timer();
    digitalWrite(LED_WIFI, HIGH);
    digitalWrite(LED, LOW);
    uint32_t millix = millis();
    digitalWrite(LED, LOW);

    while (true)
    // for (int i = 0; i < 10; i++)
    // {
    {
        // digitalWrite(LED_WIFI, HIGH);
        // delayMicroseconds(1250);
        // // delay(1250);
        // // Serial.print("abcdefg");
        //         digitalWrite(LED_WIFI, LOW);
        // // delay(1250);
        // delayMicroseconds(1250);

    }
    // while (true)
    // {
    //     //Handler timers to publish:
    //     if (xSemaphoreTake(timer_mqtt, 0) == pdTRUE)
    //     {
    //         digitalWrite(LED, HIGH);
    //         uint32_t isrCount = 0, isrTime = 0;
    //         // Read the interrupt count and time
    //         portENTER_CRITICAL(&timerMux);
    //         isrCount = isrCounter;
    //         isrTime = lastIsrAt;
    //         portEXIT_CRITICAL(&timerMux);
    //         LOG("Counter ISR:");
    //         LOGLN(isrCount);
    //         // LOGLN(sys.selector_auto);
    //         if (isrCount % 50 == 0)
    //         {
    //             publish_counter++;
    //             char json[100];
    //             DynamicJsonBuffer jsonBuffer(32);
    //             JsonObject &root = jsonBuffer.createObject();
    //             root.set("publish", publish_counter);
    //             root.set("heap", esp_get_free_heap_size());
    //             root.set("heap_min", esp_get_minimum_free_heap_size());
    //             root.set("uptime", isrTime);
    //             root.printTo(json);
    //             client.publish((String(sys.uuid_) + "/uptime").c_str(), (const uint8_t *)json, strlen(json), false);
    //             LOGLN("Publish");
    //         }
    //         sys.led_off = true;
    //     }
    //     if (sys.led_off && millis() - lastIsrAt >= 800)
    //     {
    //         sys.led_off = false;
    //         digitalWrite(LED, LOW);
    //     }
    //     pg_listen();
    //     reconnect();
    //     client.loop();
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
