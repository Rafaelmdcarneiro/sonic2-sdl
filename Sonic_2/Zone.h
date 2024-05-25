#pragma once
#include "Tile.h"
#include <vector>
#include <string>
#include "MetaTile.h"

class Zone
{
private:
	int levelWidth;
	int levelHeight;
	std::vector<Tile> tileMap;
	std::vector<MetaTile> metaTileMap;
	std::vector<int> levelMap;

	std::string zoneName;
	int zoneId;
	int actNo;

public:
	Zone(std::string zoneName, int zoneId, int actNo, int levelWidth, int levelHeight, std::vector<int> levelMap, SDL_Color backgroundColor);

	SDL_Color backgroundColor;

	std::string getZoneName();
	int getZoneWidth();
	int getZoneHeight();
	int getZoneId();
	int getActNo();

	Tile getTileFromId(int id);

	std::vector<Tile> getTileMap();
	std::vector<int> getLevelMap();

	void setTileMap();
};

