#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <Adafruit_ST7735.h>

// global var needed for all source files using display
extern Adafruit_ST7735 tft;

/* PRE-PROCESSOR DIRECTIVES */
#define TFT_CS 6  // CS line for TFT display
#define TFT_DC 7  // Data/command line for TFT
#define TFT_RST 8 // Reset line for TFT
#define SCREEN_HEIGHT tft.width()
#define SCREEN_WIDTH tft.height()


typedef struct Point {
  int x;
  int y;
} Point;

#endif
