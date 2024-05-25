#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

#include "Settings.h"

enum Type { Button, Label, TextInput, NumberInput };

struct OptionItem
{
private:
	int textSize[2];
	SDL_Rect* textRect;

	SDL_Surface* surface = nullptr;
	SDL_Texture* message = nullptr;

	SDL_Renderer* renderer;
	TTF_Font* font;

	std::string defaultText;
public:
	SDL_Rect* rect;
	bool hovered = false;
	bool selected = false;
	bool inLine = false;

	Type type;
	std::string name, text;
	SDL_Color color;

	OptionItem(SDL_Renderer* renderer, TTF_Font* font, Type type, std::string name, std::string bodyText, SDL_Rect* rect, bool inLine, SDL_Color color = { 0, 0, 0 });
	void calculateTextSize();
	void render();
	void onType(char ch);
	void updatePosition(float* oldWindowSizes, float* newWindowSizes);
	void updateText();
	void returnToDefault();
};
