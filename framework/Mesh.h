#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include <fstream>

#include "MeshData.h"
#include "ShaderProgram.h"

using namespace glm;
using namespace std;

class Mesh
{
private:
	bool hasNormals;
	bool hasUVs;
	bool hasColor;
	bool isIndexed;

	GLint normalBuffer;
	GLint UVbuffer;
	GLint colorBuffer;
	GLint indexBuffer;
	
	GLint indexCounter;
	GLint vertexCounter;

	GLuint *buffers;
	GLuint meshID;

protected:
	vector<vec3> vertices;
	vector<vec3> normals;
	vector<vec4> colors;
	vector<vec2> texUVs;
	vector<GLuint> indices;

	ShaderProgram shader;
	MeshData data;
	vec3 position;
	GLfloat scale;
	mat4 rotationMatrix;

	void SetUp(void);
	void LoadData(void);
	void LoadArrayBuffer(GLint buffer, vector<vec2> data);
	void LoadArrayBuffer(GLint buffer, vector<vec3> data);
	void LoadArrayBuffer(GLint buffer, vector<vec4> data);
	void LoadIndexer(GLint buffer, vector<GLuint> indexer);
	void BindAllBuffers(void);

public:
	Mesh(ShaderProgram *shader);
	Mesh(ShaderProgram *shader, MeshData *data);
	~Mesh(void);

	static Mesh FromFile(string filepath);

	void AddVertex(vec3 vertex);
	void AddNormal(vec3 normal);
	void AddTexCoord(vec2 texCoord);
	void AddColor(vec4 color);
	void AddIndex(GLuint index);
	void AddIndexes(int count, GLuint *index);

	vec3 Position(void);
	void Position(vec3 position);

	GLfloat Scale(void);
	void Scale(GLfloat);

	mat4 ModelMatrix(void);
	ShaderProgram Shader(void);

	void Update(GLfloat deltaTime);
	void Draw(void);

	void RotateX(GLfloat angle);
	void RotateY(GLfloat angle);
	void RotateZ(GLfloat angle);
};