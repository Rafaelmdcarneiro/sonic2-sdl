#pragma once
#include <SDL.h>
#include <map>

static struct Mouse
{
private:

public:
	std::map<int, bool> buttons;
	std::pair<float, float> position;
	std::pair<float, float> motion;
	float wheel = 0;

	void setPosition(float xPos, float yPos);
	void setMotion(float xMotion, float yMotion);

} mouse;

