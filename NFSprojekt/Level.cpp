#include "Level.h"


Level::Level()
{
	this->checkPoints[0] = CheckPoint(glm::vec3(-110, -4.5, -160), 10);
	this->checkPoints[1] = CheckPoint(glm::vec3(115, -4.5, 87), 10);
	this->checkPoints[2] = CheckPoint(glm::vec3(160, -4.5, -90), 10);
	this->checkPoints[3] = CheckPoint(glm::vec3(210, -4.5, 175), 10);
}


Level::~Level()
{
}

void Level::addGraphicalObject(GraphicalObject* object){
	this->graphicalObjects.push_back(object);
}
