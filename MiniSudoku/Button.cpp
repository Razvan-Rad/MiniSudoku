#include "Button.h"
void Button::assignTexture(ID id)
{
	switch (id)
	{
	case ID::settings:
		textureIndex = eBack;
		break;
	case ID::media:
		textureIndex = eBack;
		break;
	case ID::back:
		textureIndex = eBack;
		break;
	case ID::box:
		textureIndex = eBox;
		break;
	case ID::generate:
	case ID::solve:
	case ID::play:
	default:
		textureIndex = eBtn;
		break;
	}
}

Button::Button(std::string str, const sf::Font& font, float x, float y, float width, float height, ID id)
	:BaseObject(x, y, width, height, id)
{
	this->x = x;
	this->y = y;

	assignTexture(id);
	rect.setSize(sf::Vector2f(width, height));
	rect.setPosition(x, y);

	initText(str, font, width, x, y);
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

Gamestates Button::eventHandler(int newButtonState)
{
		switch (this->id)
		{
		case ID::play:
			return Gamestates::Main;

		case ID::generate:
			return Gamestates::Generating;

		case ID::solve:
			return Gamestates::Solving;
		case ID::box:
			break;
		case ID::media:
			return Gamestates::Media;
		case ID::settings:
			return Gamestates::Settings;
			break;
		case ID::back:
			return Gamestates::Intro;

		default:
			return Gamestates::Debug;
		}
	
}
Gamestates Button::resourcesHandler(int newButtonState)
{
	Gamestates temp = Gamestates::Debug;	
	if (changeable)
	{
		if (newButtonState != state)
		{
			needUpdating = true;

			if (state == 2 && newButtonState == 1)
			{
				temp = eventHandler(newButtonState);
				makeNoise = true;
			}
			state = newButtonState;
		}
	}
	return temp;
}

void Button::flipChangeable()
{
	changeable = !changeable;
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

void Button::setText(std::string str)
{
	text.setString(str);
}

void Button::setState(int i)
{
	state = i;
}

void Button::initText(const std::string& str, const sf::Font& font, int width, int i, int j)
{
	this->text.setFont(font);
	this->text.setString(str);
	this->text.setPosition(x, y);
	text.setFillColor(sf::Color::Black);

	if (width == 150)
		text.move(30, 10);
	else text.move(15, 5);
}

void Button::initRect()
{
}