#pragma once
class Tile
{
public:
	bool foreground;
	bool flipH, flipV;
	int palette;
	int tileMapIndex;

	Tile();
	Tile(bool foreground, bool flipH, bool flipV, int palette, int tileMapIndex);
	void reset();
};

