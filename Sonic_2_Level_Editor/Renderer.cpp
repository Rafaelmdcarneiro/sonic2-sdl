#include "Renderer.h"

Renderer::Renderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

void Renderer::renderRect(SDL_Rect rect, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderDrawRect(renderer, &rect);
}

void Renderer::renderFilledRect(SDL_Rect rect, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &rect);
}
