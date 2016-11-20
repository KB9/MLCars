#pragma once

#include "Texture.h"

#include <vector>
#include <string>

class FontTexture : public Texture
{
public:
	using Texture::Texture;

	~FontTexture()
	{
		Texture::~Texture();

		if (font)
		{
			TTF_CloseFont(font);
		}
	}

	void setFont(std::string font_path, int font_size)
	{
		font = TTF_OpenFont(font_path.c_str(), font_size);
		if (!font)
		{
			printf("Unable to load font! SDL_ttf Error: %s\n", TTF_GetError());
		}
	}

	bool loadFromRenderedText(std::string texture_text, SDL_Color text_color)
	{
		free();

		SDL_Surface* text_surface = TTF_RenderText_Solid(font, texture_text.c_str(), text_color);
		if (!text_surface)
		{
			printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
			return false;
		}

		texture = SDL_CreateTextureFromSurface(*renderer, text_surface);
		if (!texture)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			return false;
		}

		width = text_surface->w;
		height = text_surface->h;

		SDL_FreeSurface(text_surface);

		return true;
	}

private:
	TTF_Font* font;
};