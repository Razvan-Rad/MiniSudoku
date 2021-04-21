#pragma once
#include "Text.h"
#include "BaseObject.h"
#include "enums.h"
class Button:public BaseObject,public Text
{
	void assignTexture();
public:
	sf::RectangleShape rect;
	int textureIndex;
	Button(std::string str, sf::Font& font, float x, float y, float width, float height, int id = -1);
	
};

