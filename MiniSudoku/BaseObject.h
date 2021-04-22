#pragma once
#include "SFML/Graphics.hpp"
#include "enums.h"
class BaseObject
{

public:
	BaseObject(float x, float y, float width, float height, ID id);
	ID id= ID::debug;
	sf::IntRect bounds;
	bool checkBounds(sf::Vector2i& v2i);
	ID getId();
};

