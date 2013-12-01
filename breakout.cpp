#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#include "breakout.h"
#include "bricks.h"

/* GLOBAL VARIABLES */
// tft display
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Paddle Size
const int PADDLE_WIDTH = 25;
const int PADDLE_HEIGHT = 5;

// Joystick Pins
const int VERT = 1;
const int HOR = 0;
const int SEL = 9;
// Joystick Defs
const int INCREMENT = 5;
const int OFFSET = 30;
int X_CENTRE;

const int speakerPin = 11;

// Ball-Specific Variables
const int BALL_RADIUS = 3;
Point ball, oldball;
int xdir, ydir;
int paddlepos;

int totalScore = 0;

void playTone(int period, int duration){
  long elapsedTime = 0;
  int halfPeriod = period/2;

  while (elapsedTime < duration * 1000L){
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(halfPeriod);
    digitalWrite(speakerPin, LOW);
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

void drawBall(Point p, Point old){

  tft.fillCircle(old.y, old.x, BALL_RADIUS, ST7735_BLACK);
  tft.fillCircle(p.y, p.x, BALL_RADIUS, ST7735_WHITE);
}

void checkBallPos(){
  /* 
    This function does boundary checking on the ball, also determines where
    it hits the paddle, and changes the behavior of the ball depending.
  */
  if(ball.x > SCREEN_WIDTH){
    ball.x = SCREEN_WIDTH;
    xdir = -1;
    playTone(500, 50);
    return;
  }

  if(ball.x < 0){
    ball.x = 0;
    xdir = 1;
    playTone(500, 50);
    return;
  }

  if(ball.y > SCREEN_HEIGHT){
    ball.y = SCREEN_HEIGHT;
    ydir = -1;
    playTone(500, 50);
    return;
  }

  if(ball.y < 19 && (ball.x <= paddlepos+(PADDLE_WIDTH/2)+3 && ball.x >= paddlepos+(PADDLE_WIDTH/2)-3)){
    ball.y = 19;
    ydir = 1;
    xdir = 0;
    totalScore++;
    playTone(500,50);
    return;
  }

  if(ball.y < 19 && (ball.x >= paddlepos && ball.x <= paddlepos+PADDLE_WIDTH)){
    ball.y = 19;
    ydir = 1;
    totalScore++;
    playTone(500, 50);
    return;
  }

  if(ball.y < 10 && (ball.x < paddlepos || ball.x > paddlepos+PADDLE_WIDTH)) {
    playTone(500,500);
    ball.y = SCREEN_HEIGHT/2;
    ball.x = paddlepos;
    ydir = 1;
    xdir = 1;
  }

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

void displayInfo(int score){
  // Testing out score display...
  tft.setRotation(1);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.fillRect(0,120,50,4,ST7735_BLACK);
  tft.setCursor(0,120);
  tft.print("Score: ");
  tft.print(score);
  tft.setCursor(140,120);
  tft.print("ooo");

  tft.setRotation(0);
}

void setup(){
  // Start serial communication for debugging
  Serial.begin(9600);
  // Calibrate 'centre' position of joystick
  X_CENTRE = analogRead(HOR);
  pinMode(SEL, INPUT);
  digitalWrite(SEL, HIGH);
  pinMode(speakerPin, OUTPUT);
  // TODO: Check if joystick is depressed here at startup to use accelerometer for control instead
  // Initialize screen
  tft.initR(INITR_REDTAB);
  tft.fillScreen(ST7735_BLACK);
  int position = (SCREEN_WIDTH/2) - (PADDLE_WIDTH/2);
  int oldpos;

  ball.x = SCREEN_WIDTH/2;
  ball.y = SCREEN_HEIGHT/2;
  oldball.x = 0;
  oldball.y = 0;

  xdir = 1;
  ydir = 1;

  bool updateFlag = false;
  drawPaddle(position, 0);
  drawBricks(NULL);
  drawBall(ball, oldball);
  

  int speed = 1;
  displayInfo(totalScore);

  // Main program loop
  while(1){
    
    paddlepos = position;

    oldpos = position;
    position = readJoystick(position);
    if(position != oldpos)
      updateFlag = !updateFlag;
    if(updateFlag){
      drawPaddle(position, oldpos);
      displayInfo(totalScore);
      updateFlag = false;
    }

    oldball.x = ball.x;
    oldball.y = ball.y;
    checkBallPos();
    // Separate fcn: check if ball has hit a brick here...
    ball.x += xdir*speed;
    ball.y += ydir*speed;
    drawBall(ball, oldball);

    delay(20);
  }
  
}

void loop(){}
