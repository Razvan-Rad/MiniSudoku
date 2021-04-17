#pragma once
#include "Gamestate.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "fstream"
enum {
	gamestateIntro,
	gamestateMain,
	};
class Game
{
	//The purpose of this class is storing the textures and graphics
	
	sf::RenderWindow* window = NULL;
	sf::Font* font;
	std::vector<sf::Text> texts;
	std::vector<sf::Sprite> sprites;
	std::vector<std::unique_ptr<sf::Texture>> textures;

	//Takes a  path, creates a texture and a sprite. returns an index to the sprite
	size_t loadNPush(const std::string& PATH);

	sf::Texture* makeTexture(std::string PATH);
	sf::Font* makeFont();
	//creates window, loads everything from files (if possible)
	sf::RenderWindow* makeWindow();
public:
	Game();
};

