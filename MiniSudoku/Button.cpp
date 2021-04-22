#include "Button.h"
void Button::assignTexture(int id)
{
	switch (id)
	{

	case eSettingsID:
		textureIndex = eBack;
		break;
	case eMediaID:
		textureIndex = eBack;
		break;
	case eBackID:
		textureIndex = eBack;
		break;

	case eGenerateID:
	case eSolveID:
	case ePlayID:
	default:
		textureIndex = eBtn;
		break;
	}
}


Button::Button( std::string str, const sf::Font& font, float x, float y, float width, float height, int id)
	:BaseObject(x, y, width, height, id)
{
	this->x = x;
	this->y = y;

	assignTexture(id);
	rect.setSize(sf::Vector2f(width, height));
	rect.setPosition(x, y);

	initText(str, font,width,x,y);

}

void Button::setTexture(std::vector<sf::Texture>& textures)
{
	rect.setTexture(&textures[textureIndex + state]);
	needUpdating = false;

}
void Button::resetNoise()
{
	makeNoise = false;
}
void Button::resourcesHandler(int newButtonState)
{
	if (changeable)
	{
		if (newButtonState != state)
		{
			needUpdating = true;

			if (state == 2 && newButtonState == 1) makeNoise = true;
			state = newButtonState;
		}
	}
}

bool Button::getChangeable()
{
	return changeable;
}

sf::Text Button::getText()
{
	return text;
}

bool Button::shouldUpdate()
{
	return needUpdating;
}

bool Button::getNoise()
{
	return makeNoise;
}

sf::RectangleShape& Button::getRect()
{
	return rect;
}

void Button::initText(const std::string& str, const sf::Font& font,int width,int i, int j)
{
	this->text.setFont(font);
	this->text.setString(str);
	this->text.setPosition(x, y);
	text.setFillColor(sf::Color::Red);



	if (width == 150)
		text.move( 30,10);
	else text.move(15,5);
}

void Button::initRect()
{
}
