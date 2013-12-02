#ifndef GAMESTATS_H
#define GAMESTATS_H

#include <Adafruit_ST7735.h>

/* DEFINITIONS */
#define STARTING_LIVES 3

/* SHARED FUNCTIONS */
void increaseScore(int points);
void decreaseLives();
int getScore();
int getLivesLeft();
void resetAll();
void displayStats();

#endif
