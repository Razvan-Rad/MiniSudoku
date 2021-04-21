#pragma once
#include "Text.h"
#include "BaseObject.h"

class Button:BaseObject,Text
{
	
public:
	sf::RectangleShape hitbox;
	Button(std::string str, sf::Font& font, float x, float y, float width, float height, int id = -1);

};

