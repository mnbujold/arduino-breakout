#include <Adafruit_ST7735.h>

#include "breakout.h"
#include "bricks.h"
#include "ball.h"
#include "gameStats.h"

/* GLOBAL VARIABLES */
Point ball, oldball;
float xdir, ydir;
float speed;
bool onPaddle;


/* FUNCTIONS */
// draws the ball to the screen
void drawBall()
{   
    tft.fillCircle(oldball.y, oldball.x, BALL_RADIUS, ST7735_BLACK);
    tft.fillCircle(ball.y, ball.x, BALL_RADIUS, ST7735_WHITE);
}


// initializes ball to start on paddle
void initializeBall()
{
    ball.x = SCREEN_WIDTH/2;
    ball.y = PADDLE_LEVEL + PADDLE_HEIGHT + BALL_RADIUS;
    oldball.x = 0;
    oldball.y = 0;
    
    onPaddle = true;

    xdir = 0.0;
    ydir = 0.0;
    
    speed = 1.0;
}

// This function does boundary checking on the ball, also determines where
// it hits the paddle, and changes the behavior of the ball depending.
void checkBallCollisions(int paddlepos)
{
    // get paddle position
    //TODO
    
    // first check for any brick collisions
    char detected = drawBricks(&ball);
    
    // if no bricks hit, continue with normal collision detection
    if(detected == 'n')
    {
        // right wall
        if(ball.x >= SCREEN_WIDTH - BALL_RADIUS)
        {
            ball.x = SCREEN_WIDTH - BALL_RADIUS;
            xdir = -xdir;
            playTone(500, 50);
            return;
        }
        // left wall
        if(ball.x <= BALL_RADIUS)
        {
            ball.x = BALL_RADIUS;
            xdir = -xdir;
            playTone(500, 50);
            return;
        }
        // ceiling
        if(ball.y >= SCREEN_HEIGHT - BALL_RADIUS)
        {
            ball.y = SCREEN_HEIGHT - BALL_RADIUS;
            ydir = -ydir;
            playTone(500, 50);
            return;
        }

        if(ball.y < 19 && (ball.x <= paddlepos+(PADDLE_WIDTH/2)+3 && ball.x >= paddlepos+(PADDLE_WIDTH/2)-3))
        {
            ball.y = 19;
            ydir = 1;
            xdir = 0;
            playTone(500,50);
            return;
        }

        if(ball.y < 19 && ( ball.x <= paddlepos+PADDLE_WIDTH))
        {
            ball.y = 19;
            ydir = 1;
            xdir = 1;
            Serial.println(xdir);
            playTone(500, 50);
            return;
        }

        if(ball.y < 19 && (ball.x >= paddlepos ))
        {
            ball.y = 19;
            ydir = 1;
            xdir = -1;
            Serial.println(xdir);
            playTone(500, 50);
            return;
        }
        if(ball.y < 10 && (ball.x < paddlepos || ball.x > paddlepos+PADDLE_WIDTH))
        {
            playTone(500,500);
            initializeBall();
            decreaseLives();
        }
    }
    // brick collision detected, adjust ball accordingly
    else
    {
        // corner of brick hit
        if(detected == 'c')
        {
            xdir = -xdir;
            ydir = -ydir;
            playTone(200,50);
            return;
        }
        else
        {
            // left/right side of brick hit
            if(detected == 'x')
            {
                xdir = -xdir;
                playTone(200,50);
                return;
            }
            // top/bottom of brick hit  
            else if(detected == 'y')
            {
                ydir = -ydir;
                playTone(200,50);
                return;
            }
        }
    }
}

// sets old coordinates, checks for collisions, then sets new
// coordinates based on collision data
void updateBallPos(int paddlePos)
{
    if(onPaddle)
    {
        oldball.x = ball.x;
        oldball.y = ball.y;
        
        ball.x = paddlePos + (PADDLE_WIDTH / 2);
    }
    else
    {
        oldball.x = ball.x;
        oldball.y = ball.y;
        
        checkBallCollisions(paddlePos);
        
        ball.x += xdir*speed;
        ball.y += ydir*speed;
    }
}

// checks if ball is still on paddle
bool ballOnPaddle()
{
    return onPaddle;
}

// sets ball in motion, launching it from paddle
void launchBall()
{
    onPaddle = false;
    ydir = 1.0;
}
