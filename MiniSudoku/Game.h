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
	Gstate gamestate;
	sf::RenderWindow* window = NULL;
	sf::Font font;
	sf::Font makeFont();
	sf::RenderWindow* makeWindow();
	void initTable();
	
	std::vector<sf::Texture> interractable_textures;
	std::vector<sf::Texture> other_textures;

	std::vector<sf::Sprite> other_sprites;

	MouseButtonEvent mouseEvent;
	KeyboardEvent keyboardEvent;

	std::vector<Button> buttons;
	std::vector<std::vector<Button>> boxes;
	sf::Texture loadTexture(std::string PATH);

	void mouseEventHandler(MouseButtonEvent& ev);
	void keyboardEventHandler(KeyboardEvent& ev);
	void handleSfmlMouseEvent(sf::Event event);
	void handleSfmlKeyboardEvent(sf::Event event);
	void buttonMouseHandler(int newButtonState, sf::Vector2i v2i);
	void initTextures();
	void solvingAlgorithmAnimation(int table[9][9]);
	void initSprites();
	void prepareSprites();
	void initButtons();
	void initBoxes();
	void initSounds();
	void checkButtonColision(std::vector<Button>& btns, sf::Vector2i, int newButtonState, bool buttons = false);
	//void drawInterractable(Button& btn);
	void drawInterractable(Button& btn, ID ID);
	sf::SoundBuffer btnPressSoundBuffer;
	sf::SoundBuffer boxPressSoundBuffer;
	sf::Sound btnPressSound;
	sf::Sound boxPressSound;
	sf::Music music;
	bool loopHijacker(int table[9][9]);


	void render();
	void renderGenerating();
	void renderNumberPicker();
	void renderMain(bool optional = false);
	void renderSettings();
	void renderIntro();
	void renderSolving();
	void renderMedia();
	void renderSolvingAnimation(int table[9][9]);
	void renderIntroAnimation();
	void renderIntroAnimationReverse();
public:
	Game();
	void loop();
	void makeButton(std::string str, const sf::Font& font, float x, float y, std::pair<float, float> size, ID id);
};