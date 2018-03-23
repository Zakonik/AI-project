#pragma once
#include<vector>
#include<iostream>
#include"random.h"
#include<cassert>
#include<cmath>

class Neuron;

typedef std::vector <Neuron> Layer;

class Neuron
{
public:
	Neuron(unsigned numOutputs, unsigned myIndex);
	void setOutputVal(double val) { m_outputVal = val; }
	double getOutputVal() const { return m_outputVal; }
	void feedForward(const Layer &prevLayer);
	void setWeights(std::vector<double> weight) { m_outputWeights = weight; }
	std::vector<double> getWeights() const { return m_outputWeights; }


private:
	static double transferFunction(double x);
	double m_outputVal;
	std::vector<double> m_outputWeights;
	unsigned myIndex;

};



class Net
{
public:
	Net();
	Net(std::vector<unsigned> topology);
	void feedForward(const std::vector<double> &inputVals);
	void setWeights(std::vector<double> DNA);
	void getResults(std::vector<double>& a);
	std::vector<double> getWeights();

	

private:
	std::vector<Layer> m_layers;
};

