#pragma once
#include "GraphicalObject.h"
#include "Model.h"

class DynamicObject : public GraphicalObject
{
public:
	Model* model;
	DynamicObject(glm::vec3 position, Shader* shader);
	~DynamicObject();
	void draw();
	void compute();
};

