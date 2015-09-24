#include "DynamicObject.h"


DynamicObject::DynamicObject(glm::vec3 position, Shader* shader) : GraphicalObject(position, shader)
{
}


DynamicObject::~DynamicObject()
{
}


void DynamicObject::draw(){}
void DynamicObject::compute(){}