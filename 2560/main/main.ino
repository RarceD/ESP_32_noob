#define MQTT_MAX_PACKET_SIZE 7084
#include "secrets.h"
#include "periodic_task.h"
#include "wifi_config.h"
#include "pinout.h"
#include "mqtt_interections.h"
#include "rtc_controller.h"

void setup()
{
    Serial.begin(115200);
    //Initialize all the controller peripherals:
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);
    pinMode(LED_WIFI, OUTPUT);
    strcpy(sys.uuid_, UUID);
    auto_wifi_connect();
    init_mqtt();
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
            if (isrCount % 2 == 0)
            {
                refresh_msg(isrTime);
                check_schedule_on();
            }
        }
        if (led_off && millis() - lastIsrAt >= 800)
        {
            led_off = false;
            digitalWrite(LED, LOW);
        }
        // if (millis() - test_timer >= 1000)
        // {
        //     test_timer = millis();
        //     LOGLN(interrupt_counter);
        // }
        if (isr_encoder_flag)
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
            isr_encoder_flag = false;
        }
        if (digitalRead(ENCODER_SW) == LOW)
        {
            LOGLN("PUSH");
            delay(DEBOUNCED_TIME);
        }
        reconnect();
        client.loop();
    }
}
void loop()
{
}
