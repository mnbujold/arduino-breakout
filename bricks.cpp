#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#include "breakout.h"
#include "gameStats.h"
#include "bricks.h"
#include "ball.h"

/* GLOBAL VARIABLES */
// Brick array for visibility
bool hitBricks[BRICK_ROWS][BRICKS_PER_ROW];
// Brick array for position
Point brickLocations[BRICK_ROWS][BRICKS_PER_ROW];
// array defines brick row colors
const uint16_t rowColors[] = {ST7735_RED, ST7735_MAGENTA, ST7735_YELLOW, ST7735_GREEN, ST7735_BLUE};
// array defines brick row point worth
const int rowScores[] = {7, 5, 3, 2, 1};
// indicates beginning of bricks on-screen
int bricksBottom;


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
            brickLocations[i][j].y = (SCREEN_HEIGHT - 1) - (((BRICK_HEIGHT + 1) * (i+1)) + 1);
            brickLocations[i][j].x = ((BRICK_WIDTH + 1) * j) + 1;
            
            // draw brick to screen
            tft.fillRect(brickLocations[i][j].y, brickLocations[i][j].x,
                         BRICK_HEIGHT, BRICK_WIDTH, rowColors[i]);
                         
            // set where bricks begin
            if((i == BRICK_ROWS - 1) && (j == BRICKS_PER_ROW - 1))
                bricksBottom = brickLocations[i][j].y;
        }
    }
}

// used to detect a collision between ball and brick
char detectCollision(Point* p)
{
    char detected = 'n';
    
    if(p->y + BALL_RADIUS >= bricksBottom)
    {
        for(int i = BRICK_ROWS - 1; i >= 0; i--)
        {
            for(int j = 0; j < BRICKS_PER_ROW; j++)
            {
                if(hitBricks[i][j] == false)
                {   
                    // top or bottom hit detection:
                    if((p->y + BALL_RADIUS == brickLocations[i][j].y) ||
                            (p->y - BALL_RADIUS == brickLocations[i][j].y + BRICK_HEIGHT))
                    {
                        if((p->x + BALL_RADIUS >= brickLocations[i][j].x) &&
                           (p->x - BALL_RADIUS <= brickLocations[i][j].x + BRICK_WIDTH))
                        {
                            // brick is hit, fill in with black
                            hitBricks[i][j] = true;
                            tft.fillRect(brickLocations[i][j].y, brickLocations[i][j].x,
                                    BRICK_HEIGHT, BRICK_WIDTH, ST7735_BLACK);
                            
                            //add to score
                            increaseScore(rowScores[i]);
                            
                            // balls y direction changes
                            detected = 'y';
                        }
                    }
                    
                    // left or right hit detection:
                    else if((p->x + BALL_RADIUS == brickLocations[i][j].x) ||
                            (p->x - BALL_RADIUS == brickLocations[i][j].x + BRICK_WIDTH))
                    {
                        if((p->y + BALL_RADIUS >= brickLocations[i][j].y) &&
                           (p->y - BALL_RADIUS <= brickLocations[i][j].y + BRICK_HEIGHT))
                        {
                            // brick is hit, fill in with black
                            hitBricks[i][j] = true;
                            tft.fillRect(brickLocations[i][j].y, brickLocations[i][j].x,
                                    BRICK_HEIGHT, BRICK_WIDTH, ST7735_BLACK);
                                
                            //add to score
                            increaseScore(rowScores[i]);
                            
                            // if a top or bottom hit, then treated as corner hit
                            if(detected == 'y')
                            {    
                                detected = 'c';
                            }
                            else
                            {
                                // balls x direction changes
                                detected = 'x'; 
                            }
                        }
                    }
                    
                    // in case ball ends up inside brick
                    else if(((p->y > brickLocations[i][j].y) &&
                       (p->y < brickLocations[i][j].y + BRICK_HEIGHT)) &&
                       ((p->x > brickLocations[i][j].x) &&
                       (p->x < brickLocations[i][j].x + BRICK_WIDTH)))
                    {
                        // brick is hit, fill in with black
                        hitBricks[i][j] = true;
                        tft.fillRect(brickLocations[i][j].y, brickLocations[i][j].x,
                                    BRICK_HEIGHT, BRICK_WIDTH, ST7735_BLACK);
                        
                        // add to score
                        increaseScore(rowScores[i]);
                        
                        // treat as a left/right
                        detected = 'x';
                    }
                }
            }
        }
    }
    
    // return 'n' if no collision detected
    return detected;
}

// function used to draw the bricks. Point p is ball position.
// If p is NULL, then this function draws all initial bricks to the screen.
// If p is not NULL, then p is checked for collision with bricks, then updates bricks hit.
char drawBricks(Point* p)
{
    if(p == NULL)
    {
        initializeBricks();
        return 'n';
    }
    else
    {
        return detectCollision(p);
    }
}
