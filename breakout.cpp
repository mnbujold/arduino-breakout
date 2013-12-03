#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#include "breakout.h"
#include "gameStats.h"
#include "bricks.h"
#include "ball.h"

/* GLOBAL VARIABLES */
// tft display
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// joystick centres
int X_CENTRE;
int Y_CENTRE;

// paddle position on-screen
int paddlePos;
int oldPaddlePos;

// determines if paddle moved
bool updateFlag = false;


/* FUNCTIONS */
// used to play tones from the speaker
void playTone(int period, int duration)
{
    long elapsedTime = 0;
    int halfPeriod = period/2;

    while (elapsedTime < duration * 1000L)
    {
        digitalWrite(SPEAKER, HIGH);
        delayMicroseconds(halfPeriod);
        digitalWrite(SPEAKER, LOW);
        delayMicroseconds(halfPeriod);
        elapsedTime = elapsedTime + period;
    }
}

// Draws the paddle at the bottom of the screen
void drawPaddle()
{ 
  tft.fillRect(PADDLE_LEVEL, oldPaddlePos, PADDLE_HEIGHT, PADDLE_WIDTH, ST7735_BLACK);
  tft.fillRect(PADDLE_LEVEL, paddlePos, PADDLE_HEIGHT, PADDLE_WIDTH, ST7735_WHITE);
}

// reads in joystick movement, and adjusts paddle position
void readJoystick()
{
    int joystick_x = analogRead(HOR);

    if(joystick_x > X_CENTRE + OFFSET)
    {
        /* Move to the RIGHT by INCREMENT */
        paddlePos += INCREMENT;
        
        if(paddlePos + PADDLE_WIDTH >= SCREEN_WIDTH)
          paddlePos = SCREEN_WIDTH - PADDLE_WIDTH;
    }
    else if(joystick_x < X_CENTRE - OFFSET)
    {
        /* Move to the LEFT by INCREMENT */
        paddlePos -= INCREMENT;
        
        if(paddlePos <= 0)
            paddlePos = 0;
    }
}

void setup(){
    // Start serial communication for debugging
    Serial.begin(9600);

    // Calibrate 'centre' position of joystick, initialize joystick click
    X_CENTRE = analogRead(HOR);
    Y_CENTRE = analogRead(VERT);
    pinMode(SEL, INPUT);
    digitalWrite(SEL, HIGH);

    // initialize speaker
    pinMode(SPEAKER, OUTPUT);
    // TODO: Check if joystick is depressed here at startup to use accelerometer for control instead

    // Initialize screen
    tft.initR(INITR_REDTAB);
    tft.fillScreen(ST7735_BLACK);
    
    // initialize paddle position
    paddlePos = (SCREEN_WIDTH/2) - (PADDLE_WIDTH/2);
    oldPaddlePos = 0;

    // initial ball position on paddle
    initializeBall();
    
    // draw initial objects to screen
    drawPaddle();
    drawBricks(NULL);
    drawBall();
    displayStats();
}

void loop()
{   
    //Read select pin, to see if joystick has been clicked
    if(digitalRead(SEL) == LOW && ballOnPaddle())
    {
        launchBall();
        while(digitalRead(SEL) == LOW) {}
    }

    // update paddle position
    oldPaddlePos = paddlePos;
    readJoystick();
    
    if(paddlePos != oldPaddlePos)
        updateFlag = !updateFlag;
      
    if(updateFlag)
    {
        drawPaddle();
        updateFlag = false;
    }


    // now update balls position
    updateBallPos(paddlePos);
    
    // check how many lives left. If zero, end the game.
    if(getLivesLeft() <= 0)
        endGame();
    
    // draw the ball
    drawBall();
    
    delay(20);
}
