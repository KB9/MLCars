#pragma once

#include <SDL.h>
#include <string>

#include "SDL_ttf.h"

class Texture
{
public:
	Texture(SDL_Renderer** renderer);
	~Texture();

	bool loadFromFile(std::string path);

	void free();

	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	void setBlendMode(SDL_BlendMode blending);

	void setAlpha(Uint8 alpha);

	void render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int getWidth();
	int getHeight();

protected:
	SDL_Texture* texture;

	SDL_Renderer** renderer;

	int width;
	int height;
};