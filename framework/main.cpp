#include <iostream>
#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <SDL.h>
#include "main.h"

//using namespace std;

/////////////////////
// global variables 

SDL_Window *win; //pointer to the SDL_Window
SDL_GLContext context; //the SDL_GLContext

// end Global Variables
/////////////////////////


void initialiseSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		exit(1);
	}
	std::cout << "SDL initialised OK!\n";
}

void createWindow()
{
	win = SDL_CreateWindow("Hello World!", 100, 100, 600, 600, SDL_WINDOW_OPENGL); //same height and width makes the window square ...
	if (win == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}
	std::cout << "SDL CreatedWindow OK!\n";
}

void setGLAttributes()
{
	// set the opengl context version
	int major = 3;
	int minor = 3;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); //core profile
	std::cout << "Set OpenGL context to version " << major << "." << minor << " OK!\n";
}

void createContext()
{
	context = SDL_GL_CreateContext(win);
	if (context == nullptr){
		SDL_DestroyWindow(win);
		std::cout << "SDL_GL_CreateContext Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}
	std::cout << "Created OpenGL context OK!\n";
}

void initGlew()
{
	GLenum rev;
	glewExperimental = GL_TRUE; //GLEW isn't perfect - see https://www.opengl.org/wiki/OpenGL_Loading_Library#GLEW
	rev = glewInit();
	if (GLEW_OK != rev){
		std::cout << "GLEW Error: " << glewGetErrorString(rev) << std::endl;
		SDL_Quit();
		exit(1);
	}
	else {
		std::cout << "GLEW Init OK!\n";
	}
}

namespace Framework{
	GLuint createShader(GLenum eShaderType, const std::string &strShaderFile)
	{
		GLuint shader = glCreateShader(eShaderType);
		const char *strFileData = strShaderFile.c_str();
		glShaderSource(shader, 1, &strFileData, NULL);

		glCompileShader(shader);

		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

			const char *strShaderType = NULL;
			switch (eShaderType)
			{
			case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
			case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
			case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
			}

			fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
			delete[] strInfoLog;
		}

		return shader;
	}

	GLuint createProgram(const std::vector<GLuint> &shaderList)
	{
		GLuint program = glCreateProgram();

		for (size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
			glAttachShader(program, shaderList[iLoop]);

		glLinkProgram(program);

		GLint status;
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint infoLogLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
			fprintf(stderr, "Linker failure: %s\n", strInfoLog);
			delete[] strInfoLog;
		}

		for (size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
			glDetachShader(program, shaderList[iLoop]);

		return program;
	}
}

void cleanUp()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);
	std::cout << "Cleaning up OK!\n";
}

int main( int argc, char* args[] )
{

	//setup
	//- do just once
	initialiseSDL();
	createWindow();
	setGLAttributes();
	createContext();
	initGlew();

	initialize(); 
	
	while (true){

		//GET INPUT HERE - PLACEHOLDER

		//UPDATE SIMULATION - PLACEHOLDER

		render(); //RENDER HERE - PLACEHOLDER

		SDL_GL_SwapWindow(win);; //present the frame buffer to the display (swapBuffers)

	}

	//TODO cleanup and exit
	cleanUp();
	SDL_Quit();

	return 0;
}