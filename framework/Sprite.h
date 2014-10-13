#pragma once

#include <SDL.h>
#include <string>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class Sprite
{
	SDL_Renderer *renderer;
	SDL_Texture *sprite;

	SDL_Rect *source;
	SDL_Rect *destination;
	
public:
	Sprite(SDL_Renderer *renderer, string filepath);
	Sprite(SDL_Renderer *renderer, string filepath, SDL_Rect *source, SDL_Rect *destination);
	~Sprite();


	// Gets the position of this sprite;
	vec2 Position(void);
	
	// Sets the position of this sprite;
	void Position(vec2 position);


	// Gets the source rectangle of this sprite
	SDL_Rect SourceRectangle(void);

	// Sets the source rectangle of this sprite
	void SourceRectangle(SDL_Rect *source);


	// Gets the destination rectangle of this sprite
	SDL_Rect DestinationRectangle(void);

	// Sets the destination rectangle of this sprite
	void DestinationRectangle(SDL_Rect *destination);


	// Renders the sprite
	void Draw(void);
};

