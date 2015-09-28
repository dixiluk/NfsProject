#include "StaticObject.h"


StaticObject::StaticObject(glm::vec3 position, Shader* shader) : GraphicalObject(position, shader)
{
}


StaticObject::~StaticObject()
{
}



void StaticObject::draw(){}