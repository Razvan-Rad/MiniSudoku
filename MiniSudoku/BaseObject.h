#pragma once
#include "SFML/Graphics.hpp"

class BaseObject
{

public:
	BaseObject(float x, float y, float width, float height, int id);
	int id;
	sf::IntRect bounds;
	bool checkBounds(sf::Vector2i& v2i);
};

