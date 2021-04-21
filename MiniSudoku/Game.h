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
enum {
	eNone,
	eHovered,
	eClicked
};
struct MouseButtonEvent {
	ButtonEventType type;
	sf::Vector2i mousePos;
};


struct KeyboardEvent {

};




class Game
{
	int gamestate = 0;
	sf::RenderWindow* window = NULL;
	sf::Font font;

	sf::Texture* loadTexture(std::string PATH);
	sf::Font makeFont();
	sf::RenderWindow* makeWindow();
	void render();
public:
	Game();
	void loop();
	void mouseEventHandler(MouseButtonEvent& ev);
	void keyboardEventHandler(KeyboardEvent& ev);
	void handleSfmlEvent(sf::Event event);
	void buttonMouseHandler(int newButtonState);
};

//buttonChecker(state).
	//mergem la fiecare buton, verificam bounds
		//if(mousePos within button.bounds) , 
			//button.updateButton(state)
				
				
