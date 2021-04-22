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

sf::Text Button::getText()
{
	return text;
}
Button::Button(const std::string& str, const sf::Font& font, float x, float y, float width, float height, int id)
	:BaseObject(x, y, width, height, id)
	, Text(font, str, x, y)
{
	assignTexture(id);
	rect.setSize(sf::Vector2f(width, height));
	rect.setPosition(x, y);

}

void Button::setTexture(std::vector<sf::Texture>& textures)
{
	rect.setTexture(&textures[textureIndex + state]);
	needUpdating = false;
}

void Button::textureUpdateHandler(int newButtonState)
{
	if (changeable)
	{
		if (newButtonState != state)
		{
			needUpdating = true;
			state = newButtonState;
		}
	}
}

bool Button::getChangeable()
{
	return changeable;
}

bool Button::shouldUpdate()
{
	return needUpdating;
}

sf::RectangleShape& Button::getRect()
{
	return rect;
}
