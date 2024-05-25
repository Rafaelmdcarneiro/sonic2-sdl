#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <map>
#include <vector>

#include "Settings.h"
#include "Mouse.h"
#include "Keyboard.h"

#include "OptionItem.h"
#include "Zone.h"
#include "Renderer.h"
#include "OptionMenu.h"

class App
{
private:
	bool _running;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;
	TTF_Font* font = NULL;

	Renderer* gameRenderer;
	OptionMenu* optionMenu;
	
	int tileScreenSize = 0;
	int activeTile = 0;

	float camX, camY;
	//float mouseX, mouseY;
	//float movementX, movementY;
	//int mouseWheel;

	int tileSize;

	Zone* currentZone;
	OptionItem* selectedItem;

	//std::map<int, bool> keyboard;
	//std::map<int, bool> mouse;

	SDL_Texture* currentTileSet;

public:
	//static int WINDOW_WIDTH;// 1200;
	//static int WINDOW_HEIGHT;// 800;
	//static int OPTIONS_WIDTH;// (WINDOW_WIDTH / 3) > 500 ? WINDOW_WIDTH / 3 : 500; // A third of the window width, or max of 500
	//static int SCREEN_WIDTH;// WINDOW_WIDTH - OPTIONS_WIDTH; // Whatever part of the screen the options window does not fill
	//static const int TILE_SIZE = 16;
	//static const int MENU_PADDING = 20;

	//static void setScreenSizes(int windowWidth, int windowHeight);

	//static Settings* settings;// = new Settings(1200, 700);

	App(); // Used as our init function

	int onExecute();

	void onEvent(SDL_Event* Event);

	void onLoop();

	void onRender();

	void onCleanup();

	void loadDefaultZone();

	void updateTileScreenSize();

	//static void setSettings(int windowWidgth, int windowHeight);
	//static Settings* getSettings();

	//int resizeWindow(void* data, SDL_Event* event);
};