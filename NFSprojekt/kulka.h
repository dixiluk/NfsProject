#pragma once
#include "DynamicObject.h"
class kulka :
	public DynamicObject

{
public:
	static Model* kulkam;
	void draw();
	void compute();
	static void tworz(glm::vec3 poz);
	static int limit;
	kulka(glm::vec3 position, Shader* shader);
	glm::mat4 iModelMat;
	~kulka();
};

