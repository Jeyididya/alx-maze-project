#pragma once
#ifndef HEADER_H
#define HEADER_H

//standard library
#include <SDL2/SDL.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <float.h>
#include "upng.h"

//constants

#define PI 3.14159265
#define TWO_PI 6.28318530
#define TILE_SIZE 64
#define MAP_NUM_ROWS 13
#define MAP_NUM_COLS 20
#define SCREEN_WIDTH (MAP_NUM_COLS * TILE_SIZE)
#define SCREEN_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)
#define MINIMAP_SCALE_FACTOR 0.996
#define MAP_NUM_ROWS 13
#define MAP_NUM_COLS 20
#define FOV_ANGLE (60 * (PI / 180))
#define PROJ_PLANE ((SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2))
#define FPS 30
#define FRAME_TIME_LENGTH (1000 / FPS)
#define NUM_RAYS SCREEN_WIDTH
#define NUM_TEXTURES 8
typedef uint32_t color_t;

//variables
extern bool gameRunning;

//function in window file
bool initializedWindow(void);
void renderColorBuffer(void);
void destroyWindow(void);
void drawPixel(int x, int y, color_t color);
void clearColorBuffer(color_t color);

//function in main file
void destroyGame(void);
void setupGame(void);
void updateGame(void);
void renderGame(void);

//function in draw file
void drawRectangle(int x, int y, int width, int height, color_t color);
void drawLine(int x0, int y0, int x1, int y1, color_t color);

//function in rays file
void castAllRays(void);
void castRay(float rayAngle, int stripId);
void renderRays(void);
void horizontalInter(float rayAngle);
void verticalInter(float rayAngle);

//function in player file
void movePlayer(float DeltaTime);
void renderPlayer(void);

//function in ray_direction file
float distanceBetweenPoints(float x1, float y1, float x2, float y2);
bool isRayFacingUp(float angle);
bool isRayFacingDown(float angle);
bool isRayFacingLeft(float angle);
bool isRayFacingRight(float angle);

//function in input file
void SDL_KEYDOWN_FUNC(SDL_Event event);
void SDL_KEYUP_FUNC(SDL_Event event);
void handleInput(void);

//function in map file
bool DetectCollision(float x, float y);
bool isInsideMap(float x, float y);
void renderMap(void);
int getMapValue(int row, int col);

//structs for player
typedef struct player_s
{
	float x;
	float y;
	float width;
	float height;
	int turnDirection;
	int walkDirection;
	float rotationAngle;
	float walkSpeed;
	float turnSpeed;
} player_t;

//struct variable player
extern player_t player;

//structs for ray
typedef struct ray_s
{
	float rayAngle;
	float wallHitX;
	float wallHitY;
	float distance;
	bool wasHitVertical;
	int wallHitContent;
} ray_t;

//struct variable rays
extern ray_t rays[NUM_RAYS];

/**
 * struct texture_s - struct for the textures
 * @width: texture width
 * @height: texture height
 * @texture_buffer: pointer to texture buffer
 * @upngTexture: pointer to upng buffer
 *
 */

typedef struct texture_s
{
	int width;
	int height;
	color_t* texture_buffer;
	upng_t* upngTexture;
} texture_t;

texture_t wallTextures[NUM_TEXTURES];

void WallTexturesready(void);
void freeWallTextures(void);
/* Functions-variables-structs for walls */
void renderCeil(int wallTopPixel, color_t* texelColor, int x);
void renderFloor(int wallBottomPixel, color_t* texelColor, int x);
void changeColorIntensity(color_t* color, float factor);
void renderWall(void);
#endif
