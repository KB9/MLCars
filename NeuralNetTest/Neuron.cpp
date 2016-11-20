#include "Neuron.h"

#include <time.h>

#include "Utils.h"

Neuron::Neuron(int num_inputs) : num_inputs(num_inputs + 1)
{
	// Need an additional weight for the bias (hence +1)
	for (int i = 0; i < num_inputs + 1; ++i)
	{
		// Set up the weights with an initial random value
		weights.push_back(randomClamped());
	}
}