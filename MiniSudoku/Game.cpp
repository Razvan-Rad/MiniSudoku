#include "Game.h"

Game::Game()
{
	font = makeFont();
	window = makeWindow();
	
}


sf::Texture* Game::makeTexture(std::string PATH)
{
	sf::Texture* temp = new sf::Texture;
	temp->loadFromFile("Resources\\Textures\\" + PATH);
	return temp;
}
sf::Font* Game::makeFont()
{
	sf::Font* temp = new sf::Font;
	temp->loadFromFile("Resources\\Fonts\\font.ttf");
	return temp;
}

sf::RenderWindow* Game::makeWindow()
{
	//given initial values in case we can't open settings

	int vsync, height, width, frame_limit;
	//open settings and read parameters
	std::ifstream read;
	read.open("Resources\\settings.txt");
	std::string x = "Solver";
	if (read.is_open())
	{
		read >> width >> height;
		read >> frame_limit;
		read >> vsync;
		read >> x;
		read.close();
	}
	else
	{
		vsync = 0;
		height = 800,
			width = 600,
			frame_limit = 30;
	}

	sf::RenderWindow* tempwindow = new sf::RenderWindow(sf::VideoMode(width, height), x);
	tempwindow->setFramerateLimit(frame_limit);
	tempwindow->setVerticalSyncEnabled(vsync);
	return tempwindow;
}


size_t Game::loadNPush(const std::string& PATH)
{
	auto texture = std::make_unique<sf::Texture>();				//std::unique_ptr<sf::Texture>texture = std::make_unique<sf::Texture>();
	texture->loadFromFile("Resources\\Textures\\" + PATH);
	
	sf::Sprite sprite;
	sprite.setTexture(*texture);

	sprites.push_back(sprite);
	textures.push_back(std::move(texture));

	return sprites.size();
}

