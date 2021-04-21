#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"


#include "Text.h"
#include "Button.h"
#include "Table.h"
#include "fstream"

#include <iostream>
#include <queue>
#include <string>
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
enum other_texture_indexes {
	eBg,
	eIntroBg
};
enum interractable_texture_indexes{
	eBtn,
	eHover_btn,
	eActive_btn,

	eBox,
	eHover_box,
	eActive_box,

	eBack,
	eHover_back,
	eActive_back,
};
enum ID {
	ePlay,
	eSettings,
	eMedia,
	eGenerate,
	eSolve
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

	std::vector<sf::Texture> interractable_textures;
	std::vector<sf::Texture> other_textures; 

	std::vector<sf::Sprite> other_sprites;

	std::vector<Button> buttons;
	std::vector<Button> boxes;


	void mouseEventHandler(MouseButtonEvent& ev);
	void keyboardEventHandler(KeyboardEvent& ev);
	void handleSfmlEvent(sf::Event event);
	void buttonMouseHandler(int newButtonState);
	sf::Texture loadTexture(std::string PATH);
	void initTextures();
	void initSprites();
	void prepareSprites();
	void initButtons();
public:
	Game();
	void loop();
	Button makeButton(std::string str, sf::Font& font, float x, float y, float width, float height, int id);
};

//buttonChecker(state).
	//mergem la fiecare buton, verificam bounds
		//if(mousePos within button.bounds) , 
			//button.updateButton(state)
				
				
