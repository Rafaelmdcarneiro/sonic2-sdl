#include "Settings.h"


Settings::Settings(int windowWidth, int windowHeight) {
	setScreenSizes(windowWidth, windowHeight);
}

void Settings::setScreenSizes(int windowWidth, int windowHeight) {
	WINDOW_HEIGHT = windowHeight;
	WINDOW_WIDTH = windowWidth;

	OPTIONS_WIDTH = (WINDOW_WIDTH / 3) < MAX_OPTIONS_WIDTH ? WINDOW_WIDTH / 3 : MAX_OPTIONS_WIDTH;
	SCREEN_WIDTH = WINDOW_WIDTH - OPTIONS_WIDTH;
}

int Settings::getWindowWidth()
{
	return WINDOW_WIDTH;
}

int Settings::getWindowHeight()
{
	return WINDOW_HEIGHT;
}

int Settings::getOptionsWidth()
{
	return OPTIONS_WIDTH;
}

int Settings::getScreenWidth()
{
	return SCREEN_WIDTH;
}
