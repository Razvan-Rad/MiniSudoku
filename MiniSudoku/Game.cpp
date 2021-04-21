#include "Game.h"
Game::Game()
{
	font = makeFont();
	window = makeWindow();
	//vreau sa stiu unde pun textura si unde pun sprite-ul
	//acum primesc doar un index la un sprite
	//vreau sa primesc index la textura
	initTable();
	initTextures();
	initSprites();
	prepareSprites();
}


void Game::render()
{
	window->clear();
	for (int i = 0; i < other_sprites.size(); i++)
	{
		other_sprites[i].setPosition(i*20, i*20);
		window->draw(other_sprites[i]);
	}
	window->display();
}



void Game::loop()
{
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			KeyboardEvent keyboardEvent;
			MouseButtonEvent mouseEvent;
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
			default:
				mouseEvent.type = ButtonEventType::None;
			}
			mouseEventHandler(mouseEvent);
		}
		render();
	}
}


void Game::mouseEventHandler(MouseButtonEvent& ev)
{
	switch (ev.type)
	{
	case ButtonEventType::None:
		break;
	case ButtonEventType::Pressed:
		std::cout << "p\n";

		break;
	case ButtonEventType::Moved:

		buttonMouseHandler(eHovered);
		//go through all buttons 
		//see if the mouse pos is within any button's bounds
		//change button state
		std::cout << "m\n";
		break;
	case ButtonEventType::Released:
		std::cout << "r\n";
		//make sound
		break;

	}
}

sf::Font Game::makeFont()
{
	sf::Font temp;
	temp.loadFromFile("Resources\\Fonts\\font.ttf");
	return temp;
}
void Game::handleSfmlEvent(sf::Event event)
{

}
void Game::buttonMouseHandler(int newButtonState)
{
}
sf::Texture Game::loadTexture(std::string PATH)
{
	sf::Texture texture;
	texture.loadFromFile("Resources\\Textures\\" + PATH);

	return texture;
}
void Game::initTextures()
{
	std::ifstream read;
	read.open("Resources\\Textures\\textures.txt");
	std::string x;
	//we flag the textures which we know are interractable, and we put those in interractable textures
	std::vector<std::pair<sf::Texture, bool>> flaggedTextures;


	while (getline(read, x))
		if (x[0] != '#')
		{
			if (x[0] == '!') // Flagged as interractable, add bool
			{
				x.erase(0, 1);
				flaggedTextures.push_back(std::make_pair(loadTexture(x + ".jpg"), true	));
				std::cout << "pushed " << x << std::endl;
			}
			else //not flagged as interractable
			{
				flaggedTextures.push_back(std::make_pair(loadTexture(x + ".jpg"), false));
			}
		}
	for (int i = 0; i < flaggedTextures.size(); i++)
	{
		if (flaggedTextures[i].second == true) interractable_textures.push_back(flaggedTextures[i].first);
		else  other_textures.push_back(flaggedTextures[i].first);
	}
	read.close();

}
void Game::initSprites()
{
	for (int i = 0; i < other_textures.size(); i++)
	{
		sf::Sprite temp;
		temp.setTexture(other_textures[i]);
		other_sprites.push_back(temp);
	}
}
void Game::prepareSprites()
{

	other_sprites[0].setScale(18.75, 18.75);
	other_sprites[1].setScale(3.733333333, 4);
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
void Game::initTable()
{
	sudoku = Table();
}