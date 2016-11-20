#pragma once

#include <vector>
#include "NeuronLayer.h"

class NeuralNet
{
private:
	int num_inputs;
	int num_outputs;
	int num_hidden_layers;
	int num_neurons_per_hidden_layer;

	// Storage for each layer of neurons including the output layer
	std::vector<NeuronLayer> layers;

public:
	NeuralNet();

	void createNet();

	// Gets the weights from the neural network
	std::vector<double> getWeights() const;

	// Returns the total number of weights in the net
	int getNumberOfWeights() const;

	// Replaces the weights with the new ones
	void putWeights(std::vector<double>& weights);

	// Calculates the outputs from a set of inputs
	std::vector<double> update(std::vector<double>& inputs);

	// Sigmoid response curve
	inline double sigmoid(double activation, double response);
};