#include "Button.h"
void Button::assignTexture()
{
	switch (id)
	{

	default:
		textureIndex = eBox;
		break;
	}
}

Button::Button(std::string str, sf::Font &font,float x, float y, float width, float height, int id)
	:BaseObject(x,y,width,height,id)
	, Text(font,str,x,y)
{
	printf("constructor called");
	assignTexture();
	rect.setSize(sf::Vector2f(width, height));
	rect.setPosition(x, y);
	
}

Button::Button() :BaseObject(), Text()
{
}

void Button::textureUpdateHandler(int newButtonState)
{
	if (changeable)
	{
		if (newButtonState != state)
		{
			std::cout << "updated to " << newButtonState;
			needUpdating = true;
			state = newButtonState;
		}
	}
}
