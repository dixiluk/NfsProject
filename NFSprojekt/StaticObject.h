#pragma once
#include "GraphicalObject.h"
#include "Model.h"
class StaticObject :
	public GraphicalObject
{
public:
	Model* model;
	StaticObject();
	~StaticObject();
	void draw(Shader* shad = 0);

};

