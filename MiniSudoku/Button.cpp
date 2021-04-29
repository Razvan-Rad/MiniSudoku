#include "Button.h"
void Button::assignTexture(ID id)
{
	switch (id)
	{
	case ID::settings:
		textureIndex = eBox;
		break;
	case ID::media:
		textureIndex = eBox;
		break;
	case ID::back:
		textureIndex = eBack;
		break;
	case ID::box:
		textureIndex = eBox;
		break;
	case ID::fastForward:
		textureIndex = eBox;//TODO
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

Gstate Button::eventHandler(int newButtonState)
{
		switch (this->id)
		{
		case ID::play:
			return Gstate::IntroAnimation;

		case ID::generate:
			return Gstate::Generating;

		case ID::solve:
			return Gstate::Solving;

		case ID::box:
			return Gstate::NumberPicker;

		case ID::media:
			return Gstate::Media;

		case ID::settings:
			return Gstate::Settings;

		case ID::back:
			return Gstate::IntroAnimationReverse;

		case ID::fastForward:
			return Gstate::Main;

		default:
			return Gstate::Debug;
		}
	
}
Gstate Button::resourcesHandler(int newButtonState)
{
	Gstate temp = Gstate::Debug;	
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

sf::Text& Button::getText()
{
	return text;
}

int Button::getState()
{
	return state;
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