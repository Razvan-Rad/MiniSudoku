#pragma once
#include "Text.h"
#include "BaseObject.h"
class Button
{
	sf::Texture texture;
	sf::Texture hover_texture;
	sf::Texture active_texture;
	bool changeable = true;
	void refreshTexture(); //according to the set state, changes texture
	void setText(int nr); //according to the number given, changes the text.stirng

public:
	Button();
	int state = 0;
	Button(std::string str, sf::Font* font, sf::Texture* def, sf::Texture* hover, sf::Texture* active, float x, float y, float width, float height, int id = -1);
	sf::RectangleShape button;
	void lockToggle();
	bool isLockOn();
	void updateButton(int changeState = 0, int nr = INT_MIN);

};

