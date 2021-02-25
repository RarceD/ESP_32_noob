#define MQTT_MAX_PACKET_SIZE 7084
#include "secrets.h"
#include "periodic_task.h"
#include "wifi_config.h"
#include "pinout.h"
#include "mqtt_interections.h"
#include "rtc_controller.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "logos.h"

#define _cs 5    // 3 goes to TFT CS
#define _dc 2    // 4 goes to TFT DC
#define _mosi 23 // 5 goes to TFT MOSI
#define _sclk 18 // 6 goes to TFT SCK/CLK
#define _rst 4   // ESP RST to TFT RESET
#define _miso    // Not connected

Adafruit_ILI9341 tft = Adafruit_ILI9341(_cs, _dc, _mosi, _sclk, _rst);

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
    //Define the screen
    tft.begin();
    tft.setRotation(45);
    tft.fillScreen(ILI9341_WHITE);
    // tft.drawBitmap(40, 0, logo, 240, 240, ILI9341_DARKGREY);

    int h = 240, w = 240, row, col, buffidx = 0;
    for (row = 0; row < h; row++)
        for (col = 0; col < w; col++)
            tft.drawPixel(col + 40, row, pgm_read_word(color_image + buffidx++));

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
                // check_schedule_on();

                tft.fillScreen(ILI9341_BLACK);
                tft.drawBitmap(20, 50, sprinkler, 100, 100, ILI9341_NAVY);
                tft.drawBitmap(200, 50, irrigating, 100, 100, ILI9341_GREENYELLOW);
                tft.drawBitmap(0, 190, wifi, 50, 50, ILI9341_PURPLE);
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
                tft.drawBitmap(0, 190, wifi, 50, 50, ILI9341_PURPLE);

            }
            isr_encoder_flag = false;
        }
        if (digitalRead(ENCODER_SW) == LOW)
        {
            LOGLN("PUSH");
                            tft.fillScreen(ILI9341_BLACK);
                tft.drawBitmap(20, 50, sprinkler, 100, 100, ILI9341_NAVY);
            // delay(DEBOUNCED_TIME);
        }
        reconnect();
        client.loop();
    }
}
void loop()
{
}
