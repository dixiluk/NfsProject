#pragma once
#include "Environment.h"
#include "Shader.h"

class GraphicalObject
{
	friend class Engine;
	friend class StructureShader;
public:
	GraphicalObject();
	~GraphicalObject();
protected:
	glm::vec3 position;
	glm::vec3 rotationAxis;
	Shader* shader;
	double rotationPower;

	virtual void compute();
	virtual void draw(Shader *shad = 0);
};

