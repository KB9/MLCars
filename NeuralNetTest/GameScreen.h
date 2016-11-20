#pragma once

#include "Screen.h"

#include "Car.h"
#include "Track.h"
#include "FontTexture.h"
#include "Timer.h"

#include "SDL_ttf.h"

#include "GenAlg.h"
#include "Genome.h"

#include <string>
#include <memory>

constexpr int POPULATION_SIZE = 10;
//constexpr int NUM_WEIGHTS = 2;

class GameScreen : public virtual Screen
{
public:
	GameScreen(SDL_Renderer** renderer);

	void handleKeys(unsigned char key, int x, int y) override;
	void update() override;
	void render(SDL_Renderer* renderer) override;

private:
	// FPS display
	FontTexture fps_text;

	// Genetic algorithm and simulation
	GenAlg algorithm;
	int generation;
	int generation_iteration;
	FontTexture distance_text;
	FontTexture fittest_text;
	FontTexture generation_text;
	FontTexture generation_iteration_text;
	FontTexture track_segment_count;
	std::vector<Genome> population;

	std::vector<Car> cars;

	// Renderables
	Car* active_car = nullptr;
	Track track;

	Timer iteration_timer;

	void nextGenIteration();
	void nextGen();
	bool loadMedia();
	void printStats();
};