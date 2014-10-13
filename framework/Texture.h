#pragma once

#include <GL/glew.h>
#include <SDL.h>
#include <string>

using namespace std;

class Texture
{
private:
	GLuint textureID;
	GLint width;
	GLint height;

public:
	Texture(SDL_Renderer *renderer, const SDL_Rect *rectangle,
		string filepath,
		GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR,
		GLint wrapModeS = GL_CLAMP_TO_BORDER,
		GLint wrapModeT = GL_CLAMP_TO_BORDER);
	~Texture();

	// Gets the texture id for this texture
	GLuint ID();

	GLint Width();
	GLint Height();
};

