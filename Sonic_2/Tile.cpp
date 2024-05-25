#include "Tile.h"

Tile::Tile()
{
	this->color.r = 255;
	this->color.g = 0;
	this->color.b = 212;
	this->color.a = 255;

	this->texture = nullptr;
}

Tile::Tile(SDL_Color color)
{
	this->color = color;
	this->texture = nullptr;
}