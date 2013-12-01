#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#include "breakout.h"
#include "bricks.h"

/* GLOBAL VARIABLES */
// Brick array for visibility
bool hitBricks[BRICK_ROWS][BRICKS_PER_ROW];
// Brick array for position
Point brickLocations[BRICK_ROWS][BRICKS_PER_ROW];
// array defines brick row colors
uint16_t rowColors[] = {ST7735_RED, ST7735_MAGENTA, ST7735_YELLOW, ST7735_GREEN, ST7735_BLUE};


/* FUNCTIONS */
// function initializes all brick locations and visibility, and draws them to the screen.
void initializeBricks()
{
    for(int i = 0; i < BRICK_ROWS; i++)
    {
        for(int j = 0; j < BRICKS_PER_ROW; j++)
        {
            // brick is not hit, therefore false
            hitBricks[i][j] = false;
            
            // define bricks bottom left corner
            brickLocations[i][j].x = (SCREEN_HEIGHT - 1) - (((BRICK_HEIGHT + 1) * (i+1)) + 1);
            brickLocations[i][j].y = ((BRICK_WIDTH + 1) * j) + 1;
            
            // draw brick to screen
            tft.fillRect(brickLocations[i][j].x, brickLocations[i][j].y,
                         BRICK_HEIGHT, BRICK_WIDTH, rowColors[i]);
        }
    }
}

// function used to draw the bricks. Point p is ball position.
// If p is NULL, then this function draws all initial bricks to the screen.
// If p is not NULL, then p is checked for collision with bricks.
void drawBricks(Point* p)
{
    if(p == NULL)
    {
        initializeBricks();
    }
    else
    {
    
    }
}
