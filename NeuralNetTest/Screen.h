#pragma once

#include <SDL.h>

class Screen
{
public:
	virtual void handleKeys(unsigned char key, int x, int y) = 0;

	virtual void update() = 0;
	virtual void render(SDL_Renderer* renderer) = 0;

	virtual ~Screen() = default;
};