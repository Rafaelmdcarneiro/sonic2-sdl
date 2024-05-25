#include "App.h"
#include <SDL3/SDL_image.h>


App::App()
{
	_running = true;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Sonic 2", SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, 0);
	renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderScale(renderer, 2, 2);

	currentZone = 0;

	SDL_Surface* tileSetSurface = IMG_Load("../Zone Tilesets/Emerald_Hill.png");
	Uint32 colorkey = SDL_MapRGB(tileSetSurface->format, 203, 0, 212);
	SDL_SetSurfaceColorKey(tileSetSurface, SDL_TRUE, colorkey);
	currentTileSet = SDL_CreateTextureFromSurface(renderer, tileSetSurface);

	onExecute();
}

int App::onExecute()
{
	float timeA, timeB = 0;
	generateLevelSet();

	SDL_Event event;
	while (_running) {
		while (SDL_PollEvent(&event)) {
			onEvent(&event);
		}

		timeA = SDL_GetTicks();
		float deltaTime = timeA - timeB;
		if (deltaTime > 1000 / 20.0) {
			timeB = timeA;
			onLoop();
			onRender();
		}
	}

	onCleanup();
	return 0;
}

void App::onEvent(SDL_Event* event)
{
	switch (event->type) {
	case SDL_EVENT_QUIT:
		_running = false;
		break;
	case SDL_EVENT_KEY_DOWN:
		keyboard[event->key.keysym.sym] = true;
		break;
	case SDL_EVENT_KEY_UP:
		keyboard[event->key.keysym.sym] = false;
		break;
	}
}

void App::onLoop()
{
	if (keyboard[SDLK_a]) {
		printf("Moving Left\n");

	}
	if (keyboard[SDLK_d]) {
		printf("Moving Right\n");

	}
	if (keyboard[SDLK_w]) {
		printf("Looking Up\n");
	}
	if (keyboard[SDLK_s]) {
		printf("Looking Down\n");
	}
	if (keyboard[SDLK_SPACE]) {
		printf("Jumping\n");
	}
}

void App::onRender()
{
	//SDL_SetRenderDrawColor(renderer, 0, 34, 204, 255);
	for (Zone zone : zoneList) {
		if (zone.getZoneId() + zone.getActNo() == currentZone) {

			SDL_SetRenderDrawColor(renderer, zone.backgroundColor.r, zone.backgroundColor.g, zone.backgroundColor.b, zone.backgroundColor.a);
			SDL_RenderClear(renderer);

			for (int i = 0; i < zone.getLevelMap().size(); i++) {
				if (zone.getLevelMap()[i] > 0) {
					Tile tile = zone.getTileFromId(zone.getLevelMap()[i - 1]);

					SDL_FRect worldTile;
					worldTile.x = (i % zone.getZoneWidth()) * TILE_SIZE;
					worldTile.y = (i / zone.getZoneWidth()) * TILE_SIZE;
					worldTile.w = TILE_SIZE;
					worldTile.h = TILE_SIZE;

					SDL_FRect textureTile;
					textureTile.x = (zone.getLevelMap()[i] % 20) * TILE_SIZE;
					textureTile.y = (zone.getLevelMap()[i] / 20) * TILE_SIZE;
					textureTile.w = TILE_SIZE;
					textureTile.h = TILE_SIZE;

					SDL_SetRenderDrawColor(renderer, tile.color.r, tile.color.g, tile.color.b, tile.color.a);
					//SDL_RenderFillRect(renderer, &worldTile);
					SDL_RenderTexture(renderer, currentTileSet, &textureTile, &worldTile);
					//SDL_RenderTextureRotated(renderer, currentTileSet, &textureTile, &worldTile, 0.0, NULL, SDL_FLIP_HORIZONTAL);
				}
			}
		}
	}

	//pixels[(10 * SCREEN_WIDTH) + 5] = 0xFFFF00FF;
	//SDL_UpdateTexture(texture, NULL, pixels, SCREEN_WIDTH * 4);
	SDL_RenderPresent(renderer);
}

void App::onCleanup()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void App::generateLevelSet() {
	zoneList.push_back(Zone("Emerald Hill", 0, 0, 10, 10, 
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 103, 104, 0, 0, 0, 0, 0, 0, 0, 0,
		 3, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 10, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 73, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 18, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		}, { 0, 34, 204, 255 }));
}

int main(int argc, char* argv[]) {
	App app;

	return app.onExecute();
}