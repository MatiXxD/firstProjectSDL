#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>

#define PLAYER_FRAMES 6
#define ENEMY_FRAMES 6
#define ENEMIES_COUNT 20 
#define BRICKS_COUNT 10

#define GRAVITY 0.1f

typedef struct{
	float x, y;
	float dy, dx;
	char* name;
	int flyTime;
	int frame;
	bool onBrick;
	SDL_RendererFlip flip;
}Player;

typedef struct {
	float x, y;
}Enemy;

typedef struct {
	int x, y, h, w;
}Brick;

typedef struct {

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

	// Renderer
	SDL_Renderer* renderer;

	// Other
	int time;

}GameState;


void processEvents(SDL_Window* window, int* done, GameState* gameState) {

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_WINDOWEVENT: {
			if (event.window.event == SDL_WINDOWEVENT_CLOSE)
				*done = 1;
		} break;
		case SDL_KEYDOWN: {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				*done = 1;
				break;
			case SDLK_w:
				if (gameState->player.onBrick) {
					gameState->player.dy = -3.5f;
					gameState->player.flyTime = 0;
					gameState->player.onBrick = false;
				}
				break;
			}
		} break;
		case SDL_QUIT: {
			*done = 1;
		} break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);

	// Extra jumping
	if (state[SDL_SCANCODE_W] && gameState->player.flyTime < 50) {
		gameState->player.dy -= 0.1f;
		gameState->player.flyTime++;
	}
	

	// Walking
	if (state[SDL_SCANCODE_D]) {
		gameState->player.dx += 0.1f;
		if (gameState->player.dx > 1.0f)
			gameState->player.dx = 1.0f;
		gameState->player.flip = SDL_FLIP_NONE;
	}
	else if (state[SDL_SCANCODE_A]) {
		gameState->player.dx -= 0.1f;
		if (gameState->player.dx < -1.0f)
			gameState->player.dx = -1.0f;
		gameState->player.flip = SDL_FLIP_HORIZONTAL;
	}
	else {
		gameState->player.dx *= 0.9f;
		if (fabsf(gameState->player.dx) < 0.1f) {
			gameState->player.frame = 0;
			gameState->player.dx = 0.0f;
		}
	}

}

void doRender(SDL_Renderer* renderer, GameState* gameState) {

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// Drawing player
	SDL_Rect player = { gameState->player.x, gameState->player.y, 64, 80 };
	SDL_RenderCopyEx(renderer, gameState->playerFrames[gameState->player.frame], NULL,
		&player, 0, NULL, gameState->player.flip);

	// Drawing enemies from array
	/*for (int i = 0; i < ENEMIES_COUNT; i++) {
		SDL_Rect enemy = { gameState->enemies[i].x, gameState->enemies[i].y, 64, 80 };
		SDL_RenderCopyEx(renderer, gameState->enemyFrames[0], NULL,
			&enemy, 0, NULL, SDL_FLIP_NONE);
	}*/

	// Drawing bricks
	for (int i = 0; i < BRICKS_COUNT; i++) {
		SDL_Rect brickRect = { gameState->bricks[i].x, gameState->bricks[i].y,
			gameState->bricks[i].w, gameState->bricks[i].h };
		SDL_RenderCopy(renderer, gameState->brickTexture, NULL, &brickRect);
	}

	// Present what we draw
	SDL_RenderPresent(renderer);

}

void loadTexture(SDL_Texture** texture, SDL_Renderer* renderer, const char* file) {

	SDL_Surface* surface = NULL;
	surface = IMG_Load(file);
	if (surface == NULL) {
		printf("Can't find file %s!\n", file);
		SDL_Quit();
		exit(1);
	}
	*texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

}

void loadGame(GameState* gameState) {

	const char* playerFiles[PLAYER_FRAMES] = {"Textures/Player/Frame1.png", "Textures/Player/Frame2.png",
		"Textures/Player/Frame3.png", "Textures/Player/Frame4.png", "Textures/Player/Frame5.png",
		"Textures/Player/Frame6.png" };
	const char* enemyFiles[ENEMY_FRAMES] = { "Textures/Enemy/Frame1.png", "Textures/Enemy/Frame2.png",
		"Textures/Enemy/Frame3.png", "Textures/Enemy/Frame4.png", "Textures/Enemy/Frame5.png",
		"Textures/Enemy/Frame6.png" };
	
	// Load textures
	for(int i = 0 ; i < PLAYER_FRAMES ; i++)												// Player frames
		loadTexture(&gameState->playerFrames[i], gameState->renderer, playerFiles[i]);
	for (int i = 0; i < PLAYER_FRAMES; i++)													// Enemy frames
		loadTexture(&gameState->enemyFrames[i], gameState->renderer, enemyFiles[i]);
	loadTexture(&gameState->brickTexture, gameState->renderer, "Textures/Brick.png");

	// Init player
	gameState->player.x = 0;
	gameState->player.y = 920;
	gameState->player.dy = 0;
	gameState->player.dx = 0;
	gameState->player.onBrick = false;
	gameState->player.flyTime = 0;
	gameState->player.frame = 0;
	gameState->player.flip = SDL_FLIP_NONE;

	// Init game time
	gameState->time = 0;

	// Init enemies
	for (int i = 0; i < ENEMIES_COUNT; i++) {
		gameState->enemies[i].x = rand() % 1920;
		gameState->enemies[i].y = rand() % 1080;
	}
	
	// Init bricks
	for (int i = 0; i < BRICKS_COUNT; i++) {
		gameState->bricks[i].w = 256;
		gameState->bricks[i].h = 64;
		gameState->bricks[i].x = 256 * i;
		gameState->bricks[i].y = 1080 - 64;
	}
	gameState->bricks[BRICKS_COUNT - 1].x = 350;
	gameState->bricks[BRICKS_COUNT - 1].y = 700;

}

void collisionDetect(GameState* gameState) {

	// Should add corners check  
	for (int i = 0; i < BRICKS_COUNT; i++) {

		float pw = 64, ph = 80;
		float px = gameState->player.x, py = gameState->player.y;
		float bw = gameState->bricks[i].w, bh = gameState->bricks[i].h;
		float bx = gameState->bricks[i].x, by = gameState->bricks[i].y;

		// Check for collisions with top/bot side of the brick
		if (px + pw > bx && px < bx + bw) {

			if (py < by + bh && py > by && gameState->player.dy < 0) {
				// Correct player's position
				gameState->player.y = by + bh;
				py = by + bh;
				// Make velocity from jump equal 0
				gameState->player.dy = 0;
				gameState->player.onBrick = true;
			}
			else if (py + ph > by && py < by && gameState->player.dy > 0) {
				// Correct player's position
				gameState->player.y = by - ph;
				py = by - ph;
				// Make velocity from jump equal 0
				gameState->player.dy = 0;
				gameState->player.onBrick = true;
			}

		}

		// Check for collisions with left/right side of the brick
		if (py + ph > by && py < by + bh) {	

			if (px < bx + bw && px + pw > bx + bw && gameState->player.dx < 0) {		// Right side of the brick 
				gameState->player.x = bx + bw;
				px = gameState->player.x;		
				gameState->player.dx = 0;
			}																
			else if (px < bx && px + pw > bx && gameState->player.dx > 0) {				// Left side of the brick 
				gameState->player.x = bx - pw;
				px = gameState->player.x;
				gameState->player.dx = 0;
			}

		}

	}

}

void process(GameState* gameState) {

	Player* player = &gameState->player;

	// Player movement
	player->y += player->dy;
	player->x += player->dx;
	player->dy += GRAVITY;

	// Player animation
	if (player->dx != 0 && player->onBrick) {
		if (!(gameState->time % 50)) {
			player->frame++;
			if (player->frame == PLAYER_FRAMES)
				player->frame = 0;
		}
	}

	// Collision detection
	collisionDetect(gameState);

	// Changing time
	gameState->time++;

}


int main(int argc, char* argv[]) {

	GameState gameState;
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_Init(SDL_INIT_VIDEO);
	srand((unsigned int)time(NULL));

	window = SDL_CreateWindow("Game Window",
							  SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED,
							  1920,
							  1080,
							  0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	gameState.renderer = renderer;

	loadGame(&gameState);

	int done = 0;
	SDL_Event event;
	while (!done) {

		processEvents(window, &done, &gameState);
		process(&gameState);
		doRender(renderer, &gameState);

		//SDL_Delay(10);

	}

	// Destroying textures
	for (int i = 0; i < PLAYER_FRAMES; i++) 
		SDL_DestroyTexture(gameState.playerFrames[i]);
	for (int i = 0; i < ENEMY_FRAMES; i++)
		SDL_DestroyTexture(gameState.enemyFrames[i]);

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;

}