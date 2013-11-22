#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

/* PRE-PROCESSOR DIRECIVES */
#define TFT_CS 6  // CS line for TFT display
#define TFT_DC 7  // Data/command line for TFT
#define TFT_RST 8 // Reset line for TFT

/* GLOBAL VARS */
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Joystick Pins
const int VERT = 0;
const int HOR = 1;
const int SEL = 9;


void setup(){
  // Start serial communication for debugging
  Serial.begin(9600);
  
  tft.initR(INITR_REDTAB);
  pinMode(SEL, INPUT);
  digitalWrite(SEL, HIGH);

  tft.fillScreen(ST7735_BLACK);

}

void loop(){}
