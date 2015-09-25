#pragma once
#include "Environment.h"
#include "ModelObject.h"

class Model
{
	friend class Structure;
	friend class DynamicObject;
private:
	static std::list<Model*> Models;
public:
	std::list<ModelObject*> objects;
	char* modelName;
	Model(char* name);
	~Model();
};


