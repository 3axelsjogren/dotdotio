#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Player
{

private:
	sf::RectangleShape shape;

	// game logic
	float movementSpeed;
	
	int hp;
	int hpMax;

	// private functions
	void initVariables();
	void initShape();

public:
	// constructor and destructor
	Player(float x = 0.f, float y = 0.f);
	virtual ~Player();

	// accessors
	const sf::RectangleShape& getShape() const;
	const int& getHp() const;
	const int& getHpMax() const;

	// functions
	void takeDamage(const int damage);
	void gainHealth(const int health);

	void updateInput();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void update(sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

