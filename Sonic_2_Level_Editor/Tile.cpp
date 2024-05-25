#include "Tile.h"

Tile::Tile() {
	this->foreground = false;
	this->flipH = false;
	this->flipV = false;
	this->palette = 0;
	this->tileMapIndex = 0;
}

Tile::Tile(bool foreground, bool flipH, bool flipV, int palette, int tileMapIndex) {
	this->foreground = foreground;
	this->flipH = flipH;
	this->flipV = flipV;
	this->palette = palette;
	this->tileMapIndex = tileMapIndex;
}

void Tile::reset() {
	this->foreground = false;
	this->flipH = false;
	this->flipV = false;
	this->palette = 0;
	this->tileMapIndex = 0;
}