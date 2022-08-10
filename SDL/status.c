#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "status.h"

void initStatusLives(GameState* gameState) {

	char str[64];
	SDL_Color color = { 255, 255, 255, 255 };

	sprintf(str, "x %u", gameState->player.hp); 

	SDL_Surface *temp = TTF_RenderText_Blended(gameState->font, str, color);
	gameState->labelWidth = temp->w;
	gameState->labelHeight = temp->h;
	gameState->label = SDL_CreateTextureFromSurface(gameState->renderer, temp);
	SDL_FreeSurface(temp);

}

void drawStatusLives(GameState* gameState) {

	SDL_SetRenderDrawColor(gameState->renderer, 0, 0, 0, 255);
	SDL_RenderClear(gameState->renderer);

	SDL_Rect player = { 780, 480, 64, 80 };
	SDL_RenderCopyEx(gameState->renderer, gameState->playerFrames[gameState->player.frame], NULL,
		&player, 0, NULL, gameState->player.flip);

	SDL_Rect textRect = { 850, 500, gameState->labelWidth, gameState->labelHeight};
	SDL_RenderCopy(gameState->renderer, gameState->label, NULL, &textRect);

}

void shutdownStatusLives(GameState* gameState) {

	SDL_DestroyTexture(gameState->label);
	gameState->label = NULL;

}