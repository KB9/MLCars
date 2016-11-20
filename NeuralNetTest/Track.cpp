#include "Track.h"

Track::Track()
{
	float two_pi = 2.0f * 3.141562654f;
	float track_center_x = 320;
	float track_center_y = 240;
	float track_outer_radius = 200;
	float track_inner_radius = 125;
	float build_step = (two_pi / 360);

	for (float i = build_step; i < two_pi; i += build_step)
	{
		float last_outer_x = track_center_x + (sin(i - build_step) * track_outer_radius);
		float last_outer_y = track_center_y - (cos(i - build_step) * track_outer_radius);
		float last_inner_x = track_center_x + (sin(i - build_step) * track_inner_radius);
		float last_inner_y = track_center_y - (cos(i - build_step) * track_inner_radius);

		float outer_x = track_center_x + (sin(i) * track_outer_radius);
		float outer_y = track_center_y - (cos(i) * track_outer_radius);
		float inner_x = track_center_x + (sin(i) * track_inner_radius);
		float inner_y = track_center_y - (cos(i) * track_inner_radius);

		track_quads.push_back(TrackQuad(last_outer_x, last_outer_y, last_inner_x, last_inner_y, inner_x, inner_y, outer_x, outer_y));
	}

	TrackQuad first = track_quads.at(0);
	TrackQuad last = track_quads.at(track_quads.size() - 1);
	track_quads.push_back(TrackQuad(last.x4, last.y4, last.x3, last.y3, first.x2, first.y2, first.x1, first.y1));
}

bool Track::isPointOnTrack(float x, float y)
{
	for (TrackQuad quad : track_quads)
	{
		if (quad.isPointInside(x, y))
		{
			return true;
		}
	}

	return false;
}

int Track::getTrackQuadIndex(float x, float y)
{
	for (int i = 0; i < track_quads.size(); i++)
	{
		if (track_quads.at(i).isPointInside(x, y))
		{
			return i;
		}
	}

	return -1;
}

int Track::getTrackQuadCount()
{
	return track_quads.size();
}

void Track::draw(SDL_Renderer* renderer)
{
	for (TrackQuad quad : track_quads)
	{
		quad.draw(renderer);
	}
}