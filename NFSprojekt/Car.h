#pragma once
#include "DynamicObject.h"
class Car :
	public DynamicObject
{
public:
	static std::list<Car*> Cars;
	std::list<glm::vec3> colisionPoint;

	void draw();
	void compute();
	Car(glm::vec3 position, Model* model, Shader* shader);
	~Car();
	glm::mat4 iModelMat;
private:
	glm::vec3 directionPoint;
	void move();
	static Car* ControledCar;
	double speed, rpm;
	short gear, maxGear;
	bool gearup, geardown;
	void calculateSpeed();
	void calculaterpm();
	int speedAt6kRps [7];
	void addSpeed();
	void minusSpeed();
	void gearbox();
	void turn(bool site);
	bool PointToMesh(glm::vec3 P1, glm::vec3 P2, float* mesh, int meshSize, glm::mat4 invertedModelMatrix, glm::vec3* intersectionPoint, glm::vec3* surfaceVector);
	bool rayIntersectsTriangle(glm::vec3 p, glm::vec3 d, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, float& lenOnLine);
	void Colision();
};

