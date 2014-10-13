#pragma comment(lib, "glew32.lib")

#include "ShaderProgram.h"
#include <iostream>

using namespace std;

ShaderProgram::ShaderProgram(void){
	id = glCreateProgram();
	vertexShaderID = -1;
	fragmentShaderID = -1;
}

ShaderProgram::~ShaderProgram(void){
	glDeleteProgram(id);
}

bool ShaderProgram::CreateShader(GLenum shaderType, const char *sourceCode){
	GLint statusCode = -1;
	GLint infoLogLength;
	char *info = "";

	int shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &sourceCode, NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &statusCode);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	glGetShaderInfoLog(shaderID, infoLogLength, NULL, info);

	if (statusCode != 1)
	{
		glDeleteShader(shaderID);
		cout << "Error creating shader (status code: " << statusCode << ")\n" << info;
		return false;
	}

	if (shaderType == GL_VERTEX_SHADER)
		vertexShaderID = shaderID;
	else if (shaderType == GL_FRAGMENT_SHADER)
		fragmentShaderID = shaderID;

	return true;
}

bool ShaderProgram::Link(void){
	GLint statusCode = -1;
	GLint infoLogLength;
	char *info = "";

	if (vertexShaderID != -1)
		glAttachShader(id, vertexShaderID);
	
	if (fragmentShaderID != -1)
		glAttachShader(id, fragmentShaderID);

	glBindAttribLocation(id, ARRAYINDEX_VERTEXPOSITION, NAMEOF_VERTEXPOSITION);
	glBindAttribLocation(id, ARRAYINDEX_VERTEXCOLOR, NAMEOF_VERTEXCOLOR);
	glBindAttribLocation(id, ARRAYINDEX_VERTEXNORMAL, NAMEOF_VERTEXNORMAL);
	glBindAttribLocation(id, ARRAYINDEX_VERTEXTEXTUREUV, NAMEOF_VERTEXTEXTUREUV);

	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &statusCode);
	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
	glGetProgramInfoLog(id, infoLogLength, NULL, info);

	if (statusCode != 1)
	{
		glDeleteProgram(id);
		cout << "Error linking program (status code: " << statusCode << ")\n" << info;
		return false;
	}

	if (vertexShaderID != -1)
	{
		glDetachShader(id, vertexShaderID);
		glDeleteShader(vertexShaderID);
		vertexShaderID = -1;
	}

	if (fragmentShaderID != -1)
	{
		glDetachShader(id, fragmentShaderID);
		glDeleteShader(fragmentShaderID);
		fragmentShaderID = -1;
	}

	return true;
}

void ShaderProgram::Activate(void){
	glUseProgram(id);
}

void ShaderProgram::Deactivate(void){
	glUseProgram(0);
}

GLint ShaderProgram::GetVariableLocation(string name){
	GLint location;
	bool found = false;
	uint i = 0;

	while(i < names.size() && !found)
	{
		if (names[i].compare(name) == 0)
		{
			found = true;
			location = locations[i];
		}

		i++;
	}

	if (found)
		return location;

	location = glGetUniformLocation(id, name.c_str());

	if (location == -1)
		cout << "Failed to retrieve location of uniform variable " << name;
	else
	{
		names.push_back(name);
		locations.push_back(location);
	}

	return location;
}

void ShaderProgram::SetVariable(string name, GLfloat x){
	glUseProgram(id);

	GLint location = GetVariableLocation(name);

	if (location != -1)
		glUniform1f(location, x);

	glUseProgram(0);
}

void ShaderProgram::SetVariable(string name, GLfloat x, GLfloat y){
	glUseProgram(id);

	GLint location = GetVariableLocation(name);

	if (location != -1)
		glUniform2f(location, x, y);

	glUseProgram(0);
}

void ShaderProgram::SetVariable(string name, GLfloat x, GLfloat y, GLfloat z){
	glUseProgram(id);

	GLint location = GetVariableLocation(name);

	if (location != -1)
		glUniform3f(location, x, y, z);

	glUseProgram(0);
}

void ShaderProgram::SetVariable(string name, GLfloat x, GLfloat y, GLfloat z, GLfloat w){
	glUseProgram(id);

	GLint location = GetVariableLocation(name);

	if (location != -1)
		glUniform4f(location, x, y, z, w);

	glUseProgram(0);
}

void ShaderProgram::SetVariable(string name, vec2 vector){
	SetVariable(name, vector.x, vector.y);
}

void ShaderProgram::SetVariable(string name, vec3 vector){
	SetVariable(name, vector.x, vector.y, vector.z);
}

void ShaderProgram::SetVariable(string name, vec4 vector){
	SetVariable(name, vector.x, vector.y, vector.z, vector.w);
}

void ShaderProgram::SetVariable(string name, mat4 matrix){
	glUseProgram(id);

	GLint location = GetVariableLocation(name);

	if (location != -1)
		glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);

	glUseProgram(0);
}
