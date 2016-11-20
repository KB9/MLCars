#pragma once

#include <vector>

struct Genome
{
	std::vector<double> weights;

	double fitness;

	Genome() : fitness(0) {}

	Genome(std::vector<double> w, double f) : weights(w), fitness(f) {}

	// Overload '<' used for sorting
	friend bool operator<(const Genome& lhs, const Genome& rhs)
	{
		return (lhs.fitness < rhs.fitness);
	}
};