#include "VertexUnit.h"

using namespace glm;

VertexUnit::VertexUnit(vec3 position, vec3 normal, vec2 texCoord){
	this->position = position;
	this->normal = normal;
	this->texCoord = texCoord;
}

VertexUnit::~VertexUnit(void){
}

bool VertexUnit::PositionEquals(VertexUnit other){
	return this->position == other.position;
}

bool VertexUnit::NormalEquals(VertexUnit other){
	return this->normal == other.normal;
}

bool VertexUnit::TexCoordEquals(VertexUnit other){
	return this->texCoord == other.texCoord;
}

bool operator==(VertexUnit v1, VertexUnit v2){
	return
		v1.position == v2.position &&
		v1.normal == v2.normal &&
		v1.texCoord == v2.texCoord;
}