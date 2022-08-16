#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


#define PLAYER_FRAMES 6
#define ENEMIES_COUNT 100
#define BRICKS_COUNT 300

#define GRAVITY 0.1f
#define WIN_VALUE 20000

#define STATUS_LIVES 0
#define STATUS_GAME 1
#define STATUS_GAMEOVER 2
#define STATUS_VICTORY 3


// Structs definitions
typedef struct player{
	float x, y;
	float dy, dx;
	int flyTime;
	int frame;
	short hp;
	bool onBrick;
	bool isDead;
	SDL_RendererFlip flip;
}Player;

typedef struct enemy{
	float x, y;
}Enemy;

typedef struct brick{
	int x, y, h, w;
}Brick;

typedef struct gameState{

	// Screen scrolling
	float scrollX;

	// Players
	Player player;

	// Enemies
	Enemy enemies[ENEMIES_COUNT];

	// Bricks
	Brick bricks[BRICKS_COUNT];

	// Textures 
	SDL_Texture* playerFrames[PLAYER_FRAMES];
	SDL_Texture* enemyFrames;
	SDL_Texture* deadFrames;
	SDL_Texture* brickTexture;
	SDL_Texture* label;

	// Surfaces
	SDL_Surface* textSurface;

	// Fonts
	TTF_Font *font;

	// Renderer
	SDL_Renderer* renderer;

	// Other
	int time;
	int deathTime;
	int screenStatus;

}GameState;


// Functions prototypes
void doRender(SDL_Renderer* renderer, GameState* gameState);


#endif