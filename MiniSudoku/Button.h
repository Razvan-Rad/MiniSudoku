#pragma once
#include "BaseObject.h"
#include "enums.h"
#include <iostream>
class Button:public BaseObject
{
	int x = 0, y = 0;
	void assignTexture(int id);
	int state = 0;
	sf::RectangleShape rect;
	int textureIndex = 0;
	bool needUpdating = true;
	bool changeable = true;

	sf::Text text;
public:
	Button( std::string str, const sf::Font& font, float x, float y, float width, float height,int id = -1);

	void setTexture(std::vector<sf::Texture>& textures);
	void textureUpdateHandler(int newButtonState);
	bool getChangeable();
	sf::Text getText();
	bool shouldUpdate();
	sf::RectangleShape& getRect();
	void initText(const std::string& str, const sf::Font& font);
	void initRect();
};