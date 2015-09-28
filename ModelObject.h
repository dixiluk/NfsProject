#pragma once
#include "Environment.h"
#include "Texture.h"


class ModelObject
{
public:
	GLfloat* v, *uv, *n;
	const char* name;
	int verticesCount;
	glm::vec3 relativePosition;
	Texture *diffuseMap;
	GLuint arrayBuffer;
	void createArrayBuffer();
	void extractMesh(FbxNode* node);
	ModelObject(FbxNode* node);
	~ModelObject();
};

