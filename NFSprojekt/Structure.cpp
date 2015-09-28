#include "Structure.h"

std::list<Structure*> Structure::Structures;


Structure::Structure(glm::vec3 position, Model* model, Shader* shader, bool colision) : StaticObject(position, shader)
{
	this->model = model;
	this->rotationAxis = glm::vec3{ 1, 0, 0 };
	this->isColision = colision;
	Structures.push_back(this);
}

Structure::~Structure()
{
}

void Structure::draw()
{
	this->shader->onPrepare(this);

	/*for (std::list<ModelObject*>::iterator it = this->model->objects.begin();
		it != this->model->objects.end(); it++)
	{
		ModelObject* obj = *it;

		this->shader->onDraw(obj);

		glBindVertexArray(obj->arrayBuffer);
		glDrawElements(GL_TRIANGLES, obj->verticesCount, GL_UNSIGNED_INT, 0); //Rysowanie obiektu z bufora wierzchołków
		glBindVertexArray(0);
	}*/
}


bool Structure::Colision(glm::vec3* intersectionPoint, glm::vec3* surfaceVector, glm::vec3 point1, glm::vec3 point2){
	for each (Structure* item in Structure::Structures)
	{
		if (item->isColision){

			for each (ModelObject* item2 in item->model->objects){

				if (Structure::PointToMesh(point1, point2, item2->v, item2->verticesCount * 3, item->iModelMat, intersectionPoint, surfaceVector))
				{
					return true;
				}
			}
		}
	}
	return false;

}


bool Structure::rayIntersectsTriangle(glm::vec3 p, glm::vec3 d, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, float& lenOnLine)
{
	glm::vec3 e1, e2, h, s, q;
	float a, f, u, v;
	e1 = v1 - v0;
	e2 = v2 - v0;
	h = cross(d, e2);
	a = dot(e1, h);
	if (a > -0.00001 && a < 0.00001)
		return(false);

	f = 1 / a;
	s = p - v0;
	u = f * (dot(s, h));

	if (u < 0.0 || u > 1.0)
		return(false);

	q = cross(s, e1);
	v = f * dot(d, q);

	if (v < 0.0 || u + v > 1.0)
		return(false);

	lenOnLine = f * dot(e2, q);

	return(true);
}

bool Structure::PointToMesh(glm::vec3 P1, glm::vec3 P2, float* mesh, int meshSize, glm::mat4 ModelMatrix,
	glm::vec3* intersectionPoint, glm::vec3* surfaceVector)
{
	glm::vec3 dir;
	glm::vec3 p1, p2, p3;
	float len;

	for (int i = 0; i<meshSize; i += 9){
		p1.x = mesh[i]; p1.y = mesh[i + 1]; p1.z = mesh[i + 2];
		p2.x = mesh[i + 3]; p2.y = mesh[i + 4]; p2.z = mesh[i + 5];
		p3.x = mesh[i + 6]; p3.y = mesh[i + 7]; p3.z = mesh[i + 8];
		p1 = glm::vec3(ModelMatrix * glm::vec4(p1, 1.0));
		p2 = glm::vec3(ModelMatrix * glm::vec4(p2, 1.0));
		p3 = glm::vec3(ModelMatrix * glm::vec4(p3, 1.0));
		dir = normalize(P2 - P1);
		if (rayIntersectsTriangle(P1, dir, p1, p2, p3, len)){
			if (distance(P1, P2) >= len&&len >= 0){
				*intersectionPoint = P1 + dir*len;
				glm::vec3 u = p2 - p1, v = p3 - p1;
				*surfaceVector = normalize(cross(u, v));
				return true;
			}
		}
	}
	return false;
}
