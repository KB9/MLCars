#include <vector>

#include "NeuralNet.h"
#include "NeuronLayer.h"
#include "Params.h"

NeuralNet::NeuralNet()
{
	num_inputs = Params::num_inputs;
	num_outputs = Params::num_outputs;
	num_hidden_layers = Params::num_hidden_layers;
	num_neurons_per_hidden_layer = Params::num_neurons_per_hidden_layer;

	createNet();
}

/*
	Builds the artificial neural network. The weights are all initially set to random values
	-1 < w < 1.
*/
void NeuralNet::createNet()
{
	// Create the layers of the network
	if (num_hidden_layers > 0)
	{
		// Create the first hidden layer
		layers.push_back(NeuronLayer(num_neurons_per_hidden_layer, num_inputs));

		for (int i = 0; i < num_hidden_layers - 1; ++i)
		{
			layers.push_back(NeuronLayer(num_neurons_per_hidden_layer, num_neurons_per_hidden_layer));
		}

		// Create the output layer
		layers.push_back(NeuronLayer(num_outputs, num_neurons_per_hidden_layer));
	}
	else
	{
		// Create the output layer
		layers.push_back(NeuronLayer(num_outputs, num_inputs));
	}
}

/*
	Returns a vector containing the weights
*/
std::vector<double> NeuralNet::getWeights() const
{
	// Holds the weights
	std::vector<double> weights;

	// For each layer
	for (int i = 0; i < num_hidden_layers + 1; ++i)
	{
		// For each neuron
		for (int j = 0; j < layers[i].num_neurons; ++j)
		{
			// For each weight
			for (int k = 0; k < layers[i].neurons[j].num_inputs; ++k)
			{
				weights.push_back(layers[i].neurons[j].weights[k]);
			}
		}
	}

	return weights;
}

/*
	Returns the total number of weights needed for the network.
*/
int NeuralNet::getNumberOfWeights() const
{
	int weights = 0;

	// For each layer
	for (int i = 0; i < num_hidden_layers + 1; ++i)
	{
		// For each neuron
		for (int j = 0; j < layers[i].num_neurons; ++j)
		{
			// For each weight
			for (int k = 0; k < layers[i].neurons[j].num_inputs; ++k)
			{
				weights++;
			}
		}
	}

	return weights;
}

/*
	Given a vector of doubles, this function replaces the weights in the neural network with
	the new values.
*/
void NeuralNet::putWeights(std::vector<double>& weights)
{
	int weight = 0;

	// For each layer
	for (int i = 0; i < num_hidden_layers + 1; ++i)
	{
		// For each neuron
		for (int j = 0; j < layers[i].num_neurons; ++j)
		{
			// For each weight
			for (int k = 0; k < layers[i].neurons[j].num_inputs; ++k)
			{
				layers[i].neurons[j].weights[k] = weights[weight++];
			}
		}
	}
}

/*
	Given an input vector, this function calculates the output vector.
*/
std::vector<double> NeuralNet::update(std::vector<double>& inputs)
{
	// Stores the resultant outputs from each layer
	std::vector<double> outputs;

	int weight = 0;

	// First check that we have the correct amount of inputs
	if (inputs.size() != num_inputs)
	{
		// Just return an empty vector if incorrect
		return outputs;
	}

	// For each layer...
	for (int i = 0; i < num_hidden_layers + 1; ++i)
	{
		if (i > 0)
		{
			inputs = outputs;
		}

		outputs.clear();

		weight = 0;

		// For each neuron, sum the (inputs * corresponding weights).
		// Throw the total at the sigmoid function to get the output.
		for (int j = 0; j < layers[i].num_neurons; ++j)
		{
			double net_input = 0;

			int num_inputs = layers[i].neurons[j].num_inputs;

			// For each weight
			for (int k = 0; k < num_inputs - 1; ++k)
			{
				// Sum the weights * inputs
				net_input += layers[i].neurons[j].weights[k] * inputs[weight++];
			}

			// Add in the bias
			net_input += layers[i].neurons[j].weights[num_inputs - 1] * Params::bias;

			// Outputs from each layer can be stored as they are generated.
			// The combined activation is first filtered through the sigmoid function
			outputs.push_back(sigmoid(net_input, Params::activation_response));

			weight = 0;
		}
	}

	return outputs;
}

/*
	Sigmoid function
*/
double NeuralNet::sigmoid(double net_input, double response)
{
	return (1 / (1 + exp(-net_input / response)));
}