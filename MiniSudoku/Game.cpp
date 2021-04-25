#include "Game.h"
Game::Game()
{
	gamestate = Gstate::Intro;
	font = makeFont();
	window = makeWindow();
	initTable();
	initTextures();
	initSprites();
	initButtons();
	initBoxes();
	initSounds();
	initMedia();
}

void Game::render() {
	window->clear();

	switch (gamestate)
	{
	case Gstate::Intro:
		renderIntro();
		break;

	case Gstate::IntroAnimation:
		renderIntroAnimation();

		gamestate = Gstate::Main;
		break;

	case Gstate::IntroAnimationReverse:
		renderIntroAnimationReverse();
		gamestate = Gstate::Intro;
		break;

	case Gstate::Main:
		renderMain();
		break;

	case Gstate::Solving:
		loopHijacker(sudoku.table);
		gamestate = Gstate::SolvingAnimation;
		break;

	case Gstate::SolvingAnimation:

		renderSolvingAnimation(sudoku.table);
		gamestate = Gstate::Main;
		break;

	case Gstate::Generating:
		renderGenerating();
		break;

	case Gstate::Media:
		renderMedia();
		break;

	case Gstate::Settings:
		renderSettings();
		break;

	case Gstate::NumberPicker:
		renderNumberPicker();
		break;
	default:
		printf("no man should be here\n");
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
			if (!handleSfmlMouseEvent(event))
			{
				keyboardEventHandlerNr(handleSfmlKeyboardEvent(event));

			}

			
			mouseEventHandler(mouseEvent);
		}
		render();
	}
}
void Game::keyboardEventHandlerNr(int nr)
{
	if (gamestate == Gstate::NumberPicker) //if we are in the correct gamestate
	{
		for (size_t j = 0; j < boxes.size(); j++) //go through every col
		{
			for (size_t i = 0; i < boxes[j].size(); i++) //go through every row
			{
				if (boxes[j][i].getState() == eHovered) //if sth is selected
				{
					std::string temp = (nr == 0) ? "": std::to_string(nr);
					sudoku.table[j][i] = nr;
					boxes[j][i].setText(temp); //set the number
					gamestate = Gstate::Main;
				}
			}
		}
	}
}
int Game::handleSfmlKeyboardEvent(sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		if (event.key.code == sf::Keyboard::Key::Escape)
		{
			if (gamestate != Gstate::Intro)gamestate = Gstate::Intro;
			else window->close();
		}

		else if (event.key.code == sf::Keyboard::Key::Enter)
		{
			if (gamestate == Gstate::Intro)
			{
				gamestate = Gstate::Main;
			}
		}
		else if (event.key.code >= sf::Keyboard::Key::Num0 && event.key.code <= sf::Keyboard::Key::Num9)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Key::Num0:
				return 0;
				
			case sf::Keyboard::Key::Num1:
				return 1 ;
				
			case sf::Keyboard::Key::Num2:
				return 2;
				
			case sf::Keyboard::Key::Num3:
				return 3 ;
				
			case sf::Keyboard::Key::Num4:
				return 4 ;
				
			case sf::Keyboard::Key::Num5:
				return  5;

			case sf::Keyboard::Key::Num6:
				return 6;

			case sf::Keyboard::Key::Num7:
				return 7;

			case sf::Keyboard::Key::Num8:
				return 8;

			case sf::Keyboard::Key::Num9:
				return 9;
			}
		}
		break;
	case sf::Event::Closed:
		window->close();
	default:
		break;
	}
	return 0;
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
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
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

bool Game::handleSfmlMouseEvent(sf::Event event)
{
	switch (event.type)
	{

	case sf::Event::MouseButtonPressed:
		mouseEvent.type = ButtonEventType::Pressed;

		return 1;
	case sf::Event::MouseButtonReleased:
		mouseEvent.type = ButtonEventType::Released;
		return 1;

	case sf::Event::MouseMoved:
		mouseEvent.type = ButtonEventType::Moved;
		mouseEvent.mousePos = sf::Mouse::getPosition(*window);
		return 1;

	default:
		mouseEvent.type = ButtonEventType::None;
		return 0;
	}
}

void Game::buttonMouseHandler(int newButtonState, sf::Vector2i v2i)
{
	checkButtonColision(buttons, v2i, newButtonState, 1);

	if (gamestate == Gstate::Solving ||
		gamestate == Gstate::Generating ||
		gamestate == Gstate::Main) {
		for (size_t j = 0; j < boxes.size(); j++)
		{
			checkButtonColision(boxes[j], v2i, newButtonState, 0);
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

		makeSound(btn, boxPressSound, btnPressSound);

		window->draw(btn.getRect());
		window->draw(btn.getText());
	}
}
void Game::makeSound(Button& btn, sf::Sound& boxPressSound, sf::Sound& btnPressSound)
{
	if (btn.getNoise())
	{
		if (btn.getId() == ID::box || btn.getId() == ID::back)
			boxPressSound.play();

		else btnPressSound.play();

		btn.resetNoise();
	}
}
void Game::prepareSprites()
{
	other_sprites[eBg].setScale(18.75, 18.75);

	other_sprites[eIntroBg].setScale(3.733333333, 4);
	other_sprites[eIntroBg2].setScale(3.733333333, 4);
	other_sprites[eIntroBg0].setScale(3.733333333, 4);

	other_sprites[eBgOverlay].setScale(4, 4);
	other_sprites[eNrPickerOverlay].setScale(4, 4);
}

void  Game::checkButtonColision(std::vector<Button>& btns, sf::Vector2i mousepos, int newButtonState, bool isButton)
{
	//MY PURPOSE:
	//i check if the buttons you are trying to push are within reach (in the same gamestate)

	if (!isButton)//if it's a box
	{
		for (size_t i = 0; i < btns.size(); i++)
		{

			if (btns[i].checkBounds(mousepos))
			{
				//we know the button contains the cursor. We are hovering/holding
				Pgamestate = gamestate;
				Gstate temp = btns[i].resourcesHandler(newButtonState);

				gamestate = (temp == Gstate::Debug) ? gamestate : temp;

			}
			else
			{
				btns[i].resourcesHandler(eNone);
			}
		}
	}

	else //we check if the buttons are reachable relative to the gamestate we're in
	{
		for (size_t i = 0; i < btns.size(); i++)
		{
			bool valid = false;
			switch (gamestate)
			{
			case Gstate::Main: //generate and solving don't get here. they hijack the loop
				if (btns[i].id == ID::generate || btns[i].id == ID::solve || btns[i].id == ID::back)
					valid = true;

				break;
			case Gstate::Intro:
				if (btns[i].id == ID::play || btns[i].id == ID::media || btns[i].id == ID::settings)
					valid = true;

				break;
			case Gstate::Media:
				if (btns[i].id == ID::back)
					valid = true;

				break;
			case Gstate::Settings:
				if (btns[i].id == ID::back)
					valid = true;

				break;
			case Gstate::NumberPicker:
				if (btns[i].id == ID::back)
					valid = true;

				break;
			default:
				/*
printf("debug GState ");
for (size_t i = 0; i < btns.size(); i++)
{

	if (btns[i].checkBounds(mousepos))
	{
		Gstate temp = btns[i].resourcesHandler(newButtonState);
		Pgamestate = gamestate;
		gamestate = (temp == Gstate::Debug) ? gamestate : temp;

	}
	else
		btns[i].resourcesHandler(eNone);

}
*/
				break;

			}

			if (valid && btns[i].checkBounds(mousepos))
			{
				//we know the button contains the cursor. We are hovering/holding
				Pgamestate = gamestate;
				Gstate temp = btns[i].resourcesHandler(newButtonState);

				gamestate = (temp == Gstate::Debug) ? gamestate : temp;
				return;
			}
			btns[i].resourcesHandler(eNone);
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

	btnPressSoundBuffer.loadFromFile("Resources\\Sounds\\btnsound.ogg");
	btnPressSound.setBuffer(btnPressSoundBuffer);
	btnPressSound.setVolume(20);

	boxPressSoundBuffer.loadFromFile("Resources\\Sounds\\boxsound.wav");
	boxPressSound.setBuffer(boxPressSoundBuffer);
	//boxPressSound.setVolume(20);
}

void Game::initMedia()
{

	std::ifstream read;
	read.open("Resources\\media.txt");
	std::string tempstr;
	int i = -1;
	int offset = 110;
	while (std::getline(read, tempstr))
	{
		sf::Text* text = new sf::Text;
		text->setFont(font);
		text->setString(tempstr);
		text->setPosition(65, i * 50 + offset);
		text->setCharacterSize(20);
		text->setFillColor(sf::Color::Black);

		if (i == -1)
		{
			nrSelectorText = *text;
			nrSelectorText.setCharacterSize(30);
			nrSelectorText.setPosition(190,70);
		}
		else texts.push_back(*text);
		i++;
	}

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
				flaggedTextures.push_back(std::make_pair(loadTexture(x + ".png"), false));
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
	renderMain(1);/*
	window->clear();
	window->draw(other_sprites[eBg]);
	window->draw(other_sprites[eBgOverlay]);*/

	for (int j = 0; j < 9; j++)
	{
		for (int i = 0; i < 9; i++)
		{
			drawInterractable(boxes[j][i], ID::box);
		}
	}
	window->display();

	int row, col;
	if (!sudoku.emptyBoxes(row, col)) return true;
	for (int val = 1; val <= 9; val++)
	{

		if (sudoku.isSafe(row, col, val))
		{
			boxes[row][col].setText(std::to_string(val));
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
	renderMain();
}
void Game::renderNumberPicker()
{
	renderMain();
	window->draw(other_sprites[eNrPickerOverlay]);
	window->draw(nrSelectorText);
}
void Game::renderMain(bool optional)
{
	window->draw(other_sprites[eBg]);
	window->draw(other_sprites[eBgOverlay]);

	for (size_t i = 0; i < buttons.size(); i++)
	{
		drawInterractable(buttons[i], ID::generate);
		drawInterractable(buttons[i], ID::solve);
		drawInterractable(buttons[i], ID::back);
	}
	if (!optional)
	{
		for (int j = 0; j < 9; j++) //col iter
		{
			for (int i = 0; i < 9; i++)
			{
				drawInterractable(boxes[j][i], ID::box);
			}
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
	window->draw(other_sprites[eIntroBg2]);
	window->draw(other_sprites[eIntroBg0]);

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

void Game::renderMedia()
{
	window->draw(other_sprites[eBg]);
	window->draw(other_sprites[eBgOverlay]);
	for (size_t i = 0; i < buttons.size(); i++)
	{
		drawInterractable(buttons[i], ID::back);
	}
	for (int i = 0; i < texts.size(); i++)
	{
		window->draw(texts[i]);
	}
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

void Game::renderIntroAnimation()
{
	for (size_t i = 0; i < buttons.size(); i++)
	{
		makeSound(buttons[i], boxPressSound, btnPressSound);
	}
	sf::Color fade(255, 255, 255, 255);
	int alpha = 255;
	for (int i = 0; i < 150; i++)
	{
		window->clear();


		renderMain();
		window->draw(other_sprites[eIntroBg]);
		window->draw(other_sprites[eIntroBg2]);
		window->draw(other_sprites[eIntroBg0]);

		other_sprites[eIntroBg].move(0, 5);
		other_sprites[eIntroBg2].move(0, -5);
		fade = sf::Color(255, 255, 255, alpha);
		other_sprites[eIntroBg0].setColor(fade);


		if (alpha > 0)
			alpha -= 1.7;
		else if (alpha < 3)
			alpha = 0;

		window->display();
	}

	other_sprites[eIntroBg0].setColor(sf::Color(255, 255, 255, 255));
	other_sprites[eIntroBg2].setPosition(0, 0);
	other_sprites[eIntroBg].setPosition(0, 0);
}

void Game::renderIntroAnimationReverse()
{

	sf::Color fade(255, 255, 255, 0);

	other_sprites[eIntroBg2].setPosition(0, -750);
	other_sprites[eIntroBg].setPosition(0, 750);
	other_sprites[eIntroBg0].setColor(fade);


	int alpha = 0;

	for (int i = 0; i < 100; i++)
	{
		window->clear();
		switch (Pgamestate)
		{
		case Gstate::Media:
			renderMedia();
			break;

		case Gstate::Settings:
			renderSettings();
			break;

		case Gstate::Generating:
		case Gstate::Solving:
		case Gstate::Main:
			renderMain();
			break;

		case Gstate::NumberPicker:
			renderNumberPicker();
			break;
		}

		window->draw(other_sprites[eIntroBg]);
		window->draw(other_sprites[eIntroBg2]);
		window->draw(other_sprites[eIntroBg0]);

		other_sprites[eIntroBg].move(0, -7.5);
		other_sprites[eIntroBg2].move(0, 7.5);
		other_sprites[eIntroBg0].setColor(fade);
		//for (int i = 0; i < buttons.size(); i++)
		//{
		//	buttons[1].getRect().move(0,3);
		//	buttons[1].getText().move(0,3);

		//}
		fade = sf::Color(255, 255, 255, alpha);

		if (i > 50)
		{
			if (alpha < 250) alpha += 5;
			else alpha = 255;
		}

		window->display();
	}
	fade = sf::Color(255, 255, 255, 255);

	other_sprites[eIntroBg0].setColor(fade);
	other_sprites[eIntroBg2].setPosition(0, 0);
	other_sprites[eIntroBg].setPosition(0, 0);
}
