#include "Text.h"
#include <iostream>
Text::Text(const sf::Font& tempofont,const std::string &str, float x, float y)
{
	this->string = str;
	this->font = tempofont;
	this->text.setFont(font);
	this->text.setString(this->string);
	this->text.setPosition(x, y);
	text.setFillColor(sf::Color::Red);
}