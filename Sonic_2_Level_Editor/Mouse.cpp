#include "Mouse.h"

void Mouse::setPosition(float xPos, float yPos)
{
	position.first = xPos;
	position.second = yPos;
}

void Mouse::setMotion(float xMotion, float yMotion)
{
	motion.first = xMotion;
	motion.second = yMotion;
}
