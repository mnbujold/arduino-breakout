#include <Adafruit_ST7735.h>

#include "gameStats.h"
#include "breakout.h"


/* GLOBAL VARIABLES */
// keeps track of player score
int score = 0;
//keeps track of lives player has left
int lives = STARTING_LIVES;


/* FUNCTIONS */
// increase score by amount of points gathered
void increaseScore(int points)
{
    score += points;
    displayStats();
}

// lose a life
void decreaseLives()
{
    lives--;
    displayStats();
}

// returns score
int getScore()
{
    return score;
}

// returns lives left
int getLivesLeft()
{
    return lives;
}

// resets score to zero, lives to starting number of lives
void resetAll()
{
    score = 0;
    lives = STARTING_LIVES;
    displayStats();
}

// displays score and lives to bottom of screen
void displayStats()
{
    tft.setRotation(1);
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(1);
    
    tft.fillRect(0, 120, SCREEN_HEIGHT, 8, ST7735_BLACK);
    
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

// ends game, prints message to screen then stays in loop
void endGame()
{
    tft.setRotation(1);
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(2);
    
    tft.fillRect(0, 0, SCREEN_HEIGHT, SCREEN_WIDTH, ST7735_BLACK);
    
    tft.setCursor(24, 55);
    
    tft.print("GAME OVER!");
    tft.setRotation(0);
    
    while(true) {}
}

