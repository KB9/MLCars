#pragma once

#include <vector>

#include "Genome.h"

class GenAlg
{
private:
	// Holds the entire population of chromosomes
	std::vector<Genome> population;

	// Size of population
	int population_size;

	// Amount of weights per chromosome
	int chromosome_length;

	// Total fitness of population
	double total_fitness;

	// Best fitness of this population
	double best_fitness;

	// Average fitness of this population
	double average_fitness;

	// Worst fitness of this population
	double worst_fitness;

	// Keeps track of the best genome
	int fittest_genome;

	// Probability that a chromosomes bits will mutate
	// Should be figures around 0.05 to 0.3 ish.
	double mutation_rate;

	// Probability of chromosomes crossing over bits
	double crossover_rate;

	// Generation counter
	int generation;

	void crossover(const std::vector<double>& mum,
		const std::vector<double>& dad,
		std::vector<double>& baby1,
		std::vector<double>& baby2);

	void mutate(std::vector<double>& chromosome);

	Genome getChromosomeRoulette();

	void grabNBest(int n_best, const int num_copies, std::vector<Genome>& population);

	void calculateBestWorstAverageTotal();

	void reset();

public:
	GenAlg(int population_size, double mutation_rate, double crossover_rate, int weights);

	// This runs the genetic algorithm for one generation
	std::vector<Genome> epoch(std::vector<Genome>& old_population);

	// Accessor methods
	std::vector<Genome> getChromosomes() const
	{
		return population;
	}

	double getAverageFitness() const
	{
		return total_fitness / population_size;
	}

	double getBestFitness() const
	{
		return best_fitness;
	}
};