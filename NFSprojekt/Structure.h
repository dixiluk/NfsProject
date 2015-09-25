#pragma once
#include "StaticObject.h"

class Structure : public StaticObject
{
public:
	static std::list<Structure*> Structures;
	Structure(glm::vec3 position, Model* model, Shader* shader);
	~Structure();
	glm::mat4 iModelMat;
protected:
	void draw();

};
