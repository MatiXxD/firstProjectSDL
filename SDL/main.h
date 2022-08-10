#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


#define PLAYER_FRAMES 6
#define ENEMY_FRAMES 6
#define ENEMIES_COUNT 20 
#define BRICKS_COUNT 10

#define GRAVITY 0.1f

#define STATUS_LIVES 0
#define STATUS_GAME 1
#define STATUS_GAMEOVER 2


// Structs definitions
typedef struct player{
	float x, y;
	float dy, dx;
	char* name;
	unsigned hp;
	int flyTime;
	int frame;
	bool onBrick;
	SDL_RendererFlip flip;
}Player;

typedef struct enemy{
	float x, y;
}Enemy;

typedef struct brick{
	int x, y, h, w;
}Brick;

typedef struct gameState{

	// Players
	Player player;

	// Enemies
	Enemy enemies[ENEMIES_COUNT];

	// Bricks
	Brick bricks[BRICKS_COUNT];

	// Textures 
	SDL_Texture* playerFrames[PLAYER_FRAMES];
	SDL_Texture* enemyFrames[ENEMY_FRAMES];
	SDL_Texture* brickTexture;
	SDL_Texture* label;

	// Images properties
	int labelWidth;
	int labelHeight;

	// Fonts
	TTF_Font *font;

	// Renderer
	SDL_Renderer* renderer;

	// Other
	int time;
	int screenStatus;

}GameState;


// Functions prototypes
void doRender(SDL_Renderer* renderer, GameState* gameState);


#endif