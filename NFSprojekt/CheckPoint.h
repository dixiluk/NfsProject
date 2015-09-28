#pragma once
#include "Environment.h"

class CheckPoint
{
public:
	glm::vec3 position;
	double tolerance;
	CheckPoint();
	CheckPoint(glm::vec3 position, double tolerance);
	bool check(glm::vec3 position);
	~CheckPoint();
};

