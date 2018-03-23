#include"creature.h"

Creature::Creature()
{
	this->health = 100;
	this->fitnes = 100;
	this->hunger = 50;
	this->thirst = 50;
	this->maxLife = sf::milliseconds(300000);
	Net temp;
	this->controlNet = temp;
	//healthBar.setSize(sf::Vector2f(200, 20));
	//healthBar.setFillColor(sf::Color::Cyan);
	//healthBar.setPosition(0, 0);

	body.setRadius(10);
	body.setOrigin(10,10);
	body.setPosition(randomInt(10,1270), randomInt(10,710));
	this->starPosition = body.getPosition();
	body.setRotation(randomReal(0, 359));
	body.setFillColor(sf::Color::Black);
	if (!texture.loadFromFile("resources/creature.jpg"))
	{
		std::cout << "Brak tekstury" << std::endl;
	}
	else
	{
		body.setTexture(&texture);
	}

	hitbox = body.getGlobalBounds();
	Sensor sens;
	for (int i = 0; i < 9; i++)
	{
		Sensors.push_back(sens);
		Sensors[i].body.setOrigin(0, 0.5);
		Sensors[i].body.setPosition(body.getPosition());
		Sensors[i].body.setRotation(body.getRotation()-180 + (i)*22.5);
	}
	

}

void Creature::moveForward()
{
	body.move(1*std::sin(( PI/ 180)*body.getRotation()),1*-std::cos(( PI/ 180)*body.getRotation()));
	for (int i=0;i<9;i++)
	{
		Sensors[i].body.move(1 * std::sin((PI / 180)*Sensors[8].body.getRotation()), 1 * -std::cos((PI / 180)*Sensors[8].body.getRotation()));
		Sensors[i].hitbox = Sensors[i].body.getGlobalBounds();
	}
	hitbox = body.getGlobalBounds();
}

void Creature::rotateLeft()
{
	body.rotate(-1);
	for (auto &x : Sensors)
	{
		x.body.rotate(-1);
		x.hitbox = x.body.getGlobalBounds();
	}
	hitbox = body.getGlobalBounds();
	
}

void Creature::rotateRight()
{
	body.rotate(1);
	for (auto &x : Sensors)
	{
		x.body.rotate(1);
		x.hitbox = x.body.getGlobalBounds();
	}
	hitbox = body.getGlobalBounds();
}

double Creature::getHealth()
{
	return this->health;
}

void Creature::changeHealth(double a)
{
	this->health += a;
	//sf::Vector2f v = healthBar.getSize();
	//v.x += a*2;
	//this->healthBar.setSize(v);
}

void Creature::changeHunger(double a)
{
	this->hunger += a;
}

void Creature::changeThirst(double a)
{
	this->thirst += a;
}

void Creature::caltulateFintess()
{
	time_of_life = clock.getElapsedTime();

	this->fitnes = pow(2,this->fitnes* (time_of_life.asMilliseconds() / maxLife.asMilliseconds()));
}

void Creature::controls()
{
	controlNet.feedForward(input);
	std::vector<double> result;
	controlNet.getResults(result);
	if (result[0] > 0)
	{
		rotateLeft();
	}
	if (result[1] > 0)
	{
		rotateRight();
	}
	if (result[2] > 0)
	{
		moveForward();
	}

}

void Creature::mutation(double mutationRatio)
{
	std::vector<double> DNA=controlNet.getWeights();
	for (auto &x : DNA)
	{
		if (mutationRatio <= randomReal(0, 1))
		{
			x = randomReal(-8, 8);
		}
	}
	controlNet.setWeights(DNA);

}

void Creature::setInput(std::vector<double>& input)
{
	this->input = input;
}

Sensor::Sensor()
{
	body.setSize(sf::Vector2f(60, 1));
	body.setFillColor(sf::Color::Black);

	hitbox = body.getGlobalBounds();
}

bool operator<(const Creature & a, const Creature & b)
{
	if (a.getFitness() < b.getFitness())
	{
		return true;
	}
	else
	{
		return false;
	}
}
