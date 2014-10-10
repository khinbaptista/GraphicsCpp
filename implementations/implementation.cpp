#include <iostream>
#include <vector>
#include <algorithm>
#include <GL/glew.h>
#include <SDL.h>
#include "main.h"
#include "Camera.h"

GLuint vao;

//using namespace std;

//string holding the **source** of our vertex shader, to save loading from a file
const std::string strVertexShader(
	"#version 330\n"
	"layout(location = 0) in vec4 position;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = position;\n"
	"}\n"
	);

//string holding the **source** of our fragment shader, to save loading from a file
const std::string strFragmentShader(
	"#version 330\n"
	"out vec4 outputColor;\n"
	"void main()\n"
	"{\n"
	"   outputColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
	"}\n"
	);

GLuint positionBufferObject;

const float vertexPositions[] = {
	0.0f, 0.5f, 0.0f, 1.0f,
	-0.4330127f, -0.25f, 0.0f, 1.0f,
	0.4330127f, -0.25f, 0.0f, 1.0f,
};

GLuint theProgram; //GLuint that we'll fill in to refer to the GLSL program (only have 1 at this point)

void render(){
	Camera &camera = *Camera::New2D(800, 600);

	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(theProgram); //installs the program object specified by program as part of current rendering state

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject); //bind positionBufferObject

	glEnableVertexAttribArray(0); //this 0 corresponds to the location = 0 in the GLSL for the vertex shader.
	//more generically, use glGetAttribLocation() after GLSL linking to obtain the assigned attribute location.

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0); //define **how** values are reader from positionBufferObject in Attrib 0

	glDrawArrays(GL_TRIANGLES, 0, 3); //Draw something, using Triangles, and 3 vertices - i.e. one lonely triangle

	glDisableVertexAttribArray(0); //cleanup
	glUseProgram(0); //clean up
}

void initializeVertexBuffer()
{
	glGenBuffers(1, &positionBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	std::cout << "positionBufferObject created OK! GLUint is: " << positionBufferObject << std::endl;
}


void initialize()
{
	//create GLSL Shaders, link into a GLSL program
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::createShader(GL_VERTEX_SHADER, strVertexShader));
	shaderList.push_back(Framework::createShader(GL_FRAGMENT_SHADER, strFragmentShader));

	theProgram = Framework::createProgram(shaderList);
	if (theProgram == 0)
	{
		std::cout << "GLSL program creation error." << std::endl;
		SDL_Quit();
		exit(1);
	}
	else {
		std::cout << "GLSL program creation OK! GLUint is: " << theProgram << std::endl;
	}

	//clean up shaders (we don't need them anymore as they are no in theProgram
	for_each(shaderList.begin(), shaderList.end(), glDeleteShader);








	//load stuff from files
	//- usually do just once

	initializeVertexBuffer(); //load data into a vertex buffer

	glGenVertexArrays(1, &vao); //create a Vertex Array Object
	glBindVertexArray(vao); //make the VAO active
	std::cout << "Vertex Array Object created OK! GLUint is: " << vao << std::endl;

	std::cout << "Loaded Assets OK!\n";
}