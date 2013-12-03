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


// Joystick Defs
const int INCREMENT = 5;
const int OFFSET = 30;
int X_CENTRE;


// Ball-Specific Variables
int paddlepos;

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


void drawPaddle(int position, int oldpos){
  /* Draws the paddle at the bottom of the screen */
  int vert = 10;
 
  // Draw the paddle 
  tft.fillRect(vert, oldpos, PADDLE_HEIGHT, PADDLE_WIDTH, ST7735_BLACK);
  tft.fillRect(vert, position, PADDLE_HEIGHT, PADDLE_WIDTH, ST7735_WHITE);

}

int readJoystick(int position){
  int joystick_x = analogRead(HOR);

  if(joystick_x > X_CENTRE + OFFSET){
    /* Move to the RIGHT by INCREMENT */
    position += INCREMENT;
    if(position+PADDLE_WIDTH >= SCREEN_WIDTH)
      position = SCREEN_WIDTH - PADDLE_WIDTH;
  }

  else if(joystick_x < X_CENTRE - OFFSET){
    /* Move to the LEFT by INCREMENT */
    position -= INCREMENT;
    if(position <= 0)
      position = 0;
  }

  return(position);
}

void setup(){
  // Start serial communication for debugging
  Serial.begin(9600);
  randomSeed(analogRead(4));
  // Calibrate 'centre' position of joystick
  X_CENTRE = analogRead(HOR);
  pinMode(SEL, INPUT);
  digitalWrite(SEL, HIGH);
  pinMode(SPEAKER, OUTPUT);
  // TODO: Check if joystick is depressed here at startup to use accelerometer for control instead
  // Initialize screen
  tft.initR(INITR_REDTAB);
  tft.fillScreen(ST7735_BLACK);
  int position = (SCREEN_WIDTH/2) - (PADDLE_WIDTH/2);
  int oldpos;

  initializeBall();

  bool updateFlag = false;
  drawPaddle(position, 0);
  drawBricks(NULL);
  drawBall();
  
  displayStats();

  // Main program loop
  while(1){
    
    paddlepos = position;

    oldpos = position;
    position = readJoystick(position);
    if(position != oldpos)
      updateFlag = !updateFlag;
    if(updateFlag){
      drawPaddle(position, oldpos);
      updateFlag = false;
    }

    
    // collision detection for bricks done in here
    updateBallPos(paddlepos);
    
    // check how many lives left. If zero, end the game.
    if(getLivesLeft() <= 0)
        endGame();

    
    drawBall();
    
    delay(20);
  }
  
}

void loop(){}
