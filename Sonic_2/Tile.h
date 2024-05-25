#pragma once
#include <SDL3/SDL_render.h>

#define TILE_SIZE 16

struct Tile
{
	SDL_Color color;
	SDL_Texture* texture;

	Tile();
	Tile(SDL_Color color);
};

