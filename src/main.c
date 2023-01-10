#include "../headers/header.h"

bool gameRunning = false;
int TicksLastFrame = 0;
player_t player;

/**
* updateGame - update delta time per frame
*/

void updateGame(void)
{
	float DeltaTime;
	int timeToWait = FRAME_TIME_LENGTH - (SDL_GetTicks() - TicksLastFrame);

	if (timeToWait > 0 && timeToWait <= FRAME_TIME_LENGTH)
	{
		SDL_Delay(timeToWait);
	}
	DeltaTime = (SDL_GetTicks() - TicksLastFrame) / 1000.0f;

	TicksLastFrame = SDL_GetTicks();

	movePlayer(DeltaTime);
}

/**
* setupGame - initialize player and load wall textures
*/
void setupGame(void)
{

	player.x = SCREEN_WIDTH / 2;
	player.y = SCREEN_HEIGHT / 2;
	player.width = 10;
	player.height = 30;
	player.walkDirection = 0;
	player.walkSpeed = 100;
	player.turnDirection = 0;
	player.turnSpeed = 45 * (PI / 180);
	player.rotationAngle = PI / 2;
}

/**
* renderGame - calls all functions for rendering
*/

void renderGame(void)
{


	renderMap();
	renderRays();
	renderPlayer();

	renderColorBuffer();
}

/**
* DestroyGame - free wall textures and destroy window
*/

void destroyGame(void)
{
	//freeWallTextures();
	destroyWindow();

}

/**
* main - entry point
* Return: 0
*/

int main(void)
{
	gameRunning = initializedWindow();
	setupGame();

	while (gameRunning)

	{
		handleInput();
		updateGame();
		renderGame();
		
	}
	destroyWindow();
	return (0);
}
