#pragma once
#include "Text.h"
#include "BaseObject.h"
#include "enums.h"
#include <iostream>
class Button:public BaseObject,public Text
{
	void assignTexture(int id);
	int state = 0;
	sf::RectangleShape rect;
	int textureIndex = 0;
	bool needUpdating = true;
	bool changeable = true;
public:
	Button(const std::string& str, const sf::Font& font, float x, float y, float width, float height,int id = -1);
	sf::Text getText();
	void setTexture(std::vector<sf::Texture>& textures);
	void textureUpdateHandler(int newButtonState);
	bool getChangeable();
	bool shouldUpdate();
	sf::RectangleShape& getRect();
};