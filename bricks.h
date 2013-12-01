#ifndef BRICKS_H
#define BRICKS_H

#include <Adafruit_ST7735.h>
#include "breakout.h"

// Brick definitions
#define BRICK_WIDTH 19
#define BRICK_HEIGHT 9
#define BRICKS_PER_ROW 8
#define BRICK_ROWS 5
#define BRICK_TOTAL 40
 

void drawBricks(Point* p);

#endif
