#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

/* PRE-PROCESSOR DIRECIVES */
#define TFT_CS 6  // CS line for TFT display
#define TFT_DC 7  // Data/command line for TFT
#define TFT_RST 8 // Reset line for TFT

#define SCREEN_HEIGHT tft.width()
#define SCREEN_WIDTH tft.height()

/* GLOBAL VARS */
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


typedef struct Point {
  int x;
  int y;
} Point;


void drawPaddle(int position, int oldpos){
  /* Draws the paddle at the bottom of the screen */
  int vert = 10;
 
  // Draw the paddle 
  tft.fillRect(vert, oldpos, PADDLE_HEIGHT, PADDLE_WIDTH, ST7735_BLACK);
  tft.fillRect(vert, position, PADDLE_HEIGHT, PADDLE_WIDTH, ST7735_WHITE);

}

void drawBall(Point p, Point old){
  tft.fillCircle(p.x, p.y, 3, ST7735_WHITE);
  tft.fillCircle(old.x, old.y, 3, ST7735_BLACK);

}

Point checkBallPos(Point p){
  
  Point r;

  if(p.x > SCREEN_WIDTH){
    r.x = SCREEN_WIDTH;
  }
  if(p.x < 0){
    r.x = 0;
  }

  if(p.y > SCREEN_HEIGHT){
    r.y = SCREEN_HEIGHT;
  }
  if(p.y < 0){
    r.y = 0;
  }

  return r;

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
  // Calibrate 'centre' position of joystick
  X_CENTRE = analogRead(HOR);
  pinMode(SEL, INPUT);
  digitalWrite(SEL, HIGH);
  // TODO: Check if joystick is depressed here at startup to use accelerometer for control instead
  // Initialize screen
  tft.initR(INITR_REDTAB);
  tft.fillScreen(ST7735_BLACK);
  int position = SCREEN_WIDTH/2;
  int oldpos;

  Point ball;
  ball.x = SCREEN_WIDTH/2;
  ball.y = SCREEN_HEIGHT/2;
  Point oldball;
  oldball.x = 0;
  oldball.y = 0;

  bool updateFlag = false;
  drawPaddle(position, 0);
  // TODO: Add initial brick drawing routine here

  drawBall(ball, oldball);

  // Main program loop
  while(1){
    oldpos = position;
    position = readJoystick(position);
    if(position != oldpos)
      updateFlag = !updateFlag;
    if(updateFlag){
      drawPaddle(position, oldpos);
      updateFlag = false;
    }

    oldball.x = ball.x;
    oldball.y = ball.y;
    ball.x += 1;
    ball.y += 1;
    ball = checkBallPos(ball);
    drawBall(ball, oldball);

    delay(20);
  }
  
}

void loop(){}
