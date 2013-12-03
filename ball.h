#ifndef BALL_H
#define BALL_H

#include "breakout.h"

/* DEFINITIONS */
#define BALL_RADIUS 2

/* SHARED FUNCTIONS */
void drawBall();
void initializeBall(int paddlePos);
void updateBallPos(int paddlePos);
bool ballOnPaddle();
void launchBall();

#endif

