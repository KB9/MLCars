#include "Car.h"

#include <math.h>

Car::Car(double width, double height)
{
	this->x = 0;
	this->y = 0;
	this->distance_travelled = 0;
	this->width = width;
	this->height = height;
	this->fitness = 0;
}

void Car::setXY(double x, double y)
{
	this->x = x;
	this->y = y;
}

void Car::notifyDistanceTravelled(double distance)
{
	// If the car is travelling backwards
	if (distance < distance_travelled || 
		(distance - distance_travelled) > 100)	// HACK: Need to implement loop-around direction checking properly...
	{
		is_moving_in_correct_dir = false;
	}
	else
	{
		// TODO: Should this be the other way around?
		//distance = distance_travelled;
		// FIX:
		distance_travelled = distance;
	}
}

bool Car::isMovingInCorrectDir()
{
	return is_moving_in_correct_dir;
}

void Car::putWeights(std::vector<double> weights)	// GA step 3.A.i
{
	brain.putWeights(weights);

	this->weights = weights;

	speed = 1 + std::abs(weights.at(0));
	//rotation = std::abs(weights.at(1)) * (3.141592654f * 2.0f);

	// Rotation could be based on weights.at(distance_travelled) with the number of output nodes
	// equal to the number of segments on the track.
	int rotation_weight_index = (int)distance_travelled;
	rotation = std::abs(weights.at(rotation_weight_index) * (3.141592654f * 2.0f));
}

void Car::update()
{
	if (weights.size() == 0) return;

	int rotation_weight_index = (int)distance_travelled;
	rotation = std::abs(weights.at(rotation_weight_index) * (3.141592654f * 2.0f));

	x += sin(rotation) * speed;
	y -= cos(rotation) * speed;
}

void Car::draw(SDL_Renderer* renderer)
{
	SDL_Rect car_body =
	{
		x, y,
		width, height
	};
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(renderer, &car_body);
}

void Car::reset()
{
	is_moving_in_correct_dir = true;
	distance_travelled = 0;
	x = 0;
	y = 0;
	speed = 0;
	rotation = 0;
}