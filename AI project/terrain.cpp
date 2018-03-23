#include"terrain.h"

bush::bush()
{
	body.setRadius(10);
	body.setFillColor(sf::Color::Green);
	body.setPosition(randomReal(10, 1270), randomReal(10, 710));
	this->health = 100;
	hitbox = body.getGlobalBounds();
}

int bush::getHealth()
{
	return this->health;
}

void bush::changeHealth(int a)
{
	this->health += a;
	alpha = sf::Color::Green;
	alpha.a = sf::Color::Green.a*(static_cast<double>(health) / 100);
	body.setFillColor(alpha);
}

water::water()
{
	body.setRadius(10);
	body.setFillColor(sf::Color::Blue);
	body.setPosition(randomReal(10, 1270), randomReal(10, 710));
	this->health = 100;
	hitbox = body.getGlobalBounds();
}

int water::getHealth()
{
	return this->health;
}

void water::changeHealth(int a)
{
	this->health += a;
	alpha = sf::Color::Blue;
	alpha.a = sf::Color::Blue.a*(static_cast<double>(health) / 100);
	body.setFillColor(alpha);
}

trap::trap()
{
	body.setRadius(10);
	body.setFillColor(sf::Color::Red);
	body.setPosition(randomReal(10, 1270), randomReal(1, 710));
	this->health = 100;
	hitbox = body.getGlobalBounds();
}

int trap::getHealth()
{
	return this->health;
}

void trap::changeHealth(int a)
{
	this->health += a;
}
