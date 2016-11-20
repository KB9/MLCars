#pragma once

#include <SDL.h>

class TrackQuad
{
private:
	float x_points[4];
	float y_points[4];

public:
	float x1, y1, x2, y2, x3, y3, x4, y4;

	TrackQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

	//  The function will return true if the point (x,y) is inside the polygon, or
	//  false if it is not.  If the point is exactly on the edge of the polygon,
	//  then the function may return true or false.
	//
	//  int    polygon_corners  =  how many corners the polygon has
	//  float  poly_x[]			=  horizontal coordinates of corners
	//  float  poly_y[]			=  vertical coordinates of corners
	//  float  x, y				=  point to be tested
	//
	//  Note that division by zero is avoided because the division is protected
	//  by the "if" clause which surrounds it.
	bool isPointInside(float x, float y);

	void draw(SDL_Renderer* renderer);
};