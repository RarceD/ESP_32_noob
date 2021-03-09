#ifndef SCREENS
#define SCREENS

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "logos.h"

#define _cs 5    // 3 goes to TFT CS
#define _dc 2    // 4 goes to TFT DC
#define _mosi 23 // 5 goes to TFT MOSI
#define _sclk 18 // 6 goes to TFT SCK/CLK
#define _rst 4   // ESP RST to TFT RESET
#define _miso    // Not connected//
//     3.3V     // Goes to TFT LED
//       5v       // Goes to TFT Vcc
//       Gnd      // Goes to TFT Gnd
void write_numbers(uint8_t number, uint8_t pos_x, uint8_t pos_y);
void init_windows();
void main_window();
void config_window();

/*
 - Main
    - Manual
            - Program
            - Valve
    - Program
            -
    - Config
            - TIME

*/

//Define the screen:
Adafruit_ILI9341 tft = Adafruit_ILI9341(_cs, _dc, _mosi, _sclk, _rst);
void init_windows()
{
    tft.begin();
    tft.setRotation(45);
    tft.fillScreen(ILI9341_WHITE);
}
void main_window()
{
    tft.fillScreen(ILI9341_WHITE);
    int h = 240, w = 240, row, col, buffidx = 0;
    for (row = 0; row < h; row++)
        for (col = 0; col < w; col++)
            tft.drawPixel(col + 40, row, pgm_read_word(color_image + buffidx++));
}
void config_window()
{
    // tft.fillScreen(ILI9341_WHITE);
    tft.setRotation(45);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(4);
    const char *config_text[] = {
        "MANUAL",
        "PROGRAM",
        "CONFIG",
    };
    int ofset = 20;
    static int value = 0;
    for (int i = 0; i < 3; i++)
    {
        tft.setCursor(60, ofset += 50);
        tft.println(config_text[i]);
    }
    write_numbers(value++, 60, ofset + 40);
}

void config_window_2(uint8_t input)
{
    // tft.fillScreen(ILI9341_BLACK);
    tft.drawBitmap(100, 100, back, 25, 25, ILI9341_YELLOW);
    tft.drawBitmap(20, 50, sprinkler, 100, 100, ILI9341_NAVY);
    tft.drawBitmap(10, 10, back, 25, 25, ILI9341_BLUE);
    tft.setRotation(45);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(4);
    const char *config_text[] = {
        "MANUAL",
        "PROGRAM",
        "CONFIG",
    };
    int ofset_letters = 5;
    int ofset_box = 0;
    for (int i = 0; i < 3; i++)
    {
        uint8_t h = 20, l = 15;
        tft.drawRect(50, ofset_box += 50, 220, 40, ILI9341_WHITE);
        tft.drawRect(10 + h, ofset_box + l, 10, 10, ILI9341_BLACK);
        tft.drawRect(10 + 1 + h, ofset_box + 1 + l, 10 - 2, 10 - 2, ILI9341_BLACK);
        if (input == i)
        {
            tft.drawRect(10 + h, ofset_box + l, 10, 10, ILI9341_YELLOW);
            tft.drawRect(10 + 1 + h, ofset_box + 1 + l, 10 - 2, 10 - 2, ILI9341_YELLOW);
        }
        tft.setCursor(60, ofset_letters += 50);
        tft.println(config_text[i]);
    }
}

void write_numbers(uint8_t number, uint8_t pos_x, uint8_t pos_y)
{
    // Fill clear the screen with white:
    tft.setTextColor(ILI9341_WHITE);
    int letters_clean[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    for (int i = 0; i < 10; i++)
    {
        tft.setCursor(pos_x, pos_y);
        tft.print(String(letters_clean[i]) + String(letters_clean[i]));
    }
    tft.setTextColor(ILI9341_BLACK);
    //Write the real number
    tft.setCursor(pos_x, pos_y);
    tft.print(number);
}
#endif
