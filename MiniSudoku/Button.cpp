#include "Button.h"

Button::Button(std::string str, sf::Font &font,float x, float y, float width, float height, int id)
	:BaseObject(x,y,width,height,id)
	, Text(font,str,x,y)
{

	hitbox.setSize(sf::Vector2f(width, height));
}
