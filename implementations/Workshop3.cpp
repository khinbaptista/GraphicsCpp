#include <iostream>
#include <vector>
#include <algorithm>
#include <GL/glew.h>
#include <SDL.h>
#include "main.h"
#include "ShaderProgram.h"
#include "glm\gtx\transform.hpp"
#include "glm\gtc\matrix_transform.hpp"

GLuint positionBufferObject;
GLuint vao;
ShaderProgram *shaderProgram;

vec2 actualOffset(0.0f, 0.0f);
vec2 addOffset(0.00005f, 0.0f);


vec3 position(0.5f, 0.0f, 0.0f);
float mscale = 0.5f;
float angleX = 0.0f;
float angleY = 0.0f;
float angleZ = 180.0f;

mat4 rotationMatrix(){ return glm::rotate(angleX, vec3(1, 0, 0)) * glm::rotate(angleY, vec3(0, 1, 0)) * glm::rotate(angleZ, vec3(0, 0, 1)); }


const float vertexPositions[] = {
	0.0f, 0.5f, 0.0f, 1.0f,
	-0.4330127f, -0.25f, 0.0f, 1.0f,
	0.4330127f, -0.25f, 0.0f, 1.0f,
};

mat4 ModelMatrix(void){
	return
		glm::translate(position) *
		glm::scale(vec3(mscale, mscale, mscale)) *
		rotationMatrix();
}

vec2 ComputePositionOffsets()
{
	const float fLoopDuration = 5.0f;
	const float fScale = 3.14159f * 2.0f / fLoopDuration;

	float fElapsedTime = SDL_GetTicks() / 1000.0f;

	float fCurrTimeThroughLoop = fmodf(fElapsedTime, fLoopDuration);

	return vec2(cosf(fCurrTimeThroughLoop * fScale) * 0.5f, sinf(fCurrTimeThroughLoop * fScale) * 0.5f);
}

float ComputeAngleRad(float fElapsedTime, float fLoopDuration)
{
	const float fScale = 3.14159f * 2.0f / fLoopDuration;
	float fCurrTimeThroughLoop = fmodf(fElapsedTime, fLoopDuration);
	return fCurrTimeThroughLoop * fScale;
}

/*glm::mat3 RotateZ(float fElapsedTime)
{
	float fAngRad = ComputeAngleRad(fElapsedTime, 2.0);
	float fCos = cosf(fAngRad);
	float fSin = sinf(fAngRad);

	glm::mat3 theMat(1.0f);
	theMat[0].x = fCos; theMat[1].x = -fSin;
	theMat[0].y = fSin; theMat[1].y = fCos;
	return theMat;
}*/

glm::mat4 ConstructMatrix(float fElapsedTime)
{
	//const glm::mat3 &rotMatrix = RotateZ(fElapsedTime);
	float degree = ComputeAngleRad(fElapsedTime, 5.0) * 180.0f / 3.1415926f;
	const glm::mat4 rotMatrix = glm::rotate(degree, 0.0f, 0.0f, 1.0f);
	

	return rotMatrix;
}

void render(){
	glClear(GL_COLOR_BUFFER_BIT);


	
	actualOffset += addOffset;
	shaderProgram->SetVariable("elapsedTime", SDL_GetTicks());
	shaderProgram->Activate(); // set variable deactivates..
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject); //bind positionBufferObject

	glEnableVertexAttribArray(0); //this 0 corresponds to the location = 0 in the GLSL for the vertex shader.
	//more generically, use glGetAttribLocation() after GLSL linking to obtain the assigned attribute location.

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0); //define **how** values are reader from positionBufferObject in Attrib 0

	mat4 rotation = ConstructMatrix(SDL_GetTicks()/1000.0f);
	//mat4 rotation = ConstructMatrix(1);

	shaderProgram->SetVariable("loopDuration", 5.0f);
	//shaderProgram->SetVariable("rotation", rotation);
	shaderProgram->SetVariable("modelMatrix", ModelMatrix());
	shaderProgram->Activate();
	glDrawArrays(GL_TRIANGLES, 0, 3); //Draw something, using Triangles, and 3 vertices - i.e. one lonely triangle

	shaderProgram->SetVariable("loopDuration", 2.5f);
	shaderProgram->Activate();
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0); //cleanup


	shaderProgram->Deactivate();
}


void initialize()
{
	shaderProgram = new ShaderProgram();
	shaderProgram->CreateShader("vertexShader.vsh", GL_VERTEX_SHADER );
	shaderProgram->CreateShader("fragmentShader.fsh", GL_FRAGMENT_SHADER);

	shaderProgram->Link();


	//shaderProgram->SetVariable("loopDuration", 5.0f); //only sets loop duration once
	shaderProgram->SetVariable("fragLoopDuration", 5.0f); //only sets loop duration once


	glGenBuffers(1, &positionBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vao); //create a Vertex Array Object
	glBindVertexArray(vao); //make the VAO active

	
}