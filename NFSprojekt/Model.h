#pragma once
#include "Environment.h"
#include "ModelObject.h"

class Model
{
	friend class Structure;
	friend class DynamicObject;
private:
	static std::list<Model*> Models;
	char* modelName;
public:
	std::list<ModelObject*> objects;
	Model(char* name);
	~Model();
};


