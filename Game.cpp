#include "Game.h"

void Game::initVariables()
{
	this->endGame = false;
	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxSwagBalls = 10;
	this->points = 0;
}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(800, 600); // eller this->videoMode = sf::VideoMode::getDesktopMode();
	this->window = new sf::RenderWindow(this->videoMode, "GAME 1", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("Fonts/gomarice_game_music_love.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << std::endl;
	}
}

void Game::initText()
{
	//gui text init
	this->guiText.setFont(this->font);
	this->guiText.setFillColor(sf::Color::Yellow);
	this->guiText.setOutlineColor(sf::Color::Red);
	this->guiText.setOutlineThickness(1.f);
	this->guiText.setCharacterSize(20);
	this->guiText.setPosition(sf::Vector2f(10, 10));

	// end game text init
	this->endGameText.setFont(this->font);
	this->endGameText.setFillColor(sf::Color::Red);
	this->endGameText.setCharacterSize(60);
	this->endGameText.setPosition(sf::Vector2f(255, 250));
	this->endGameText.setString("GAME OVER");
}

// constructors and destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}

const bool& Game::getEndGame() const
{
	return this->endGame;
}

// functions

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->sfmlEvent)) 
	{
		switch (this->sfmlEvent.type) 
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->sfmlEvent.key.code == sf::Keyboard::Escape) 
			{
				this->window->close();
			}
			break;
		}
	}
}

void Game::spawnSwagBalls()
{
	//timer
	if (this->spawnTimer < this->spawnTimerMax) 
	{
		this->spawnTimer += 1.f;
	}
	
	else 
	{
		if (this->swagBalls.size() < this->maxSwagBalls) 
		{
			this->swagBalls.push_back(SwagBall(*this->window, this->randBallType()));

			this->spawnTimer = 0.f;
		}
	}
}

const int Game::randBallType() const
{
	int type = SwagBallTypes::DEFAULT;

	int randValue = rand() % 100 + 1;

	if (randValue > 60 && randValue <= 80) 
	{
		type = SwagBallTypes::DAMAGING;
	}
	
	else if (randValue > 80 && randValue <= 100) 
	{
		type = SwagBallTypes::HEALING;
	}

	return type;
}

void Game::updatePlayer()
{
	this->player.update(this->window);

	if (this->player.getHp() <= 0) 
	{
		this->endGame = true;
	}
}

void Game::updateCollision()
{
	// check the collision
	for (size_t i = 0; i < this->swagBalls.size(); i++) 
	{
		if (this->player.getShape().getGlobalBounds().intersects(this->swagBalls[i].getShape().getGlobalBounds()))
		{
			switch (this->swagBalls[i].getType()) 
			{
			case SwagBallTypes::DEFAULT:
				this->points++;
				break;
			case SwagBallTypes::DAMAGING:
				this->player.takeDamage(34);
				break;
			case SwagBallTypes::HEALING:
				this->player.gainHealth(8);
			}

			// add points
			this->points++;

			// remove the ball
			this->swagBalls.erase(this->swagBalls.begin() + i);
		}
	}
}

void Game::updateGui()
{
	std::stringstream ss;
	ss << "Points: " << this->points << std::endl << std::endl << "Health: " 
		<< this->player.getHp() << " / " 
		<< this->player.getHpMax() << std::endl;

	this->guiText.setString(ss.str());
}

void Game::update()
{
	this->pollEvents();

	if (this->endGame == false) 
	{
		this->spawnSwagBalls();
		this->updatePlayer();
		this->updateCollision();
		this->updateGui();
	}
}



void Game::renderGui(sf::RenderTarget* target)
{
	target->draw(this->guiText);
}

void Game::render()
{
	this->window->clear();

	//render stuff
	this->player.render(this->window);

	for (size_t i = 0; i < this->swagBalls.size(); ++i)
	{
		this->swagBalls[i].render(*this->window);
	}

	// render gui
	this->renderGui(this->window);

	// render end text
	if (this->endGame == true) 
	{
		this->window->draw(this->endGameText);
	}

	this->window->display();
}