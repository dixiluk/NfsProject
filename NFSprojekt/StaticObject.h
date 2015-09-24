#pragma once
#include "GraphicalObject.h"
#include "Model.h"
class StaticObject :
	public GraphicalObject
{
public:
	Model* model;
	StaticObject(glm::vec3 position, Shader* shader);
	~StaticObject();
	void draw();

};

