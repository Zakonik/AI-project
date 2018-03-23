#pragma once
#include<string>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<math.h>
#include<iostream>
#include"random.h"

class bush
{
public:
	bush();

	sf::CircleShape body;
	sf::FloatRect hitbox;
	int getHealth();
	void changeHealth(int a);

private:
	int health;
	sf::Color alpha;

};

class water
{
public:
	water();

	sf::CircleShape body;
	sf::FloatRect hitbox;
	int getHealth();
	void changeHealth(int a);
private:
	int health;
	sf::Color alpha;

};

class trap
{
public:
	trap();

	sf::CircleShape body;
	sf::FloatRect hitbox;
	int getHealth();
	void changeHealth(int a);

private:
	int health;

};