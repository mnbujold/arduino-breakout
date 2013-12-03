#ifndef BALL_H
#define BALL_H

#include "breakout.h"

/* DEFINITIONS */
#define BALL_RADIUS 3

/* SHARED FUNCTIONS */
void drawBall();
void initializeBall();
void updateBallPos(int paddlePos);
bool ballOnPaddle();
void launchBall();

#endif

