#pragma once
#include "Environment.h"
#include "Shader.h"

class GraphicalObject
{
	friend class Engine;
	friend class StructureShader;
public:
	GraphicalObject(glm::vec3 position, Shader* shader);
	~GraphicalObject();
	bool isColision;
protected:
	glm::vec3 position;
	glm::vec3 rotationAxis;
	Shader* shader;

	virtual void compute();
	virtual void draw();
};

