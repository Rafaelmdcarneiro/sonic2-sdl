#include "OptionMenu.h"

OptionMenu::OptionMenu(SDL_Renderer* renderer, TTF_Font* font, SDL_Color background)
{
	this->renderer = renderer;
	this->font = font;
	this->backgroundColor = background;
	this->tileSetRect = new SDL_Rect{ 0, 0, 0, 0 };

	float initValues[3] = { 
		settings.getWindowHeight(), 
		settings.getScreenWidth(), 
		settings.getOptionsWidth() };
	updateTileSetRect(initValues);
}

void OptionMenu::updateTileSetRect(float* screenSizes)
{
	tileSetRect->x = screenSizes[1] + settings.MENU_PADDING;
	tileSetRect->y = settings.MENU_PADDING;
	tileSetRect->w = screenSizes[2] - (settings.MENU_PADDING * 2);
	tileSetRect->h = screenSizes[2] - (settings.MENU_PADDING * 2);
}

void OptionMenu::renderTileSet(SDL_Texture* tileSet)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 120);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderDrawRect(renderer, tileSetRect);
	SDL_RenderCopy(renderer, tileSet, NULL, tileSetRect);
}

void OptionMenu::addMenuItem(Type type, std::string itemName, std::string itemText, std::string labelText, bool inlineWithPrev)
{
	int itemX = settings.MENU_PADDING;
	int itemY = settings.getOptionsWidth();
	if (!inlineWithPrev) {
		for (OptionItem item : options) {
			if (item.rect->y >= itemY) itemY = item.rect->y + 50;
		}
	}
	else {
		itemX = options.back().rect->x + options.back().rect->w + 20 - settings.getScreenWidth();
		itemY = options.back().rect->y;
	}

	if (labelText != "") {
		this->options.push_back(OptionItem(renderer, font, Label, itemName + "Label", labelText, new SDL_Rect{ settings.MENU_PADDING, itemY, -1, -1 }, false));

		this->options.push_back(OptionItem(renderer, font, type, itemName, itemText, new SDL_Rect{ itemX + options.back().rect->w, itemY, settings.getOptionsWidth() - (settings.MENU_PADDING * 2) - options.back().rect->w, -1}, true));
	}
	else {
		this->options.push_back(OptionItem(renderer, font, type, itemName, itemText, new SDL_Rect{ itemX, itemY, -1, -1 }, inlineWithPrev));
	}

	
}

void OptionMenu::updateMenu()
{
}
