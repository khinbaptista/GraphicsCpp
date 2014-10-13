#include <iostream>
#include <vector>
#include <algorithm>
#include <GL/glew.h>
#include <SDL.h>
#include "main.h"
#include "ShaderProgram.h"

GLuint positionBufferObject;
GLuint vao;
ShaderProgram *shaderProgram;

vec2 actualOffset(0.0f, 0.0f);
vec2 addOffset(0.00005f, 0.0f);

const float vertexPositions[] = {
	0.0f, 0.5f, 0.0f, 1.0f,
	-0.4330127f, -0.25f, 0.0f, 1.0f,
	0.4330127f, -0.25f, 0.0f, 1.0f,
};

const std::string strVertexShader(
	"#version 330\n"
	"layout(location = 0) in vec4 position;\n"
	"uniform vec2 offset;\n"
	"void main()\n"
	"{\n"
	"	vec4 vecOffset = vec4(offset.x,offset.y,0.0f,0.0f);\n"
	"   gl_Position = position + vecOffset;\n"
	"}\n"
	);
//vec4(1.0f, 0.0f, 0.0f, 0.0f);

//string holding the **source** of our fragment shader, to save loading from a file
const std::string strFragmentShader(
	"#version 330\n"
	"out vec4 outputColor;\n"
	"void main()\n"
	"{\n"
	"   outputColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
	"}\n"
	);

vec2 ComputePositionOffsets()
{
	const float fLoopDuration = 5.0f;
	const float fScale = 3.14159f * 2.0f / fLoopDuration;

	float fElapsedTime = SDL_GetTicks() / 1000.0f;

	float fCurrTimeThroughLoop = fmodf(fElapsedTime, fLoopDuration);

	return vec2(cosf(fCurrTimeThroughLoop * fScale) * 0.5f, sinf(fCurrTimeThroughLoop * fScale) * 0.5f);
}

void render(){
	glClear(GL_COLOR_BUFFER_BIT);


	
	actualOffset += addOffset;
	shaderProgram->SetVariable("offset", ComputePositionOffsets());
	shaderProgram->Activate(); // set variable deactivates..
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject); //bind positionBufferObject

	glEnableVertexAttribArray(0); //this 0 corresponds to the location = 0 in the GLSL for the vertex shader.
	//more generically, use glGetAttribLocation() after GLSL linking to obtain the assigned attribute location.

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0); //define **how** values are reader from positionBufferObject in Attrib 0

	glDrawArrays(GL_TRIANGLES, 0, 3); //Draw something, using Triangles, and 3 vertices - i.e. one lonely triangle

	glDisableVertexAttribArray(0); //cleanup


	shaderProgram->Deactivate();
}


void initialize()
{
	shaderProgram = new ShaderProgram();
	shaderProgram->CreateShader("vertexShader.vsh", GL_VERTEX_SHADER );
	shaderProgram->CreateShader(GL_FRAGMENT_SHADER, strFragmentShader.c_str());

	shaderProgram->Link();




	glGenBuffers(1, &positionBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vao); //create a Vertex Array Object
	glBindVertexArray(vao); //make the VAO active

	
}