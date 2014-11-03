#include <iostream>
#include <vector>
#include <algorithm>
#include <GL/glew.h>
#include <SDL.h>
#include <random>
#include "main.h"
#include "ShaderProgram.h"
#include "glm\gtx\transform.hpp"
#include "glm\gtc\matrix_transform.hpp"

void createTriangleBuffer();

GLuint positionBufferObject;
#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))
#define GREEN_COLOR 0.75f, 0.75f, 1.0f, 1.0f
#define BLUE_COLOR 	0.0f, 0.5f, 0.0f, 1.0f
#define RED_COLOR 1.0f, 0.0f, 0.0f, 1.0f

GLuint vertexBufferObject;
GLuint indexBufferObject;
GLuint vao;
GLuint vaoObject1;
ShaderProgram *shaderProgram;

vec2 actualOffset(0.0f, 0.0f);
vec2 addOffset(0.00005f, 0.0f);


vec3 position(0.0f, 0.0f, 0.0f);
float mscale = 1.0f;
float angleX = 0.0f;
float angleY = 0.0f;
float angleZ = 0.0f;

mat4 rotationMatrix(){ return glm::rotate(angleX, vec3(1, 0, 0)) * glm::rotate(angleY, vec3(0, 1, 0)) * glm::rotate(angleZ, vec3(0, 0, 1)); }

#define TRIANGLES_NUMBERS 10000

float vertexPositions[TRIANGLES_NUMBERS * 3 * 4 * 2];
GLshort indexData[TRIANGLES_NUMBERS * 3];// = { 0 }; // WHY I had to initialize it with one not zero?
/*GLshort indexData[] =
{
	0, 1, 2,

};*/


float ticks = 0;

#define sqrt3over3 0.57735026918962576450914878050196f
#define sqrt3over6 0.28867513459481288225457439025098f

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

glm::mat4 ConstructMatrix(float fElapsedTime)
{
	//const glm::mat3 &rotMatrix = RotateZ(fElapsedTime);
	float degree = ComputeAngleRad(fElapsedTime, 5.0) * 180.0f / 3.1415926f;
	const glm::mat4 rotMatrix = glm::rotate(degree, 0.0f, 0.0f, 1.0f);
	

	return rotMatrix;
}

void genereateRandomTrianglePositions(int count){	
	std::random_device generator;
	std::uniform_real_distribution<double> distribution(-1.0f, 1.0f);
	double newX = distribution(generator);
	double newY = distribution(generator);
	double side = 0.02f;

	vertexPositions[count * 4 * 3 + 0] = newX;
	vertexPositions[count * 4 * 3 + 1] = newY + sqrt3over3 * side;
	vertexPositions[count * 4 * 3 + 2] = 0.0f;
	vertexPositions[count * 4 * 3 + 3] = 1.0f;

	vertexPositions[count * 4 * 3 + 4] = newX - side / 2;
	vertexPositions[count * 4 * 3 + 5] = newY - sqrt3over6 * side;
	vertexPositions[count * 4 * 3 + 6] = 0.0f;
	vertexPositions[count * 4 * 3 + 7] = 1.0f;

	vertexPositions[count * 4 * 3 + 8] = newX + side / 2;
	vertexPositions[count * 4 * 3 + 9] = newY - sqrt3over6 * side;
	vertexPositions[count * 4 * 3 + 10] = 0.0f;
	vertexPositions[count * 4 * 3 + 11] = 1.0f;
}

void genereateRandomTriangleColors(int count){
	std::random_device generator;
	std::uniform_real_distribution<double> distributionColor(0.0f, 1.0f);
	vertexPositions[TRIANGLES_NUMBERS * 3 * 4 + count * 4 * 3 + 0] = distributionColor(generator);
	vertexPositions[TRIANGLES_NUMBERS * 3 * 4 + count * 4 * 3 + 1] = distributionColor(generator);
	vertexPositions[TRIANGLES_NUMBERS * 3 * 4 + count * 4 * 3 + 2] = distributionColor(generator);
	vertexPositions[TRIANGLES_NUMBERS * 3 * 4 + count * 4 * 3 + 3] = 1.0f;

	vertexPositions[TRIANGLES_NUMBERS * 3 * 4 + count * 4 * 3 + 0] = distributionColor(generator);
	vertexPositions[TRIANGLES_NUMBERS * 3 * 4 + count * 4 * 3 + 1] = distributionColor(generator);
	vertexPositions[TRIANGLES_NUMBERS * 3 * 4 + count * 4 * 3 + 2] = distributionColor(generator);
	vertexPositions[TRIANGLES_NUMBERS * 3 * 4 + count * 4 * 3 + 3] = 1.0f;

	vertexPositions[TRIANGLES_NUMBERS * 3 * 4 + count * 4 * 3 + 0] = distributionColor(generator);
	vertexPositions[TRIANGLES_NUMBERS * 3 * 4 + count * 4 * 3 + 1] = distributionColor(generator);
	vertexPositions[TRIANGLES_NUMBERS * 3 * 4 + count * 4 * 3 + 2] = distributionColor(generator);
	vertexPositions[TRIANGLES_NUMBERS * 3 * 4 + count * 4 * 3 + 3] = 1.0f;
}

bool timeChanged = false;
int timesChanged = 0;

void render(){
	glClear(GL_COLOR_BUFFER_BIT);

	
	ticks = SDL_GetTicks() - timesChanged*2000;

	if (ticks > 2000){
		createTriangleBuffer();
		timesChanged++;
	}


	//shaderProgram->SetVariable("elapsedTime", SDL_GetTicks());
	//shaderProgram->Activate(); // set variable deactivates..
	//glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject); //bind positionBufferObject

	//glEnableVertexAttribArray(0); //this 0 corresponds to the location = 0 in the GLSL for the vertex shader.
	//more generically, use glGetAttribLocation() after GLSL linking to obtain the assigned attribute location.

	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0); //define **how** values are reader from positionBufferObject in Attrib 0

	//mat4 rotation = ConstructMatrix(SDL_GetTicks()/1000.0f);
	//mat4 rotation = ConstructMatrix(1);

	//shaderProgram->SetVariable("loopDuration", 5.0f);
	//shaderProgram->SetVariable("rotation", rotation);
	mscale = (SDL_GetTicks() % 1000);
	mscale /= 1000;


	shaderProgram->SetVariable("modelMatrix", ModelMatrix());
	shaderProgram->Activate();
	//glDrawArrays(GL_TRIANGLES, 0, 3); //Draw something, using Triangles, and 3 vertices - i.e. one lonely triangle
	//glDrawElements(GL_TRIANGLES, 4, GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(vaoObject1);
	//ARRAY_COUNT(indexData)
	glDrawElements(GL_TRIANGLES, ARRAY_COUNT(indexData), GL_UNSIGNED_SHORT, 0);

	//shaderProgram->SetVariable("loopDuration", 2.5f);
	//shaderProgram->Activate();
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	//glDisableVertexAttribArray(0); //cleanup

	glBindVertexArray(0);
	shaderProgram->Deactivate();
}

void createTriangleBuffer(){
	for (int i = 0; i < TRIANGLES_NUMBERS; i++)
		genereateRandomTrianglePositions(i);
	for (int i = 0; i < TRIANGLES_NUMBERS; i++)
		genereateRandomTriangleColors(i);


	glGenBuffers(1, &vertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexBufferObject);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	glGenVertexArrays(1, &vaoObject1);
	glBindVertexArray(vaoObject1);

	int numberOfVertices = TRIANGLES_NUMBERS * 3;

	size_t colorDataOffset = sizeof(float) * 4 * numberOfVertices;

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorDataOffset);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);

	glBindVertexArray(0);
}


void initialize()
{
	shaderProgram = new ShaderProgram();
	shaderProgram->CreateShader("vertexShader.vsh", GL_VERTEX_SHADER);
	shaderProgram->CreateShader("fragmentShader.fsh", GL_FRAGMENT_SHADER);

	shaderProgram->Link();


	//shaderProgram->SetVariable("loopDuration", 5.0f); //only sets loop duration once
	//shaderProgram->SetVariable("fragLoopDuration", 5.0f); //only sets loop duration once


	/*glGenBuffers(1, &positionBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);*/

	//start indexes>
	for (int i = 0; i < TRIANGLES_NUMBERS * 3; i++)
		indexData[i] = i;

	

	createTriangleBuffer();

	//****
	


	glGenVertexArrays(1, &vao); //create a Vertex Array Object
	glBindVertexArray(vao); //make the VAO active

	

	
}