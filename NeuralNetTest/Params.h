#pragma once

class Params
{
public:
	// Used for the neural network
	static const int num_inputs = 4;
	static const int num_hidden_layers = 1;
	static const int num_neurons_per_hidden_layer = 6;
	static const int num_outputs = 2;

	// For tweaking the sigmoid function
	static constexpr double activation_response = 1.0;

	// Bias value
	static constexpr double bias = -1.0;

	// Genetic algorithm parameters
	static constexpr double crossover_rate = 0.7;
	static constexpr double mutation_rate = 0.1;

	// Maximum amount each weight may mutate by
	static constexpr double max_perturbation = 0.3;

	// Used for elitism
	static const int num_elite = 4;
	static const int num_copies_elite = 1;
};