#pragma once
#include "SFML/Graphics.hpp"
class Text
{
	sf::Font font;

	int x = 0, y = 0;
public:
	sf::Text text;
	Text(const sf::Font& tempfont,const std::string &str, float x=0, float y=0);
	Text();
};
