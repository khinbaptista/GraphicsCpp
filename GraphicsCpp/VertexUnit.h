#pragma once

#include <glm/glm.hpp>

using namespace glm;

class VertexUnit
{
public:
	vec3 position;
	vec3 normal;
	vec2 texCoord;

	VertexUnit(vec3 position, vec3 normal, vec2 texCoord);
	~VertexUnit(void);

	bool PositionEquals(VertexUnit other);
	bool NormalEquals(VertexUnit other);
	bool TexCoordEquals(VertexUnit other);
};

bool operator==(VertexUnit v1, VertexUnit v2);
bool operator!=(VertexUnit v1, VertexUnit v2);