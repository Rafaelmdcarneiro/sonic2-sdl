#include <iostream>

#include "OptionItem.h"

/* If color is excluded, then the default is black. Alpha is ignored in the color.
If -1 is given as the rect width/height then the text width/height is used.
The X coordinate given to the rect is in relation to the option window.
*/
OptionItem::OptionItem(SDL_Renderer* renderer, TTF_Font* font, Type type, std::string name, 
	std::string bodyText, SDL_Rect* rect, bool inLine, SDL_Color color)
{
	this->renderer = renderer;
	this->font = font;

	this->type = type;

	this->name = name;
	this->text = bodyText;
	this->defaultText = bodyText;

	this->rect = rect;
	this->color = color;
	this->inLine = inLine;

	this->rect->x += settings.getScreenWidth();

	// Below is math for centering text
	calculateTextSize();

	if (this->rect->w < 0) this->rect->w = textSize[0] + (settings.MENU_PADDING * 2);
	if (this->rect->h < 0) this->rect->h = textSize[1];

	if (this->type == Button) this->rect->y = settings.getWindowHeight() - settings.MENU_PADDING - this->rect->h;

	this->textRect = new SDL_Rect(*rect);
	textRect->x += settings.MENU_PADDING;


	updateText();
}

// Calculate the width and height of the option text
void OptionItem::calculateTextSize()
{
	TTF_SizeUTF8(font, text.c_str(), &textSize[0], &textSize[1]);
}

// Render the option item on screen
void OptionItem::render()
{	
	if ((type == Button || type == TextInput|| type == NumberInput) && this->selected) SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 220);
	else if ((type == Button || type == TextInput || type == NumberInput) && this->hovered) SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 190);
	else SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 120);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, rect);

	
	SDL_RenderCopy(renderer, message, NULL, textRect);
	//SDL_RenderTexture(renderer, message, NULL, textRect);
}

void OptionItem::onType(char ch)
{
	if (type == TextInput || type == NumberInput) {
		// Backspace
		if (ch == 8 && text.size() > 0) {
			text.pop_back();
		}
		// Numbers
		else if ((ch >= 48 && ch <= 57)) {
			text.push_back(ch);
		}
		// Space
		else if (type != NumberInput && ch == 32) {
			text.push_back(' ');
		}
		// Lowercase/Uppercase
		else if (type != NumberInput && ((ch >= 97 && ch <= 122))) {
			if (SDL_GetModState() & KMOD_SHIFT) text.push_back(ch - 32);
			else text.push_back(ch);
		}

		updateText();
	}
}

void OptionItem::updatePosition(float* oldWindowSizes, float* newWindowSizes)
{
	float screenSizeDifference[] = {
		newWindowSizes[0] - oldWindowSizes[0],
		newWindowSizes[1] - oldWindowSizes[1],
		newWindowSizes[2] - oldWindowSizes[2],
	};

	this->rect->x += screenSizeDifference[1];
	this->textRect->x += screenSizeDifference[1];

	if (this->type != Button) {
		this->rect->y += screenSizeDifference[2];
		this->textRect->y += screenSizeDifference[2];
	}
	else {
		this->rect->y += screenSizeDifference[0];
		this->textRect->y += screenSizeDifference[0];
	}

	if (this->inLine && this->type != Label && this->type != Button) {
		this->rect->w += screenSizeDifference[2];
	}
}

// Update text size/length/position
void OptionItem::updateText()
{
	calculateTextSize();
	textRect->w = textSize[0];
	textRect->h = textSize[1];
	surface = TTF_RenderUTF8_Blended(font, text.c_str(), { 255, 255, 255, 255 });
	message = SDL_CreateTextureFromSurface(renderer, surface);
}

void OptionItem::returnToDefault()
{
	this->color = { 0, 0, 0 };
	this->text = defaultText;
}