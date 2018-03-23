#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include"creature.h"
#include<iostream>
#include"terrain.h"
#include"random.h"
#include<vector>
#include"NeuralNetwork.h"
#include"Genetic Algorithm.h"


int main()
{
	/*std::vector<unsigned> topology;
	topology.push_back(11);
	topology.push_back(3);*/
	//std::vector<double> result;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Evolution simulator");
	window.setFramerateLimit(60);
	int population_size=10;
	double mutationRatio = 0.05;
	int terrain_size = 50;

	Population population(population_size, mutationRatio);
	
	std::vector<water> waters(terrain_size);
	std::vector<bush> bushes(terrain_size);
	std::vector<trap> traps(terrain_size);
	double regHealth = 0;
	std::vector<double> input(11);
	sf::Clock timer;
	sf::Time runningTime;
	bool notMoving=true;



	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}
		window.clear(sf::Color::White);
		

		//Draw terrain
		for (int i = 0; i < waters.size(); i++)
		{
			if (waters[i].getHealth() > 0) 
			{
				window.draw(waters[i].body);
			}
			if (bushes[i].getHealth() > 0) {

				window.draw(bushes[i].body);
			}
			if (traps[i].getHealth() > 0) 
			{
				window.draw(traps[i].body);
			}
		}

		runningTime = timer.getElapsedTime();
		population.CheckAlive();
		if (runningTime.asSeconds() >= 300||!population.populationAlive)
		{
			for (auto &x : population.testSubs)
			{
				if (x.getFitness() == 0)
				{
					x.caltulateFintess();
				}
			}
			population.Repopulate();
			timer.restart();
		}

		if (runningTime.asSeconds() >= 60&& notMoving)
		{
			for (auto &x : population.testSubs)
			{
				if (x.getStart() == x.body.getPosition())
				{
					x.changeHealth(-100);
					x.setFitness(-100);
				}
			}
		}

		

		//Draw creature
		//window.draw(population.testSubs[0].body);
		for (auto &x : population.testSubs)
		{
			if (x.getHealth() > 0)
			{
				window.draw(x.body);
				window.draw(x.Sensors[4].body);
			}
			else
			{
				if ((x.getHunger() > 100 && x.getThirst() > 100) || (x.getHunger() <= 0 && x.getThirst() <= 0) || (x.getHunger() > 100 && x.getThirst() <= 0) || (x.getHunger() <= 0 && x.getThirst() > 100))
				{
					x.setFitness(-50);
				}
				else if (x.getHunger()>100||x.getThirst()>100||x.getHunger()<=0||x.getThirst()<=0)
				{
					x.setFitness(-25);
				}
				x.caltulateFintess();
			}
		}



		//Draw health bar
		//window.draw(test.healthBar);

		window.display();

		//Controls
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			test.rotateLeft();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			test.rotateRight();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			test.moveForward();
		}*/

		//change of stats
		for (auto &x : population.testSubs)
		{
			x.changeHunger(-0.05);
			x.changeThirst(-0.08);
		}

		//Creature Hitbox check
		for (auto &x : population.testSubs)
		{
			for (int i = 0; i <  waters.size(); i++)
			{
				if (x.hitbox.intersects(waters[i].hitbox) && waters[i].getHealth() > 0 && x.getHealth() > 0)
				{
					waters[i].changeHealth(-1);
					x.changeThirst(1);
				}
				else if (x.hitbox.intersects(bushes[i].hitbox) && bushes[i].getHealth() > 0 && x.getHealth() > 0)
				{
					bushes[i].changeHealth(-1);
					x.changeHunger(1);
				}
				else if (x.hitbox.intersects(traps[i].hitbox) && traps[i].getHealth() > 0 && x.getHealth() > 0)
				{
					x.changeHealth(-100);
					traps[i].changeHealth(-100);
					x.setFitness(-50);
				}
				else if ((!x.hitbox.intersects(waters[i].hitbox) && waters[i].getHealth() < 100) || (bushes[i].getHealth() < 100 && !x.hitbox.intersects(bushes[i].hitbox)))
				{
					regHealth += 0.1;
					if (regHealth >= 1 && bushes[i].getHealth() < 100)
					{
						bushes[i].changeHealth(regHealth);
						regHealth = 0;
					}
					else if (regHealth >= 1 && waters[i].getHealth() < 100)
					{
						waters[i].changeHealth(regHealth);
						regHealth = 0;
					}

				}
			}
		}

		//check stats
		for (auto &x : population.testSubs)
		{
			if (x.getHunger() > 100 || x.getThirst() > 100 || x.getHunger() < 0 || x.getThirst() < 0)
			{
				x.changeHealth(-0.2);
			}
			
		}
		//Sensors hitbox check and input values
		for (auto &x : population.testSubs)
		{
			for (auto &y : input)
			{
				y = 0;
			}
			for (int i = 0; i <  waters.size(); i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if (x.Sensors[j].hitbox.intersects(waters[i].hitbox) && waters[i].getHealth() > 0 && x.getHealth() > 0)
					{
						input[j] = 1;
					}
					else if (x.Sensors[j].hitbox.intersects(bushes[i].hitbox) && bushes[i].getHealth() > 0 && x.getHealth() > 0)
					{
						input[j] = -1;
					}
					else if (x.Sensors[j].hitbox.intersects(traps[i].hitbox) && traps[i].getHealth() > 0 && x.getHealth() > 0)
					{
						input[j] = 0;
					}
					else if (!x.Sensors[j].hitbox.intersects(traps[i].hitbox) && !x.Sensors[j].hitbox.intersects(bushes[i].hitbox) && x.Sensors[j].hitbox.intersects(waters[i].hitbox))
					{
						input[j] = 0;
					}
				}
			}
			if (x.getHunger() < 50)
			{
				input[9] = 20;
			}
			else if (x.getHunger() > 75)
			{
				input[9] = 0;
			}
			if (x.getThirst() < 50)
			{
				input.back() = 20;
			}
			else if (x.getThirst() > 75)
			{
				input[9] = 0;
			}
			x.setInput(input);
		}
		
		
		/*for (const auto &x : input)
		{
			std::cout << x << " ";
		}
		std::cout << std::endl;*/

		//network work
		/*controlNetwork.feedForward(input);
		controlNetwork.getResults(result);
		std::vector<int> DNA=controlNetwork.getWeights();*/
		
		/*for (auto x : result)
		{
			std::cout << x << " ";
		}
		std::cout << std::endl;*/

		//AI control
		for (auto &x : population.testSubs)
		{
			if (x.getHealth() > 0)
			{
				x.controls();
			}
		}
		//std::cout << "check" << std::endl;

	}
	return EXIT_SUCCESS;
}
