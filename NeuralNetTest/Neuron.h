#pragma once

#include <vector>

struct Neuron
{
	// The number of inputs into the neuron
	int num_inputs;

	// The weights for each input
	std::vector<double> weights;

	Neuron(int num_inputs);
	Neuron() {}	// NOTE: REQUIRED AS ITS INSTANTIATED VIA VECTOR IN NEURONLAYER.H
};