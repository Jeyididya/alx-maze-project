#include "../headers/header.h"

static SDL_Renderer *renderer;
static color_t *colorBuffer;
static SDL_Texture *colorBufferTexture;
static SDL_Window *win;

/**
 * initializedWindow - Initialize the window to render the maze
 * return - true of false
 */

bool initializedWindow(void)
{

	SDL_DisplayMode display_mode;
	int fullScreenWidth, fullScreenHeight;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error initializing SDL.\n");
		return (false);
	}
	SDL_GetCurrentDisplayMode(0, &display_mode);
	fullScreenWidth = display_mode.w;
	fullScreenHeight = display_mode.h;
	win = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		fullScreenWidth,
		fullScreenHeight,
		SDL_WINDOW_BORDERLESS
	);
	if (!win)
	{
		fprintf(stderr, "Error creating SDL window.\n");
		return (false);
	}
	renderer = SDL_CreateRenderer(win, -1, 1);
	if (!renderer)
	{
		fprintf(stderr, "Error creating SDL renderer.\n");
		return (false);
	}
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	/* allocate the total amount of bytes in memory to hold our colorbuffer */
	colorBuffer = malloc(sizeof(color_t) * SCREEN_WIDTH * SCREEN_HEIGHT);

	/* create an SDL_Texture to display the colorbuffer */
	colorBufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	return (true);
}

/**
 * clearColorBuffer - clear buffer for every frame
 * @color: color buffer
 */
void clearColorBuffer(color_t color)
{
	int i;

	for (i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
		colorBuffer[i] = color;
}
/**
 * destroyWindow - destroy window and subsystem when the game is over.
 */
void destroyWindow(void)
{
	free(colorBuffer);
	SDL_DestroyTexture(colorBufferTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
/**
 * renderColorBuffer - render buffer for every frame
 */
void renderColorBuffer(void)
{
	SDL_UpdateTexture(colorBufferTexture, NULL, colorBuffer, 
			  (int)(SCREEN_WIDTH * sizeof(color_t))
			 );
	SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}
/**
 * drawPixel - assign a color to each pixel
 * @x: x  pixel coordinate
 * @y: y pixel coordinate 
 * @color: color buffer
 */
void drawPixel(int x, int y, color_t color)
{
	colorBuffer[(SCREEN_WIDTH * y) + x] = color;
}



