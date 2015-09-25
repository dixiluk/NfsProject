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
	bool control;
	double speed, rpm;
	short gear, maxGear;
	bool gearup, geardown;
	void calculateSpeed();
	void calculaterpm();
	int speedAt6kRps [7];
	void addSpeed();
	void gearbox();
	void turn(bool site);

};

