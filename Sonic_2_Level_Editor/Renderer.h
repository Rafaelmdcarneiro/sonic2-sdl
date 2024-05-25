#pragma once

#include <SDL.h>

struct Renderer
{
private:
	SDL_Renderer* renderer;

public:
	Renderer(SDL_Renderer* renderer);

	void renderRect(SDL_Rect rect, SDL_Color color);
	void renderFilledRect(SDL_Rect rect, SDL_Color color);
};

