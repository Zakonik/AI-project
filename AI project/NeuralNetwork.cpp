#include "NeuralNetwork.h"

Net::Net()
{
	std::vector<unsigned> topology;
	topology.push_back(11);
	topology.push_back(3);

	unsigned numLayers = topology.size();
	for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum)
	{
		m_layers.push_back(Layer());
		unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

		for (unsigned neuronNum = 0; neuronNum < topology[layerNum]; ++neuronNum)
		{
			m_layers.back().push_back(Neuron(numOutputs,neuronNum));
		}
	}

}

Net::Net(std::vector<unsigned> topology)
{
	unsigned numLayers = topology.size();
	for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum)
	{
		m_layers.push_back(Layer());
		unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];
		for (unsigned neuronNum = 0; neuronNum <  topology[layerNum]; ++neuronNum)
		{
			m_layers.back().push_back(Neuron(numOutputs, neuronNum));
		}
	}
}

void Net::feedForward(const std::vector<double>& inputVals)
{
	assert(inputVals.size() == m_layers[0].size());
	for (unsigned i = 0; i < inputVals.size(); i++)
	{
		m_layers[0][i].setOutputVal(inputVals[i]);
	}

	for (unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum)
	{
		Layer &prevLayer = m_layers[layerNum - 1];
		for (unsigned n = 0; n < m_layers[layerNum].size(); n++)
		{
			m_layers[layerNum][n].feedForward(prevLayer);
		}
	}
}

void Net::setWeights(std::vector<double> DNA)
{
	int i = 0;
	std::vector<double> temp;
	for (unsigned layerNum = 0; layerNum < m_layers.size(); layerNum++)
	{
		for (unsigned n = 0; n < m_layers[layerNum].size(); n++)
		{
			for (unsigned c = 0; c < m_layers[layerNum][n].getWeights().size(); c++)
			{
				temp.push_back(DNA[i]);
				i++;
			}
			m_layers[layerNum][n].setWeights(temp);
		}

	}
}

 void Net::getResults(std::vector<double>&a)
{
	 a.clear();
	 for (unsigned n = 0; n < m_layers.back().size(); n++)
	 {
		 a.push_back(m_layers.back()[n].getOutputVal());
	 }
	
}

std::vector<double> Net::getWeights()
{
	std::vector<double> DNA;

	for (unsigned layerNum = 0; layerNum < m_layers.size(); layerNum++)
	{
		for (unsigned n = 0; n < m_layers[layerNum].size(); n++)
		{
			for (unsigned c = 0; c < m_layers[layerNum][n].getWeights().size(); c++)
			{
				DNA.push_back(m_layers[layerNum][n].getWeights()[c]);
			}
		}

	}

	return DNA;
}

Neuron::Neuron(unsigned numOutputs, unsigned myIndex)
{
	for (unsigned c = 0; c < numOutputs; ++c) {
		m_outputWeights.push_back(randomInt(-8, 8));
	}
	m_outputVal = 1;
	this->myIndex = myIndex;
}

void Neuron::feedForward(const Layer & prevLayer)
{
	double sum = 0;
	for (unsigned n = 0; n < prevLayer.size(); n++)
	{
		sum += prevLayer[n].getOutputVal()* prevLayer[n].m_outputWeights[myIndex];
	}

	m_outputVal = Neuron::transferFunction(sum);
}

double Neuron::transferFunction(double x)
{
	if (x > 1)
	{
		return pow(2,x); 
	}
	if (x < -1)
	{
		return -pow(2, x);
	}
	else
	{
		return 0;
	}
}
	