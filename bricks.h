#ifndef BRICKS_H
#define BRICKS_H

#include <Adafruit_ST7735.h>
#include "breakout.h"

/* DEFINITIONS */
#define BRICK_WIDTH 19
#define BRICK_HEIGHT 9
#define BRICKS_PER_ROW 8
#define BRICK_ROWS 5
#define BRICK_TOTAL 40

/* COLLISION STRUCT */
// character indicates if top/bottom, or left/right side hit.
// boolean indicates if it was a corner
typedef struct collisionType
{
    char valueChange;
    bool cornerHit;
} collision;


collision* drawBricks(Point* p);

#endif
