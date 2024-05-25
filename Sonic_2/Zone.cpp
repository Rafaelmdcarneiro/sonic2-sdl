#include "Zone.h"

Zone::Zone(std::string zoneName, int zoneId, int actNo, int levelWidth, int levelHeight, std::vector<int> levelMap, SDL_Color backgroundColor)
{
    this->levelWidth = levelWidth;
    this->levelHeight = levelHeight;
    this->zoneName = zoneName;
    this->zoneId = zoneId;
    this->actNo = actNo;

    this->levelMap = levelMap;
    this->levelMap.resize(levelWidth * levelHeight);

    this->backgroundColor = backgroundColor;
}

int Zone::getZoneWidth()
{
    return levelWidth;
}

int Zone::getZoneHeight()
{
    return levelHeight;
}

int Zone::getZoneId()
{
    return zoneId;
}

int Zone::getActNo()
{
    return actNo;
}

Tile Zone::getTileFromId(int id)
{
    Tile tile;
    for (int i = 0; i < tileMap.size(); i++) {
        if (i == id) tile = tileMap[i];
    }
    return tile;
}

std::string Zone::getZoneName() {
    return zoneName;
}

std::vector<Tile> Zone::getTileMap()
{
    return tileMap;
}

std::vector<int> Zone::getLevelMap()
{
    return levelMap;
}

void Zone::setTileMap()
{
    tileMap.push_back(Tile());
}
