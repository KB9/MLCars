#pragma once

#include <vector>
#include <math.h>
#include <SDL.h>

#include "TrackQuad.h"

/*
	IMPLEMENTATION DETAILS:

	Cars can be told they are going in the correct direction if they traverse
	over the track quads in ascending index order.
*/

class Track
{
private:
	std::vector<TrackQuad> track_quads;

public:
	Track();

	bool isPointOnTrack(float x, float y);

	int getTrackQuadIndex(float x, float y);
	int getTrackQuadCount();

	void draw(SDL_Renderer* renderer);
};