#pragma once
#include <SDL.h>

// TODO: Fix this, it needs to work for resizing the window
static struct Settings {
private:
	int WINDOW_WIDTH;
	int WINDOW_HEIGHT;
	int OPTIONS_WIDTH;
	int SCREEN_WIDTH;

public:
	const int TILE_SIZE = 16;
	const int MENU_PADDING = 20;
	const int MAX_OPTIONS_WIDTH = 500;
	const int MIN_WINDOW_WIDTH = 1200;
	const int MIN_WINDOW_HEIGHT = 700;
	const int MIN_LEVEL_WIDTH = 100;
	const int MIN_LEVEL_HEIGHT = 64;

	Settings(int windowWidth, int windowHeight);
	void setScreenSizes(int windowWidth, int windowHeight);

	int getWindowWidth();
	int getWindowHeight();
	int getOptionsWidth();
	int getScreenWidth();
} settings(1200, 700);