#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "status.h"

void initStatusLives(GameState* gameState) {

	char str[64];
	SDL_Color color = { 255, 255, 255, 255 };

	sprintf(str, "x %hd", gameState->player.hp); 

	gameState->textSurface = TTF_RenderText_Blended(gameState->font, str, color);
	gameState->label = SDL_CreateTextureFromSurface(gameState->renderer, gameState->textSurface);

}

void initGameoverScreen(GameState* gameState) {

	char str[64];
	SDL_Color color = { 255, 255, 255, 255 };

	sprintf(str, "Gameover.");

	gameState->textSurface = TTF_RenderText_Blended(gameState->font, str, color);
	gameState->label = SDL_CreateTextureFromSurface(gameState->renderer, gameState->textSurface);

}

void initVictoryScreen(GameState* gameState) {

	char str[64];
	SDL_Color color = { 255, 255, 255, 255 };

	sprintf(str, "You are won.");

	gameState->textSurface = TTF_RenderText_Blended(gameState->font, str, color);
	gameState->label = SDL_CreateTextureFromSurface(gameState->renderer, gameState->textSurface);

}

void drawFinalScreen(GameState* gameState) {

	SDL_SetRenderDrawColor(gameState->renderer, 0, 0, 0, 255);
	SDL_RenderClear(gameState->renderer);

	SDL_Rect textRect = { 850, 500, gameState->textSurface->w, gameState->textSurface->h };
	SDL_RenderCopy(gameState->renderer, gameState->label, NULL, &textRect);

}

void drawStatusLives(GameState* gameState) {

	SDL_SetRenderDrawColor(gameState->renderer, 0, 0, 0, 255);
	SDL_RenderClear(gameState->renderer);

	SDL_Rect player = { 780, 480, 64, 80 };
	SDL_RenderCopyEx(gameState->renderer, gameState->playerFrames[gameState->player.frame], NULL,
		&player, 0, NULL, gameState->player.flip);

	SDL_Rect textRect = { 850, 500, gameState->textSurface->w, gameState->textSurface ->h};
	SDL_RenderCopy(gameState->renderer, gameState->label, NULL, &textRect);

}

void shutdownStatusLives(GameState* gameState) {

	if(gameState->textSurface != NULL)
		SDL_FreeSurface(gameState->textSurface);
	if(gameState->label != NULL)
		SDL_DestroyTexture(gameState->label);
	gameState->textSurface = NULL;
	gameState->label = NULL;

}