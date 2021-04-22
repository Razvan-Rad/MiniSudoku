#pragma once
#include "BaseObject.h"
#include <iostream>
class Button:public BaseObject
{
	int x = 0, y = 0;
	void assignTexture(ID id);
	int state = 0;
	sf::RectangleShape rect;
	int textureIndex = 0;
	bool needUpdating = true;
	bool changeable = true;
	bool makeNoise = false;
	sf::Text text;
	void initRect();
	void initText(const std::string& str, const sf::Font& font, int width, int i, int j);
public:
	Button( std::string str, const sf::Font& font, float x, float y, float width, float height,ID ID = ID::debug);

	void setTexture(std::vector<sf::Texture>& textures);
	void resourcesHandler(int newButtonState);
	

	sf::Text getText();
	sf::RectangleShape& getRect();

	bool shouldUpdate();
	bool getNoise();
	void resetNoise();
	bool getChangeable();
};