#pragma once
#include<string>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<cmath>
#include<iostream>
#include<vector>
#include"NeuralNetwork.h"
#include"random.h"

#define PI 3.14159265358979323846

class Sensor
{
public:
	Sensor();
	sf::FloatRect hitbox;
	sf::RectangleShape body;

private:

};



class Creature
{
public:
	
	Creature();
	void moveForward();
	void rotateLeft();
	void rotateRight();

	sf::CircleShape body;
	sf::Texture texture;
	sf::FloatRect hitbox;
	//sf::RectangleShape healthBar;
	std::vector<Sensor> Sensors;
	Net controlNet;

	sf::Clock clock;
	sf::Time time_of_life;
	sf::Time maxLife;

	double getHealth();
	void changeHealth(double a);

	
	double getHunger() const { return hunger; }
	double getThirst() const { return thirst; }
	void changeHunger(double a);
	void changeThirst(double a);

	void setFitness(double a) { this->fitnes += a; }
	double getFitness() const { return fitnes; }
	void caltulateFintess();

	void controls();

	void mutation(double mumationRatio);

	void setInput(std::vector<double> &input);
	sf::Vector2f getStart() { return starPosition; }

private:
	double health;
	double fitnes;
	double hunger, thirst;
	std::vector<double> input;
	sf::Vector2f starPosition;
};

bool operator <(const Creature &a, const Creature &b);


