//#include <iostream>
//
//int main()
//{
//	NeuralNet network;
//	GenAlg algorithm(4, Params::mutation_rate, Params::crossover_rate, 10);
//
//	std::vector<Genome> population = algorithm.getChromosomes();
//
//	std::vector<int> best_fitnesses;
//
//	std::cout << "----- NEURAL NETWORK & GENETIC ALGORITHM TEST -----" << std::endl;
//
//	int generation = 0;
//	while (true)
//	{
//		int selection = randInt(0, population.size() - 1);
//		population[selection].fitness++;
//
//		std::cout << std::endl;
//		std::cout << "----- POPULATION INFO (GENERATION " << generation++ << ") -----" << std::endl;
//		std::cout << "Size: " << population.size() << std::endl;
//		std::cout << "Best: " << algorithm.getBestFitness() << std::endl;
//		std::cout << "Average: " << algorithm.getAverageFitness() << std::endl;
//		std::cout << "Weights from: [";
//		for (int f : best_fitnesses)
//		{
//			std::cout << f << ",";
//		}
//		std::cout << "]" << std::endl;
//
//		// This member of the population is more suited - increase its fitness
//		// Every entity has a neural network (a brain). Put its weights from GA into brain.
//		// Reset its fitness after applying weights (why?).
//		//population[1].fitness++;
//		network.putWeights(population[selection].weights);
//
//		best_fitnesses.push_back(selection);
//
//		population = algorithm.epoch(population);
//
//		population[selection].fitness = 0;
//		system("PAUSE");
//	}
//
//	return 0;
//}
#include <SDL.h>
#undef main

#include <stdio.h>

#include "Timer.h"

#include "Screen.h"
#include "GameScreen.h"

#include "SDL_image.h"
#include "SDL_ttf.h"

#include <memory>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int FRAMES_PER_SECOND = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / FRAMES_PER_SECOND;

// Function prototypes
bool init();
void close();

// Window and renderer
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

// Simulation loop terminator
bool quit;

std::unique_ptr<Screen> active_screen = nullptr;

int main()
{
	if (!init())
	{
		return -1;
	}

	active_screen.reset(new GameScreen(&renderer));

	// Actual FPS and FPS cap timers
	Timer fps_timer;
	Timer cap_timer;
	
	// Enable text input
	SDL_StartTextInput();

	fps_timer.start();
	int counted_frames = 0;
	while (!quit)
	{
		cap_timer.start();

		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			// User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			// Handle key press with current mouse position
			else if (e.type == SDL_TEXTINPUT)
			{
				int x = 0, y = 0;
				SDL_GetMouseState(&x, &y);
				active_screen->handleKeys(e.text.text[0], x, y);
			}
		}

		active_screen->update();
		active_screen->render(renderer);

		// Update screen
		counted_frames++;

		// Cap framerate
		int frame_ticks = cap_timer.getTicks();
		if (frame_ticks < SCREEN_TICKS_PER_FRAME)
		{
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frame_ticks);
		}
	}

	// Disable text input
	SDL_StopTextInput();

	close();

	return 0;
}

bool init()
{
	// Initialize SDL video
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialized! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	// Initialize PNG loading
	int img_flags = IMG_INIT_PNG;
	if (!(IMG_Init(img_flags) & img_flags))
	{
		printf("SDL_image could not be initialized! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	// Intialize SDL ttf
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not be initialized! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	window = SDL_CreateWindow("Neural Network & Genetic Algorithm",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);
	if (!window)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	// Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	return true;
}

void close()
{
	// Commenting this causes a crash upon exiting the application
	active_screen.reset();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = nullptr;
	renderer = nullptr;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}