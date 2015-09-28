#include "GraphicalObject.h"


GraphicalObject::GraphicalObject(glm::vec3 position, Shader* shader)
{
	this->position = position;
	this->shader = shader;
}


GraphicalObject::~GraphicalObject()
{
}


void GraphicalObject::draw(){}

void GraphicalObject::compute(){}

