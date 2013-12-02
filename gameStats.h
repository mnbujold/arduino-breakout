#ifndef GAMESTATS_H
#define GAMESTATS_H

/* DEFINITIONS */
#define STARTING_LIVES 3

/* SHARED FUNCTIONS */
void increaseScore(int points);
void decreaseLives();
int getScore();
int getLivesLeft();
void resetAll();
void displayStats();
void endGame();

#endif
