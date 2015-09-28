#pragma once
#include "Environment.h"
#include "Shader.h"

class GraphicalObject
{
	friend class Engine;
	friend class StructureShader;
	friend class TerrainShader;
	friend class CarShader;
public:
	GraphicalObject(glm::vec3 position, Shader* shader);
	~GraphicalObject();
	bool isColision;
	glm::vec3 rotationAxis;
protected:
	glm::vec3 position;
	Shader* shader;

	virtual void compute();
	virtual void draw();
};

