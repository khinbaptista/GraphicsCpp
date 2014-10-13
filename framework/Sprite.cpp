#include "Sprite.h"
#include <iostream>

using namespace std;
using namespace glm;

Sprite::Sprite(SDL_Renderer *renderer, string filepath)
{
	SDL_Surface *surface = SDL_LoadBMP(filepath.c_str());
	if (surface == nullptr){
		cout << "Error loading BMP file: " << SDL_GetError() << endl;
		return;
	}
	
	sprite = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (sprite == nullptr){
		cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
		return;
	}

	source = NULL;
	destination = NULL;
}

Sprite::Sprite(SDL_Renderer *renderer, string filepath, SDL_Rect *source, SDL_Rect *destination){
	SDL_Surface *surface = SDL_LoadBMP(filepath.c_str());
	if (surface == nullptr){
		cout << "Error loading BMP file: " << SDL_GetError() << endl;
		return;
	}

	sprite = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (sprite == nullptr){
		cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
		return;
	}

	this->source = source;
	this->destination = destination;
}

Sprite::~Sprite(){
	
}


vec2 Sprite::Position(void){
	if (destination == NULL)
		return vec2(0.0f, 0.0f);
	else
		return vec2(destination->x, destination->y);
}

void Sprite::Position(vec2 position){
	if (destination == NULL){
		cout << "This sprite has a NULL destination";
		return;
	}

	destination->x = position.x;
	destination->y = position.y;
}


SDL_Rect Sprite::SourceRectangle(void){
	return *source;
}

void Sprite::SourceRectangle(SDL_Rect *source){
	this->source = source;
}


SDL_Rect Sprite::DestinationRectangle(void){
	return *destination;
}

void Sprite::DestinationRectangle(SDL_Rect *destination){
	this->destination = destination;
}


void Sprite::Draw(void){
	SDL_RenderCopy(renderer, sprite, source, destination);

	SDL_RenderPresent(renderer);
}