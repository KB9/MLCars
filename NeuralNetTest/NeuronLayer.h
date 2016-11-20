#pragma once

#include <vector>
#include "Neuron.h"

struct NeuronLayer
{
	// The number of neurons in this layer
	int num_neurons;

	// The layer of neurons
	std::vector<Neuron> neurons;

	NeuronLayer(int num_neurons, int num_inputs_per_neuron);
};