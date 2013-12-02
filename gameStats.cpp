#include <Adafruit_ST7735.h>

#include "gameStats.h"
#include "breakout.h"


/* GLOBAL VARIABLES */
// keeps track of player score
int score = 0;
//keeps track of lives player has left
int lives = STARTING_LIVES;


/* FUNCTIONS */
void increaseScore(int points)
{
    score += points;
}

void decreaseLives()
{
    lives--;
}

int getScore()
{
    return score;
}

int getLivesLeft()
{
    return lives;
}

void resetAll()
{
    score = 0;
    lives = STARTING_LIVES;
}

void displayStats()
{
    tft.setRotation(1);
    
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(1);
    
    tft.fillRect(0,120,50,8,ST7735_BLACK);
    
    tft.setCursor(0,120);
    
    tft.print("Score:");
    tft.print(score);
    
    tft.setCursor(100,120);
    
    tft.print("Lives:");
    if(lives == 3)
        tft.print("ooo");
    else if(lives == 2)
        tft.print("oo");
    else if(lives == 1)
        tft.print("o");

    tft.setRotation(0);
}

