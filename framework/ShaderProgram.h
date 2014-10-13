#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#define NAMEOF_MODELMATRIX "model_matrix"
#define NAMEOF_VIEWMATRIX "view_matrix"
#define NAMEOF_PROJECTIONMATRIX "projection_matrix"
#define NAMEOF_VERTEXPOSITION "vertex_position"
#define NAMEOF_VERTEXCOLOR "vertex_color"
#define NAMEOF_VERTEXNORMAL "vertex_normal"
#define NAMEOF_VERTEXTEXTUREUV "vertex_textureUV"
#define NAMEOF_TEXTURE "texture_sampler"
#define NAMEOF_ALPHA "alpha"

#define ARRAYINDEX_VERTEXPOSITION 0
#define ARRAYINDEX_VERTEXCOLOR 1
#define ARRAYINDEX_VERTEXNORMAL 2
#define ARRAYINDEX_VERTEXTEXTUREUV 3

using namespace glm;
using namespace std;

class ShaderProgram
{
private:
	GLuint id;
	GLint vertexShaderID;
	GLint fragmentShaderID;

	vector<GLint> locations;
	vector<string> names;

public:
	// Creates a new shader program
	ShaderProgram(void);

	~ShaderProgram(void);

	// Creates a new shader in this program
	bool CreateShader(GLenum shaderType, const char *sourceCode);
	
	// Links the program to OpenGL
	bool Link(void);

	// Activates this program
	void Activate(void);

	// Deactivates this program
	void Deactivate(void);
	
	// Retrieves the location of a uniform variable inside the shaders
	GLint GetVariableLocation(string name);

	// Sets a uniform variable inside the shader
	void SetVariable(string name, GLfloat x);

	// Sets a uniform variable inside the shader
	void SetVariable(string name, GLfloat x, GLfloat y);

	// Sets a uniform variable inside the shader
	void SetVariable(string name, GLfloat x, GLfloat y, GLfloat z);

	// Sets a uniform variable inside the shader
	void SetVariable(string name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	// Sets a uniform variable inside the shader
	void SetVariable(string name, vec2 vector);

	// Sets a uniform variable inside the shader
	void SetVariable(string name, vec3 vector);

	// Sets a uniform variable inside the shader
	void SetVariable(string name, vec4 vector);

	// Sets a uniform variable inside the shader
	void SetVariable(string name, mat4 matrix);
};

