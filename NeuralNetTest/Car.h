#pragma once

#include <SDL.h>

#include "NeuralNet.h"

class Car
{
public:
	std::vector<double> weights;

	NeuralNet brain;	// GA step 2
	double fitness;

	void putWeights(std::vector<double> weights);	// GA step 3.A.i

	float speed;
	float rotation;

	double distance_travelled;
	bool is_moving_in_correct_dir = true;

	double x, y;
	double width, height;

	Car(double width, double length);

	void setXY(double x, double y);

	void notifyDistanceTravelled(double distance);
	bool isMovingInCorrectDir();

	void update();
	void draw(SDL_Renderer* renderer);

	void reset();
};