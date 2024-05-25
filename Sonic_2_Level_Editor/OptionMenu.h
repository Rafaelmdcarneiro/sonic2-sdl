#pragma once
#include <vector>

#include "OptionItem.h"
#include "Settings.h"

class OptionMenu
{
private:
	SDL_Color backgroundColor;
	SDL_Renderer* renderer;
	TTF_Font* font;

	SDL_Rect* tileSetRect;

public:
	std::vector<OptionItem> options;
	
	OptionMenu(SDL_Renderer* renderer, TTF_Font* font, SDL_Color background);

	void updateTileSetRect(float* screenSizes);
	void renderTileSet(SDL_Texture* tileSet);
	void addMenuItem(Type type, std::string itemName, std::string itemText, std::string labelText = "", bool inlineWithPrev = false);
	void updateMenu();
};

