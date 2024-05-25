#pragma once

#include <SDL3/SDL.h>
#include <map>
#include <vector>
#include "Zone.h"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 480

class App
{
private:
	bool _running;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;

	std::vector<Zone> zoneList;

	std::map<int, bool> keyboard;

	int currentZone;
	SDL_Texture *currentTileSet;


public:
	App(); // Used as our init function

	int onExecute();

	void onEvent(SDL_Event* Event);

	void onLoop();

	void onRender();

	void onCleanup();

	void generateLevelSet();
};