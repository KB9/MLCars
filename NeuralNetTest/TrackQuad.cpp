#include "TrackQuad.h"

TrackQuad::TrackQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) :
	x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3), x4(x4), y4(y4)
{
	x_points[0] = x1;
	x_points[1] = x2;
	x_points[2] = x3;
	x_points[3] = x4;

	y_points[0] = y1;
	y_points[1] = y2;
	y_points[2] = y3;
	y_points[3] = y4;
}

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
bool TrackQuad::isPointInside(float x, float y)
{
	// TODO: Get rid of these. Just to make it more portable for now.
	int polygon_corners = 4;
	float* poly_x = x_points;
	float* poly_y = y_points;

	int i, j = polygon_corners - 1;
	bool odd_nodes = false;

	for (i = 0; i < polygon_corners; i++)
	{
		if ((poly_y[i] < y && poly_y[j] >= y
			|| poly_y[j] < y && poly_y[i] >= y)
			&& (poly_x[i] <= x || poly_x[j] <= x))
		{
			odd_nodes ^= (poly_x[i] + (y - poly_y[i]) / (poly_y[j] - poly_y[i]) * (poly_x[j] - poly_x[i]) < x);
		}
		j = i;
	}

	return odd_nodes;
}

void TrackQuad::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
	SDL_RenderDrawLine(renderer, x3, y3, x4, y4);
	SDL_RenderDrawLine(renderer, x4, y4, x1, y1);
}