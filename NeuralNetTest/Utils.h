#pragma once

#include <cstdlib>

using namespace std;

//returns a random integer between x and y
inline int randInt(int x, int y)
{
	return rand() % (y - x + 1) + x;
}

//returns a random float between zero and 1
inline double randFloat()
{
	return (rand()) / (RAND_MAX + 1.0);
}

//returns a random float in the range -1 < n < 1
inline double randomClamped()
{
	return randFloat() - randFloat();
}