#pragma once
#include "StaticObject.h"

class Structure : public StaticObject
{
public:
	static std::list<Structure*> Structures;
	Structure(glm::vec3 position, Model* model, Shader* shader, bool Colision);
	~Structure();
	glm::mat4 iModelMat;
	static bool Colision(glm::vec3* intersectionPoint, glm::vec3* surfaceVector, glm::vec3 pont1, glm::vec3 pont2);

protected:
	void draw();
private:
	static bool PointToMesh(glm::vec3 P1, glm::vec3 P2, float* mesh, int meshSize, glm::mat4 invertedModelMatrix, glm::vec3* intersectionPoint, glm::vec3* surfaceVector);
	static bool rayIntersectsTriangle(glm::vec3 p, glm::vec3 d, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, float& lenOnLine);

};
