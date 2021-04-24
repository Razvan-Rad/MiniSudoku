#include "Game.h"
Game::Game()
{
	gamestate = Gamestates::Intro;
	font = makeFont();
	window = makeWindow();
	initTable();
	initTextures();
	initSprites();
	initButtons();
	initBoxes();
	initSounds();
}

void Game::render() {
	window->clear();

	switch (gamestate)
	{
	case Gamestates::Intro:
		renderIntro();
		break;

	case Gamestates::Main:
		renderMain();
		break;

	case Gamestates::Solving:
		renderMain();
		loopHijacker(sudoku.table);
		gamestate = Gamestates::SolvingAnimation;
		break;

	case Gamestates::SolvingAnimation:
		
		printf("f");
		renderSolvingAnimation(sudoku.table);
		gamestate = Gamestates::Main;
		break;

	case Gamestates::Generating:
		renderGenerating();
		break;

	case Gamestates::Settings:
		renderSettings();

		break;

	default:
		printf("no man should be here..\n");
		break;
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
			case sf::Event::KeyPressed:
				gamestate = Gamestates::Intro;
			default:
				mouseEvent.type = ButtonEventType::None;
			}
			mouseEventHandler(mouseEvent);
		}
		if(window->hasFocus())render();
	}
}

void Game::makeButton(std::string str, const sf::Font& font, float x, float y, std::pair<float, float> size, ID id)
{
		if (ID::box == id)
		{
			Button btn(str, font, x, y, size.first, size.second, id);
			boxes[boxes.size() - 1].push_back(btn);
			return;
		}
		Button btn(str, font, x, y, size.first, size.second, id);
		buttons.push_back(btn);
	
}

void Game::mouseEventHandler(MouseButtonEvent& ev)
{
	//got a custom event. we have to see what type it is, so we can see if there's any button that needs updated
	switch (ev.type)
	{
	case ButtonEventType::None:
		break;

	case ButtonEventType::Pressed:
		buttonMouseHandler(eClicked, ev.mousePos);
		break;

	case ButtonEventType::Moved:
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			buttonMouseHandler(eClicked, ev.mousePos);
			break;
		}
	case ButtonEventType::Released:
		buttonMouseHandler(eHovered, ev.mousePos);
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

void Game::buttonMouseHandler(int newButtonState, sf::Vector2i v2i)
{
	checkButtonColision(buttons, v2i, newButtonState);
	if (gamestate == Gamestates::Solving ||
		gamestate == Gamestates::Generating ||
		gamestate == Gamestates::Main){
		for (size_t j = 0; j < boxes.size(); j++)
		{
			checkButtonColision(boxes[j], v2i, newButtonState);
		}
	}
}

sf::Texture Game::loadTexture(std::string PATH)
{
	sf::Texture texture;
	texture.loadFromFile("Resources\\Textures\\" + PATH);

	return texture;
}


void Game::drawInterractable(Button& btn, ID ID)
{
	if (btn.getId() == ID)
	{
		if (btn.shouldUpdate())
			btn.setTexture(interractable_textures);

		if (btn.getNoise())
		{
			if (btn.getId() == ID::box || btn.getId() == ID::back)
				boxPressSound.play();

			else btnPressSound.play();

			btn.resetNoise();
		}
		window->draw(btn.getRect());
		window->draw(btn.getText());
	}
}

void Game::prepareSprites()
{
	other_sprites[eBg].setScale(18.75, 18.75);
	other_sprites[eIntroBg].setScale(3.733333333, 4);
}

void  Game::checkButtonColision(std::vector<Button>& btns, sf::Vector2i mousepos, int newButtonState)
{
	for (size_t i = 0; i < btns.size(); i++)
	{
		if (btns[i].checkBounds(mousepos))
		{
			//we know the button contains the cursor. We are hovering/holding
			Gamestates temp = btns[i].resourcesHandler(newButtonState);

			gamestate = (temp == Gamestates::Debug) ? gamestate: temp;
		}
		else
		{
			btns[i].resourcesHandler(eNone);
			//we are outside. we HAVE to set the texture to none
		}
	}
}



sf::RenderWindow* Game::makeWindow()
{
	//given initial values in case we can't open settings
	int vsync, height, width, frame_limit;
	//open settings and read parameters
	std::ifstream read;
	read.open("Resources\\settings.txt");

	//make a structure settings
	std::string x = "Mini Sudoku";
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

void Game::initSounds()
{
	music.openFromFile("Resources\\Sounds\\music.ogg");
	music.setVolume(10);

	music.play();
	music.setLoop(true);

	btnPressSoundBuffer.loadFromFile("Resources\\Sounds\\sound.ogg");
	btnPressSound.setBuffer(btnPressSoundBuffer);
	btnPressSound.setVolume(20);

	boxPressSoundBuffer.loadFromFile("Resources\\Sounds\\boxsound.wav");
	boxPressSound.setBuffer(boxPressSoundBuffer);
	//boxPressSound.setVolume(20);
}

void Game::initBoxes()
{
	std::vector<Button> temp;

	std::pair<float, float> normal(50, 50);
	for (int j = 0, yoffset = 0, xoffset = 50; j < 9; j++, yoffset += (j % 3 == 0 && j != 0) ? 55 : 50, xoffset = 50) //col iter
	{
		boxes.push_back(temp);
		for (int i = 0; i < 9; i++, xoffset += ((i % 3 == 0 && i != 0) ? 55 : 50)) // row iter
		{
			std::string tempstr = (std::to_string(sudoku.table[j][i]) == "0") ? "" : std::to_string(sudoku.table[j][i]);
			makeButton(tempstr,
				font, xoffset, 105 + yoffset, normal, ID::box);
		}
	}
}

void Game::initButtons()
{
	std::pair<float, float> wide(150, 50);
	std::pair<float, float> normal(50, 50);

	makeButton("PLAY", font, 205, 400, wide, ID::play);
	makeButton("Generate", font, 145, 20, wide, ID::generate);
	makeButton("Solve", font, 300, 20, wide, ID::solve);

	makeButton("", font, 90, 20, normal, ID::back);
	makeButton("", font, 205, 455, normal, ID::settings);
	makeButton("", font, 305, 455, normal, ID::media);
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
				flaggedTextures.push_back(std::make_pair(loadTexture(x + ".jpg"), true));
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
	for (size_t i = 0; i < other_textures.size(); i++)
	{
		sf::Sprite temp;
		temp.setTexture(other_textures[i]);
		other_sprites.push_back(temp);
	}
	prepareSprites();
}

bool Game::loopHijacker(int table[9][9]) //returns if it's solved or not
{
	printf("l\n");/*
	window->clear();
	window->draw(other_sprites[eBg]);
	window->draw(other_sprites[eBgOverlay]);*/

	//for (size_t i = 0; i < buttons.size(); i++)
	//{
	//	drawInterractable(buttons[i], ID::generate);
	//	drawInterractable(buttons[i], ID::solve);
	//	drawInterractable(buttons[i], ID::back);
	//}

	for (int j = 0; j < 9; j++) 
	{
		for (int i = 0; i < 9; i++)
		{
			drawInterractable(boxes[j][i], ID::box);
		}
	}
	window->display();
	//TODO rendering, to slow down the algo. put a break point and see how it works and work around it.
	int row, col;
	if (!sudoku.emptyBoxes(row, col)) return true;
	for (int val = 1; val <= 9; val++)
	{

		if (sudoku.isSafe(row, col, val))
		{
			boxes[row][col].setText(std::to_string(val) );
			boxes[row][col].setState(eHovered);
			boxes[row][col].setTexture(interractable_textures);
			boxes[row][col].flipChangeable();
			table[row][col] = val;


			if (loopHijacker(table))
				return true;
			boxes[row][col].flipChangeable();
			//tru again!
			table[row][col] = 0;

			boxes[row][col].setText("");
			boxes[row][col].setState(eNone);
			boxes[row][col].setTexture(interractable_textures);

		}
	}

	// trigger for backtracking
	return false;
}

void Game::renderGenerating()
{
	window->draw(other_sprites[eBg]);
	window->draw(other_sprites[eBgOverlay]);

	for (size_t i = 0; i < buttons.size(); i++)
	{
		drawInterractable(buttons[i], ID::generate);
		drawInterractable(buttons[i], ID::solve);
		drawInterractable(buttons[i], ID::back);
	}

	for (int j = 0; j < 9; j++) //col iter
	{
		for (int i = 0; i < 9; i++)
		{
			drawInterractable(boxes[j][i], ID::box);
		}
	}
}

void Game::renderMain()
{
	window->draw(other_sprites[eBg]);
	window->draw(other_sprites[eBgOverlay]);

	for (size_t i = 0; i < buttons.size(); i++)
	{
		drawInterractable(buttons[i], ID::generate);
		drawInterractable(buttons[i], ID::solve);
		drawInterractable(buttons[i], ID::back);
	}

	for (int j = 0; j < 9; j++) //col iter
	{
		for (int i = 0; i < 9; i++)
		{
			drawInterractable(boxes[j][i], ID::box);
		}
	}

}

void Game::renderSettings()
{
	window->draw(other_sprites[eBg]);
	window->draw(other_sprites[eBgOverlay]);

	for (size_t i = 0; i < buttons.size(); i++)
	{
		drawInterractable(buttons[i], ID::back);
	}
}

void Game::renderIntro()
{
	window->draw(other_sprites[eIntroBg]);

	for (size_t i = 0; i < buttons.size(); i++)
	{
		drawInterractable(buttons[i], ID::play);
		drawInterractable(buttons[i], ID::settings);
		drawInterractable(buttons[i], ID::media);
	}
}

void Game::renderSolving()
{
}

void Game::renderSolvingAnimation(int table[9][9])
{
		int count = 0;
		for (int j = 0; j < 9; j++)
			for (int i = 0; i < 9; i++)
			{
				window->clear();
				renderMain();
				if (!boxes[j][i].getChangeable())
				{

					count++;
					boxes[j][i].flipChangeable();
					boxes[j][i].resourcesHandler(eNone);
					drawInterractable(boxes[j][i], ID::box);
				}
				window->display();
			}

	
}
