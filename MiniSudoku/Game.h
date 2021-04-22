#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

#include "Button.h"
#include "Table.h"
#include "fstream"

#include <iostream>
#include <string>

#include "enums.h"

struct KeyboardEvent {

};

struct FlaggedButton {

};
class Game
{
	Table sudoku;
	Gamestates gamestate;
	sf::RenderWindow* window = NULL;
	sf::Font font;
	sf::Font makeFont();
	sf::RenderWindow* makeWindow();
	void initTable();
	void render();

	std::vector<sf::Texture> interractable_textures;
	std::vector<sf::Texture> other_textures; 

	std::vector<sf::Sprite> other_sprites;

	MouseButtonEvent mouseEvent;
	std::vector<Button> buttons;
	std::vector<Button> boxes;

	void mouseEventHandler(MouseButtonEvent& ev);
	void keyboardEventHandler(KeyboardEvent& ev);
	void handleSfmlEvent(sf::Event event);
	void buttonMouseHandler(int newButtonState, sf::Vector2i v2i);
	sf::Texture loadTexture(std::string PATH);
	void initTextures();
	void initSprites();
	void prepareSprites();
	void initButtons();
	void checkButtonColision(std::vector<Button>& btns, sf::Vector2i, int newButtonState);
	void drawInterractable(Button& btn);
	void drawInterractable(Button& btn, int ID);
public:
	Game();
	void loop();
	std::string temp = "hey";
	void makeButton(std::string str, const sf::Font& font, float x, float y, std::pair<float, float> size, int id);
};
