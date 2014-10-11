#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")

#include "Mesh.h"

using namespace glm;
using namespace std;

Mesh::Mesh(ShaderProgram *shader){
	scale = 1;
	rotationMatrix = mat4(1.0f);
	this->shader = *shader;
}

Mesh::Mesh(ShaderProgram *shader, MeshData *data){
	scale = 1;
	rotationMatrix = mat4(1.0f);
	this->shader = *shader;

	LoadData();
}

Mesh::~Mesh(void){
	shader.~ShaderProgram();
}



void Mesh::AddVertex(vec3 vertex){
	vertices.push_back(vertex);
}

void Mesh::AddNormal(vec3 normal){
	normals.push_back(normal);
}

void Mesh::AddTexCoord(vec2 texCoord){
	texUVs.push_back(texCoord);
}

void Mesh::AddColor(vec4 color){
	colors.push_back(color);
}

void Mesh::AddIndex(GLuint index){
	indices.push_back(index);
}

void Mesh::AddIndexes(int count, GLuint *index){
	indices.insert(indices.end(), index, index + count - 1);
}



void Mesh::LoadData(void){
	int unitCounter = data.data.size();
	for (int i = 0; i < unitCounter; i++)
	{
		vertices.push_back(data.data[i].position);

		if (data.data[i].normal != vec3(0, 0, 0))
			normals.push_back(data.data[i].normal);

		if (data.data[i].texCoord != vec2(-1, -1))
			texUVs.push_back(data.data[i].texCoord);
	}

	int indexCounter = data.indices.size();
	for (int i = 0; i < indexCounter; i++)
		indices.push_back(data.indices[i]);
}

void Mesh::LoadArrayBuffer(GLint buffer, vector<vec2> data){
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::LoadArrayBuffer(GLint buffer, vector<vec3> data){
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::LoadArrayBuffer(GLint buffer, vector<vec4> data){
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::LoadIndexer(GLint buffer, vector<GLuint> indexer){
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexer), &indexer, GL_STATIC_DRAW);
}

void Mesh::SetUp(void){
	GLint bufferCounter = 1;

	if (colors.size() > 0) { bufferCounter++; hasColor = true; }
	if (normals.size() > 0) { bufferCounter++; hasNormals = true; }
	if (texUVs.size() > 0) { bufferCounter++; hasUVs = true; }
	if (indices.size() > 0) { bufferCounter++; isIndexed = true; }

	glGenBuffers(bufferCounter, buffers);

	LoadArrayBuffer(buffers[0], vertices);
	vertexCounter = vertices.size();

	GLint buffersUsed = 1;
	if (hasColor)
	{
		colorBuffer = buffersUsed;
		LoadArrayBuffer(buffers[colorBuffer], colors);
		buffersUsed++;
	}
	if (hasNormals)
	{
		normalBuffer = buffersUsed;
		LoadArrayBuffer(buffers[normalBuffer], normals);
		buffersUsed++;
	}
	if (hasUVs)
	{
		UVbuffer = buffersUsed;
		LoadArrayBuffer(buffers[UVbuffer], texUVs);
		buffersUsed++;
	}
	if (isIndexed)
	{
		indexBuffer = buffersUsed;
		LoadIndexer(buffers[indexBuffer], indices);
		indexCounter = indices.size();
	}

	glGenVertexArrays(1, &meshID);
	//glBindVertexArray(meshID);
}



ShaderProgram Mesh::Shader(void){
	return shader;
}

vec3 Mesh::Position(void){
	return position;
}

void Mesh::Position(vec3 position){
	this->position = position;
}

GLfloat Mesh::Scale(void){
	return scale;
}

void Mesh::Scale(GLfloat scale){
	this->scale = scale;
}

mat4 Mesh::ModelMatrix(void){
	return
		glm::translate(position) *
		glm::scale(vec3(scale, scale, scale)) *
		rotationMatrix;
}

void Mesh::BindAllBuffers(void){
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glVertexAttribPointer(ARRAYINDEX_VERTEXPOSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);

	if (hasColor)
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffers[colorBuffer]);
		glVertexAttribPointer(ARRAYINDEX_VERTEXCOLOR, 4, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (hasNormals)
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffers[normalBuffer]);
		glVertexAttribPointer(ARRAYINDEX_VERTEXNORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (hasUVs)
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffers[UVbuffer]);
		glVertexAttribPointer(ARRAYINDEX_VERTEXTEXTUREUV, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (isIndexed)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[indexBuffer]);
}

void Mesh::Update(GLfloat deltaTime){

}

void Mesh::Draw(void){
	shader.SetVariable(NAMEOF_MODELMATRIX, ModelMatrix());
	shader.Activate();

	glBindVertexArray(meshID);
	BindAllBuffers();

	glEnableVertexAttribArray(ARRAYINDEX_VERTEXPOSITION);
	if (hasColor) glEnableVertexAttribArray(ARRAYINDEX_VERTEXCOLOR);
	if (hasNormals) glEnableVertexAttribArray(ARRAYINDEX_VERTEXNORMAL);
	if (hasUVs) glEnableVertexAttribArray(ARRAYINDEX_VERTEXTEXTUREUV);
	
	if (isIndexed)
		glDrawElements(GL_TRIANGLES, indexCounter, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, vertexCounter);
	
	glDisableVertexAttribArray(ARRAYINDEX_VERTEXPOSITION);
	glDisableVertexAttribArray(ARRAYINDEX_VERTEXCOLOR);
	glDisableVertexAttribArray(ARRAYINDEX_VERTEXNORMAL);
	glDisableVertexAttribArray(ARRAYINDEX_VERTEXTEXTUREUV);
	shader.Deactvate();
}

void Mesh::RotateX(GLfloat angle){
	rotationMatrix = glm::rotate(angle, vec3(1, 0, 0)) * rotationMatrix;
}

void Mesh::RotateY(GLfloat angle){
	rotationMatrix = glm::rotate(angle, vec3(0, 1, 0)) * rotationMatrix;
}

void Mesh::RotateZ(GLfloat angle){
	rotationMatrix = glm::rotate(angle, vec3(0, 0, 1)) * rotationMatrix;
}

Mesh* Mesh::FromFile(ShaderProgram *shader, string filepath){
	MeshData meshData;
	vector<vec3> positions;
	vector<vec3> normals;
	vector<vec2> texCoords;

	FILE *file = fopen(filepath.c_str(), "r");

	if (file == NULL){
		cout << "Could not open file " << filepath;
		return NULL;
	}

	char char_line[256];
	int filestatus = fscanf(file, "%s", char_line);

	while (filestatus != EOF){
		string line = char_line;

		if (line.size() == 0 || line.substr(0, 1) == "#")
			continue;

		if (line.substr(0, 2) == "v "){
			vec3 v;
			fscanf(file, "%f %f %f\n", &v.x, &v.y, &v.z);
			positions.push_back(v);
			continue;
		}

		if (line.substr(0, 3) == "vn "){
			vec3 n;
			fscanf(file, "%f %f %f\n", &n.x, &n.y, &n.z);
			normals.push_back(n);
			continue;
		}

		if (line.substr(0, 3) == "vt "){
			vec2 t;
			fscanf(file, "%f %f %f\n", &t.x, &t.y);
			texCoords.push_back(t);
			continue;
		}

		if (line.substr(0, 2) == "f "){
			uint vi[3], ti[3], ni[3];

			if (line.size() < 17){
				int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", vi[0], ni[0], vi[1], ni[1], vi[2], ni[2]);

				if (matches != 6){	// wrong format
					cout << "";
					fclose(file);
					return NULL;
				}

				for (int i = 0; i < 3; i++){
					VertexUnit unit(positions[vi[i]], normals[ni[i]], vec2(-1.0f, -1.0f));

					meshData.AddVertexUnit(unit);
				}

				continue;
			}
			else {
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", vi[0], ti[0], ni[0], vi[1], ti[1], ni[1], vi[2], ti[2], ni[2]);

				if (matches != 9){	// wrong format
					cout << "";
					fclose(file);
					return NULL;
				}

				for (int i = 0; i < 3; i++){
					VertexUnit unit(positions[vi[i]], normals[ni[i]], texCoords[ti[i]]);

					meshData.AddVertexUnit(unit);
				}

				continue;
			}
		}

		// if line starts with anything else (mtllib, usemtl), it is ignored (for now).

		filestatus = fscanf(file, "%s", char_line);
	}

	fclose(file);
	return new Mesh(shader, &meshData);
}