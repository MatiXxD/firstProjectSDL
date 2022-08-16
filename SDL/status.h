#ifndef _STATUS_H_
#define _STATUS_H_

#include "main.h"


// Functions prototypes
void initStatusLives(GameState* gameState);
void initGameoverScreen(GameState* gameState);
void initVictoryScreen(GameState* gameState);
void drawStatusLives(GameState* gameState);
void drawFinalScreen(GameState* gameState);
void shutdownStatusLives(GameState* gameState);


#endif