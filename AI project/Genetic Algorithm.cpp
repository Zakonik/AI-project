#include "Genetic Algorithm.h"

Population::Population(unsigned n, double mutationRatio)
{
	
	for (unsigned i = 0; i < n; i++)
	{
		Creature temp;
		testSubs.push_back(temp);
	}

	this->mutationRatio = mutationRatio;
	this->popolution_size = n;
	this->populationAlive = true;
}

void Population::Repopulate()
{
	meeting_pool.clear();
	std::sort(testSubs.begin(), testSubs.end());
	for (unsigned i = 0; i < popolution_size; i++)
	{
		for (unsigned j = 0; j < popolution_size - i; i++)
		{
			meeting_pool.push_back(testSubs[i].controlNet.getWeights());
		}
	}
	testSubs.clear();
	for (unsigned i = 0; i < popolution_size; i++)
	{
		Creature* child = new Creature;
		std::vector<double> parent1_DNA, paretn2_DNA,child_DNA;
		parent1_DNA = meeting_pool[randomInt(0, meeting_pool.size() - 1)];
		paretn2_DNA = meeting_pool[randomInt(0, meeting_pool.size() - 1)];
		child_DNA = crossover(parent1_DNA, paretn2_DNA);
		child->controlNet.setWeights(child_DNA);
		child->mutation(mutationRatio);
		testSubs.push_back(*child);
		delete(child);
	}
}

void Population::CheckAlive()
{
	for (auto &x : testSubs)
	{
		if (x.getHealth() > 0)
		{
			this->populationAlive = true;
			break;
		}
		else
		{
			this->populationAlive = false;
		}
	}
}

std::vector<double> Population::crossover(std::vector<double> DNA1, std::vector<double> DNA2)
{
	std::vector<double> DNA;
	for (unsigned i = 0; i < DNA1.size(); i++)
	{
		if (i % 2 == 0)
		{
			DNA.push_back(DNA1[i]);
		}
		else
		{
			DNA.push_back(DNA2[i]);
		}
	}
	return DNA;
}
