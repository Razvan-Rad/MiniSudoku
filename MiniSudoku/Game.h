#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Table.h"
#include "fstream"
#include <iostream>
#include <queue>
#include <string>
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
enum buttonState{
	eNone,
	eHovered,
	eClicked
};
enum textureIndexes{
	eBtn,
	eHover_btn,
	eActive_btn,

	eBox,
	eHover_box,
	eActive_box,

	eBack,
	eHover_back,
	eActive_back,
	eBackground,
	eIntroBackground


};
struct MouseButtonEvent {
	ButtonEventType type;
	sf::Vector2i mousePos;
};


struct KeyboardEvent {

};


class Game
{
	Table sudoku;
	int gamestate = 0;
	sf::RenderWindow* window = NULL;
	sf::Font font;

	sf::Font makeFont();
	sf::RenderWindow* makeWindow();
	void initTable();
	void render();

	std::vector<sf::Texture> textures;
	std::vector<sf::Sprite> sprites;
public:
	Game();
	void loop();
	void mouseEventHandler(MouseButtonEvent& ev);
	void keyboardEventHandler(KeyboardEvent& ev);
	void handleSfmlEvent(sf::Event event);
	void buttonMouseHandler(int newButtonState);
	sf::Texture loadTexture(std::string PATH);
	void initTextures();
	void initSprites();
};

//buttonChecker(state).
	//mergem la fiecare buton, verificam bounds
		//if(mousePos within button.bounds) , 
			//button.updateButton(state)
				
				
