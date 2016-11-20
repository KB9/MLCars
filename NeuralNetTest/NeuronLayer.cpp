#include "NeuronLayer.h"

NeuronLayer::NeuronLayer(int num_neurons, int num_inputs_per_neuron) : neurons(num_neurons)
{
	for (int i = 0; i < num_neurons; ++i)
	{
		neurons.push_back(Neuron(num_inputs_per_neuron));
	}
}