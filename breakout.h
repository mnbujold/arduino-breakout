#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <Adafruit_ST7735.h>

// global var needed for all source files drawing to display
extern Adafruit_ST7735 tft;

/* DEFINITIONS */
// display pins
#define TFT_CS 6  // CS line for TFT display
#define TFT_DC 7  // Data/command line for TFT
#define TFT_RST 8 // Reset line for TFT
// joystick pins
#define VERT 1
#define HOR 0
#define SEL 9
// speaker pin
#define SPEAKER 11
// height and width of screen
#define SCREEN_HEIGHT tft.width()
#define SCREEN_WIDTH tft.height()

// paddle dimensions
#define PADDLE_WIDTH 25
#define PADDLE_HEIGHT 5

/* POINT STRUCT */
typedef struct Point
{
    int x;
    int y;
} Point;

/* SHARED FUNCTIONS */
void playTone(int period, int duration);

#endif
