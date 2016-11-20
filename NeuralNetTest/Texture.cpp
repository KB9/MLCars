#include "Texture.h"

#include "SDL_image.h"

Texture::Texture(SDL_Renderer** renderer)
{
	this->renderer = renderer;

	texture = nullptr;
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	free();
}

bool Texture::loadFromFile(std::string path)
{
	free();

	SDL_Texture* texture = nullptr;

	SDL_Surface* loaded_surface = IMG_Load(path.c_str());
	if (!loaded_surface)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), IMG_GetError());
		return false;
	}

	SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0x00, 0x00, 0x00));

	SDL_Texture* new_texture = SDL_CreateTextureFromSurface(*renderer, loaded_surface);
	if (!new_texture)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		return false;
	}

	width = loaded_surface->w;
	height = loaded_surface->h;

	SDL_FreeSurface(loaded_surface);

	texture = new_texture;

	return true;
}

void Texture::free()
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
		width = 0;
		height = 0;
	}
}

void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect render_quad = { x, y, width, height };
	SDL_RenderCopy(*renderer, texture, nullptr, &render_quad);
}

int Texture::getWidth()
{
	return width;
}

int Texture::getHeight()
{
	return height;
}