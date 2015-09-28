#pragma once
#include "Environment.h"
#include "GraphicalObject.h"
#include "CheckPoint.h"

class Level
{
public:
	std::list<GraphicalObject*> graphicalObjects;
	std::list<GraphicalObject*> kulki; //
	void addGraphicalObject(GraphicalObject* object);
	CheckPoint checkPoints[4];
	Level();
	~Level();
	
};

