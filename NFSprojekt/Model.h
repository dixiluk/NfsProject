#pragma once
#include "Environment.h"
#include "ModelObject.h"

class Model
{
	friend class Structure;
	friend class DynamicObject;
private:
	static std::list<Model*> Models;
	std::list<ModelObject*> objects;
	char* modelName;
public:

	Model(char* name);
	~Model();
	static Model* GetModel(char* name, char* location = "Models");
};


