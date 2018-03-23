#pragma once
#include"creature.h"
#include<vector>
#include"random.h"
#include<algorithm>

class Population
{
public:
	Population(unsigned n, double mutationRatio);
	std::vector<Creature> testSubs;
	std::vector<std::vector<double>> meeting_pool;
	bool populationAlive;

	void Repopulate();
	void CheckAlive();
	

private:
	double mutationRatio;
	unsigned popolution_size;
	std::vector<double> crossover(std::vector<double> DNA1, std::vector<double>DNA2);
};
