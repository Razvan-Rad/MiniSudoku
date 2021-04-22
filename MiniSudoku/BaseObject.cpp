#include "BaseObject.h"
BaseObject::BaseObject(float x, float y, float width, float height, int id)
{
	this->id = id;
	bounds = sf::IntRect(x, y, width, height);
}

bool BaseObject::checkBounds(sf::Vector2i& v2i)
{
	return bounds.contains(v2i);
}
int BaseObject::getId()
{

	return id;
}
