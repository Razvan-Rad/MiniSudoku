#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "fstream"
#include <iostream>
#include <queue>

#include "Text.h"
#include "Button.h"
enum class ButtonEventType {
	None,
	Pressed,
	Released,
	Moved
};
enum class Gamestates {
	Intro,
	Main,
	Solving,
	Generating,
	Settings,
	Other
};
struct mouseButtonEvent {
	ButtonEventType type;
	sf::Vector2i mousePos;
};
class Game
{
	
	int gamestate = 0;
	sf::RenderWindow* window = NULL;
	sf::Font font;


	sf::Event event;
	sf::Texture* loadTexture(std::string PATH);
	sf::Font makeFont();
	sf::RenderWindow* makeWindow();
	void render();
public:
	Game();
	void loop();
	void MouseEventHandler(mouseButtonEvent& ev);
};


