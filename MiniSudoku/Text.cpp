#include "Text.h"

Text::Text(const sf::Font& tempofont,const std::string &str, float x, float y)
{
	this->font = tempofont;
	this->text.setFont(font);
	this->text.setString(str);
	this->text.setPosition(x, y);
	text.setFillColor(sf::Color::Red);
}
Text::Text()
{

}