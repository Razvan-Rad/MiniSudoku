#include "Game.h"
Game::Game()
{
	font = makeFont();
	window = makeWindow();
	window->clear();
	//vreau sa stiu unde pun textura si unde pun sprite-ul
	//acum primesc doar un index la un sprite
	//vreau sa primesc index la textura
}

void Game::render()
{
	window->display();
}



void Game::loop()
{
	while (window->isOpen())
	{
		while (window->pollEvent(event))
		{
			mouseButtonEvent mouseEvent;
			// check the type of the event...
			switch (event.type)
			{

			case sf::Event::MouseButtonPressed:
				mouseEvent.type = ButtonEventType::Pressed;
				break;
			case sf::Event::MouseButtonReleased:
				mouseEvent.type = ButtonEventType::Released;
				break;

			case sf::Event::MouseMoved:
				mouseEvent.type = ButtonEventType::Moved;
				mouseEvent.mousePos = sf::Mouse::getPosition(*window);
				break;
			}
			MouseEventHandler(mouseEvent);
		}
		render();
	}
}

void Game::MouseEventHandler(mouseButtonEvent& ev)
{
	switch (ev.type)
	{
	case ButtonEventType::Pressed:
		std::cout << "p\n";
		break;
	case ButtonEventType::Moved:
		std::cout << "m\n";
		break;
	case ButtonEventType::Released:
		std::cout << "r\n";
		//make sound
		break;
	case ButtonEventType::None:
		std::cout << "n\n";
		break;
	}
}
sf::Texture* Game::loadTexture(std::string PATH)
{
	sf::Texture* temp = new sf::Texture;
	temp->loadFromFile("Resources\\Textures\\" + PATH);
	return temp;
}
 sf::Font Game::makeFont()
{
	sf::Font temp;
	temp.loadFromFile("Resources\\Fonts\\font.ttf");
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
