#pragma once
#include "Text.h"
#include "BaseObject.h"
#include "enums.h"
#include <iostream>
class Button:public BaseObject,public Text
{
	void assignTexture(int id);
public:
	int state = 0;
	sf::RectangleShape rect;
	int textureIndex = 0;

	bool changeable = true;
	Button(std::string str, sf::Font& font, float x, float y, float width, float height,int id = -1);
	Button();
	void setTexture(std::vector<sf::Texture>& textures);
	bool needUpdating = true;
	void textureUpdateHandler(int newButtonState);
};




























/*
if (changeable)
{
	if (nr != INT_MIN)
		setText(nr);

	if (changeState != state)
	{

		if (changeState == _hover && state == _active) sound->play();

		//else if (changeState == _active 
			//&&(id == _play_ || id == _generate_ || id == _solve_))sound->play();
		state = changeState;
		refreshTexture();
	}

}*/