#include "CheckPoint.h"


CheckPoint::CheckPoint(glm::vec3 position, double tolerance)
{
	this->position = position;
	this->tolerance = tolerance;
}


CheckPoint::CheckPoint()
{

}
CheckPoint::~CheckPoint()
{
}

bool CheckPoint::check(glm::vec3 position){
	double tmp = glm::length(this->position - position);
	if (tmp<this->tolerance && tmp>-this->tolerance) return true;
	return false;
}