#include <SDL_image.h>
#include <iostream>
#include <nfd.hpp>

#include "Zone.h"
#include "Settings.h"

Zone::Zone(SDL_Renderer* renderer, std::string zoneName, int actNo, SDL_Color background, std::string tileSetPath, int width, int height)
{
	std::string zonePath = "../Zone Tilesets/" + tileSetPath;
	SDL_Surface* tileSetSurface = IMG_Load(zonePath.c_str());
	Uint32 colorKey = SDL_MapRGB(tileSetSurface->format, ALPHA_KEY);
	SDL_SetColorKey(tileSetSurface, SDL_TRUE, colorKey);

	this->renderer = renderer;
	this->tileSetPath = tileSetPath;
	this->zoneName = zoneName;
	this->actNo = actNo;
	this->backgroundColor = background;
	this->tileSet = SDL_CreateTextureFromSurface(renderer, tileSetSurface);

	this->zoneWidth = (width >= settings.MIN_LEVEL_WIDTH) ? width : settings.MIN_LEVEL_WIDTH;
	this->zoneHeight = (height >= settings.MIN_LEVEL_HEIGHT) ? height : settings.MIN_LEVEL_HEIGHT;
	//if (width >= 100) this->zoneWidth = width;
	//else this->zoneWidth = 100;
	//if (height >= 64) this->zoneHeight = height;
	//else this->zoneHeight = 64;

	//this->currentMapSet.reserve(zoneWidth * zoneHeight);
	for (int i = 0; i < zoneWidth * zoneHeight; i++) mapSet.push_back(Tile());
}

void Zone::renderZone(float camX, float camY, int tileSize) {
	for (int i = 0; i < mapSet.size(); i++) {
		int tileIndex = mapSet[i].tileMapIndex;
		
		int xPos = (i % zoneWidth) * tileSize + camX;
		int yPos = (i / zoneWidth) * tileSize + camY;

		SDL_Rect worldTile{xPos, yPos, tileSize, tileSize};

		if (tileIndex == 0) {
			SDL_SetRenderDrawColor(renderer, 80, 80, 80, 70);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderDrawRect(renderer, &worldTile);
		}
		else {
			SDL_Rect textureTile;
			textureTile.x = (tileIndex % 20) * 16;
			textureTile.y = (tileIndex / 20) * 16;
			textureTile.w = 16;
			textureTile.h = 16;

			int flip = SDL_FLIP_NONE;
			if (mapSet[i].flipH && mapSet[i].flipV) flip = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
			else if (mapSet[i].flipH) flip = SDL_FLIP_HORIZONTAL;
			else if (mapSet[i].flipV) flip = SDL_FLIP_VERTICAL;

			SDL_RenderCopyEx(renderer, tileSet, &textureTile, &worldTile, 0.0, NULL, (SDL_RendererFlip)flip);
			
		}
	}
}

// Save the zone under /Zones/XXN.zone:
// X: First letter of each word in zone
// N: Act number
void Zone::saveZone(std::string filePath)
{
	std::ofstream ZoneFile(filePath, std::ofstream::trunc);
	ZoneFile << zoneName + "\n";
	ZoneFile << std::to_string(actNo) + "\n";
	ZoneFile << tileSetPath + "\n";
	ZoneFile << std::to_string(zoneWidth) + "\n";
	ZoneFile << std::to_string(zoneHeight) + "\n";
	for (int y = 0; y < zoneHeight; y++) {
		for (int x = 0; x < zoneWidth; x++) {
			Tile* currentTile = &mapSet[x + (y * zoneWidth)];

			uint16_t tileData = 0;
			tileData |= (currentTile->foreground << 15);
			tileData |= (currentTile->flipH << 14);
			tileData |= (currentTile->flipV << 13);
			tileData |= (currentTile->palette << 11);
			tileData |= (currentTile->tileMapIndex);

			//printf("0x%X ", tileData);

			ZoneFile.write(reinterpret_cast<char*>(&tileData), sizeof(uint16_t));
			//ZoneFile << tileData;
		}
		ZoneFile << "\n";
	}

	ZoneFile.close();		
}

Zone* Zone::OpenZone(SDL_Renderer* renderer, std::string zonePath)
{
	std::ifstream zoneFile(zonePath);
	std::string text;
	std::vector<std::string> zoneMetaData;
	std::vector<uint16_t> zoneData;
	int iterator = 0;

	do {
		std::getline(zoneFile, text);
		zoneMetaData.push_back(text);
		iterator++;
	} while (iterator < 5);

	while (zoneFile >> text) {
		for (int i = 0; i < text.size(); i += 2) {
			uint16_t data = 0;
			data |= ((uint8_t)text[i + 1] << 8);
			data |= ((uint16_t)text[i]);

			zoneData.push_back(data);
		}
	}

	zoneFile.close();

	Zone* zoneOut = new Zone(renderer, zoneMetaData[0], stoi(zoneMetaData[1]), { 23, 27, 33, 255 }, zoneMetaData[2], stoi(zoneMetaData[3]), stoi(zoneMetaData[4]));
	std::vector<Tile> loadedTileSet;
	for (uint16_t tileData : zoneData) {
		Tile loadedTile;
		loadedTile.foreground = (tileData & 0x8000) >> 15;
		loadedTile.flipH = (tileData & 0x4000) >> 14;
		loadedTile.flipV = (tileData & 0x2000) >> 13;
		loadedTile.palette = (tileData & 0x1800) >> 11;
		loadedTile.tileMapIndex = (tileData & 0x7FF);

		loadedTileSet.push_back(loadedTile);
	}

	zoneOut->mapSet = loadedTileSet;

	return zoneOut;
}
