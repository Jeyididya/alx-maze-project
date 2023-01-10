#include "../headers/header.h"

/**
 * SDL_KEYDOWN_FUNC - when key is down process input
 * @event: union that contains structures for the event types
 */

void SDL_KEYDOWN_FUNC(SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_ESCAPE)
		gameRunning = false;
	if (event.key.keysym.sym == SDLK_UP)
		player.walkDirection = -1;
	if (event.key.keysym.sym == SDLK_DOWN)
		player.walkDirection = +1;
	if (event.key.keysym.sym == SDLK_RIGHT)
		player.turnDirection = +1;
	if (event.key.keysym.sym == SDLK_LEFT)
		player.turnDirection = -1;
}

/**
 * SDL_KEYUP_FUNC - when key is up process input
 * @event: union that contains structures for the event types
 */

void SDL_KEYUP_FUNC(SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_UP)
		player.walkDirection = 0;
	if (event.key.keysym.sym == SDLK_DOWN)
		player.walkDirection = 0;
	if (event.key.keysym.sym == SDLK_RIGHT)
		player.turnDirection = 0;
	if (event.key.keysym.sym == SDLK_LEFT)
		player.turnDirection = 0;
}

/**
 * handleInput - process input from the keyboard
 */

void handleInput(void)
{
	SDL_Event event;

	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT)
		gameRunning = false;
	else if (event.type == SDL_KEYDOWN)
		SDL_KEYDOWN_FUNC(event);
	else if (event.type == SDL_KEYUP)
		SDL_KEYUP_FUNC(event);	
}
