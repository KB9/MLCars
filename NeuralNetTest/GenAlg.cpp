#include <time.h>
#include <algorithm>

#include "GenAlg.h"
#include "Genome.h"
#include "Utils.h"
#include "Params.h"

GenAlg::GenAlg(int population_size, double mutation_rate, double crossover_rate, int num_weights) :
	population_size(population_size),
	mutation_rate(mutation_rate),
	crossover_rate(crossover_rate),
	chromosome_length(num_weights),
	total_fitness(0),
	generation(0),
	fittest_genome(0),
	best_fitness(0),
	worst_fitness(99999999),
	average_fitness(0)
{
	// Initialize the population with chromosomes consisting of random weights and all fitnesses
	// set to zero.
	for (int i = 0; i < population_size; ++i)
	{
		population.push_back(Genome());

		for (int j = 0; j < chromosome_length; ++j)
		{
			population[i].weights.push_back(randomClamped());	// TODO: AGAIN, WHAT RANGE?
		}
	}
}

/*
	Mutates a chromosome by perturbing its weights by an amount not greater than
	Params::max_perturbation.
*/
void GenAlg::mutate(std::vector<double>& chromosome)
{
	// Traverse the chromosome and mutate each weight dependent on the mutation rate
	for (int i = 0; i < chromosome.size(); ++i)
	{
		// Do we perturb this weight?
		if (randFloat() < mutation_rate)
		{
			// Add or subtract a small value to the weight
			chromosome[i] += (randomClamped() * Params::max_perturbation);
		}
	}
}

/*
	Returns a chromosome based on roulette wheel sampling.
*/
Genome GenAlg::getChromosomeRoulette()
{
	// Generate a random number between 0 and total fitness count
	double slice = (double)(randFloat() * total_fitness);

	// This will be set to the chosen chromosome
	Genome chosen;

	// Go through the chromosomes adding up the fitness so far
	double fitness_so_far = 0;

	for (int i = 0; i < population_size; ++i)
	{
		fitness_so_far += population[i].fitness;

		// If the fitness so far > random number return the chromosome at this point
		if (fitness_so_far >= slice)
		{
			chosen = population[i];
			break;
		}
	}

	return chosen;
}

/*
	Given parents and storage for the offspring, this method performs crossover
	according to the genetic algorithm's crossover rate.
*/
void GenAlg::crossover(const std::vector<double>& mum,
	const std::vector<double>& dad,
	std::vector<double>& baby1,
	std::vector<double>& baby2)
{
	// Just return parents as offspring dependent on the rate or if parents are the same
	if ((randFloat() > crossover_rate) || (mum == dad))
	{
		baby1 = mum;
		baby2 = dad;

		return;
	}

	// Determine a crossover point
	int cp = randInt(0, chromosome_length - 1);

	// Create the offspring
	for (int i = 0; i < cp; ++i)
	{
		baby1.push_back(mum[i]);
		baby2.push_back(dad[i]);
	}

	// TODO: This i was not initialized in the original source
	for (int i = cp; i < mum.size(); ++i)
	{
		baby1.push_back(dad[i]);
		baby2.push_back(mum[i]);
	}
}

/*
	Takes a population of chromosomes and runs the algorithm through one cycle.
	Returns a new population of chromosomes.
*/
std::vector<Genome> GenAlg::epoch(std::vector<Genome>& old_population)
{
	// Assign the given population to the classes population
	population = old_population;

	// Reset the appropriate variables
	reset();

	// Sort the population (for scaling and elitism)
	std::sort(population.begin(), population.end());

	// Calculate best, worst, average and total fitness
	calculateBestWorstAverageTotal();

	// Create a temporary vector to store new chromosomes
	std::vector<Genome> new_population;

	// Add in some copies of the fittest genome to add elitism. Make sure that an EVEN number
	// is added or the roulette wheel sampling will crash.
	if (!(Params::num_copies_elite * Params::num_elite % 2))
	{
		grabNBest(Params::num_elite, Params::num_copies_elite, new_population);
	}

	// Enter genetic algorithm loop

	// Repeat until a new population is generated
	while (new_population.size() < population_size)
	{
		// Grab two chromosomes
		Genome mum = getChromosomeRoulette();
		Genome dad = getChromosomeRoulette();

		// Create some offspring via crossover
		std::vector<double> baby1, baby2;

		crossover(mum.weights, dad.weights, baby1, baby2);

		// Now mutate
		mutate(baby1);
		mutate(baby2);

		// Now copy into new population
		new_population.push_back(Genome(baby1, 0));
		new_population.push_back(Genome(baby2, 0));
	}

	// Finished so assign new population back into original population
	population = new_population;

	return population;
}

/*
	Works like an advanced form of elitism by inserting num_copies copies of the N best most
	fittest genomes into a population vector.
*/
void GenAlg::grabNBest(int n_best, const int num_copies, std::vector<Genome>& pop)
{
	// Add the required amount of copies of the N most fittest to the supplied vector
	while (n_best--)
	{
		for (int i = 0; i < num_copies; ++i)
		{
			pop.push_back(population[(population_size - 1) - n_best]);
		}
	}
}

/*
	Calculates the fittest and weakest genome and the average/total fitness scores.
*/
void GenAlg::calculateBestWorstAverageTotal()
{
	total_fitness = 0;

	double highest_so_far = 0;
	double lowest_so_far = 9999999;

	for (int i = 0; i < population_size; ++i)
	{
		// Update fittest if necessary
		if (population[i].fitness > highest_so_far)
		{
			highest_so_far = population[i].fitness;

			fittest_genome = i;

			best_fitness = highest_so_far;
		}

		// Update worst if necessary
		if (population[i].fitness < lowest_so_far)
		{
			lowest_so_far = population[i].fitness;

			worst_fitness = lowest_so_far;
		}

		total_fitness += population[i].fitness;
	}

	average_fitness = total_fitness / population_size;
}

/*
	Resets all the relevant variables ready for a new generation.
*/
void GenAlg::reset()
{
	total_fitness = 0;
	best_fitness = 0;
	worst_fitness = 9999999;
	average_fitness = 0;
}