#pragma once
#include "DynamicObject.h"
class Car :
	public DynamicObject
{
public:
	static std::list<Car*> Cars;


	void draw();
	void compute();
	Car(glm::vec3 position, Model* model, Shader* shader);
	~Car();
private:
	static Car* Controld;
};

