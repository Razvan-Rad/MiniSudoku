#include "Text.h"

Text::Text(sf::Font& tempofont,std::string &str, float x, float y)
{
	this->font = tempofont;
	this->text.setFont(font);
	this->text.setString(str);
	this->text.setPosition(x, y);
	text.setFillColor(sf::Color::Red);
}