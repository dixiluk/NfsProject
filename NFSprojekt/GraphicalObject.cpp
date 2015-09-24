#include "GraphicalObject.h"


GraphicalObject::GraphicalObject(glm::vec3 position, Shader* shader)
{
	this->position = position;
	this->rotationPower = 0;
	this->shader = shader;
}


GraphicalObject::~GraphicalObject()
{
}


void GraphicalObject::draw(){}

void GraphicalObject::compute(){}

