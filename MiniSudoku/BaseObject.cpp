#include "BaseObject.h"
BaseObject::BaseObject(float x, float y, float width, float height, ID id)
{
	this->id = id;
	bounds = sf::IntRect(x, y, width, height);
}

bool BaseObject::checkBounds(sf::Vector2i& v2i)
{
	return bounds.contains(v2i);
}
ID BaseObject::getId()
{
	return id;
}
