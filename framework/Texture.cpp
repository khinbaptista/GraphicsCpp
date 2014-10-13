#include "Texture.h"

using namespace std;

Texture::Texture(SDL_Renderer *renderer, const SDL_Rect *rectangle, string filepath,
		GLint minFilter, GLint magFilter, GLint wrapModeS, GLint wrapModeT){

	SDL_Surface *surface = SDL_LoadBMP(filepath.c_str());
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	width = rectangle->w;
	height = rectangle->h;

	SDL_LockTexture(texture, rectangle, (void**)0, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, texture);

	SDL_UnlockTexture(texture);

	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapModeS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapModeT);

	// clean up
	glBindTexture(GL_TEXTURE_2D, 0);
}


Texture::~Texture(){
	glDeleteTextures(1, &textureID);
}

GLuint Texture::ID(){
	return textureID;
}

GLint Texture::Width(){
	return width;
}

GLint Texture::Height(){
	return height;
}