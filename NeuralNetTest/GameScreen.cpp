#include "GameScreen.h"

#include "Params.h"

GameScreen::GameScreen(SDL_Renderer** renderer) :
	algorithm(POPULATION_SIZE, Params::mutation_rate, Params::crossover_rate, /*NUM_WEIGHTS*/361), // Horrible hard code of track quad count + speed node
	fps_text(renderer),
	distance_text(renderer),
	fittest_text(renderer),
	generation_text(renderer),
	generation_iteration_text(renderer),
	track_segment_count(renderer)
{
	loadMedia();

	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		cars.push_back(Car(20, 20));
	}

	population = algorithm.getChromosomes();	// GA step 1

	active_car = &cars.at(0);
}

void GameScreen::handleKeys(unsigned char key, int x, int y)
{
	if (key == 'p')
	{
		active_car->x = x;
		active_car->y = y;
		printf("Car on track: %s\n", track.isPointOnTrack(active_car->x, active_car->y) ? "YES" : "NO");
	}
}

bool is_sim_started;

void GameScreen::update()
{
	if (!is_sim_started)
	{
		active_car->setXY(320, 77.5);
		is_sim_started = true;
	}

	active_car->update();

	// Get the index of the track quad the active car is on
	int track_quad_index = track.getTrackQuadIndex(active_car->x, active_car->y);
	active_car->notifyDistanceTravelled(track_quad_index);

	// If car went off the track
	if (track_quad_index < 0 || !active_car->isMovingInCorrectDir())
	{
		// If all of the population has been simulated for the current generation
		if (generation_iteration == POPULATION_SIZE - 1)
		{
			// Print stats and move to next generation
			//printStats();		// TODO: Replace when stats aren't so exhaustive they slow down the UI loop
			nextGen();

			// Set the active car to the first member of the population
			active_car = &cars.at(0);
		}
		else
		{
			// Start the next simulation for the next member of the population
			nextGenIteration();
			is_sim_started = false;

			// Move to the next car
			active_car = &cars.at(generation_iteration);
		}
	}
	else
	{
		// Update both active car's fitness and REAL genomic fitness of population member
		// The car's fitness is irrelevant when crossing and mutating genomes.
		active_car->fitness = track_quad_index;
		population.at(generation_iteration).fitness = track_quad_index;
	}
}

void GameScreen::render(SDL_Renderer* renderer)
{
	// Clear screen
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);

	// Render track
	track.draw(renderer);

	// Update and draw active car
	active_car->update();
	active_car->draw(renderer);

	// Displaying FPS
	float average_fps = 60;//counted_frames / (fps_timer.getTicks() / 1000.0f);
	fps_text.loadFromRenderedText("FPS: " + std::to_string(average_fps).substr(0, 4), SDL_Color{ 0, 0, 0 });
	fps_text.render(0, 0);

	distance_text.loadFromRenderedText("Distance: " + std::to_string((int)active_car->fitness), SDL_Color{ 0, 0, 0 });
	distance_text.render(0, fps_text.getHeight());

	generation_text.loadFromRenderedText("Generation: " + std::to_string(generation), SDL_Color{ 0, 0, 0 });
	generation_text.render(0, fps_text.getHeight() + distance_text.getHeight());

	generation_iteration_text.loadFromRenderedText("Iteration: " + std::to_string(generation_iteration), SDL_Color{ 0, 0, 0 });
	generation_iteration_text.render(0, fps_text.getHeight() + distance_text.getHeight() + generation_text.getHeight());

	fittest_text.loadFromRenderedText("Best fitness: " + std::to_string((int)algorithm.getBestFitness()) + " (Avg: " + std::to_string((int)algorithm.getAverageFitness()) + ")", SDL_Color{ 0, 0, 0 });
	fittest_text.render(0, fps_text.getHeight() + distance_text.getHeight() + generation_text.getHeight() + generation_iteration_text.getHeight());

	track_segment_count.loadFromRenderedText("Track segments: " + std::to_string(track.getTrackQuadCount()), SDL_Color{ 0, 0, 0 });
	track_segment_count.render(0, fps_text.getHeight() + distance_text.getHeight() + generation_text.getHeight() + generation_iteration_text.getHeight() + fittest_text.getHeight());

	// Update screen
	SDL_RenderPresent(renderer);
}

void GameScreen::nextGenIteration()
{
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		cars.at(i).putWeights(population.at(i).weights);	// GA step 3.A.i
	}

	generation_iteration++;
}

void GameScreen::nextGen()
{
	population = algorithm.epoch(population);	// GA step 3.B.*

	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		cars.at(i).putWeights(population.at(i).weights);	// GA step 3.C

		// Reset the cars
		cars.at(i).reset();
	}

	generation++;
	generation_iteration = 0;
}

bool GameScreen::loadMedia()
{
	std::string font_path = "C:\\Users\\kavan\\Documents\\Visual Studio 2015\\Projects\\NeuralNetTest\\Debug\\AGENTORANGE.ttf";
	int font_size = 12;

	fps_text.setFont(font_path, font_size);
	distance_text.setFont(font_path, font_size);
	fittest_text.setFont(font_path, font_size);
	generation_text.setFont(font_path, font_size);
	generation_iteration_text.setFont(font_path, font_size);
	track_segment_count.setFont(font_path, font_size);

	return true;
}

void GameScreen::printStats()
{
	printf("####################################################\n################### GENERATION %d ###################\n####################################################\n\n", generation);
	for (int i = 0; i < population.size(); i++)
	{
		printf("=================== GENOME %d ===================\n", i);
		printf("Fitness: %f\n", population.at(i).fitness);
		printf("Weights:\n");
		for (int j = 0; j < population.at(i).weights.size(); j++)
		{
			printf("%d: %f\n", j, population.at(i).weights.at(j));
		}
		printf("\n");
	}
}