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

	for (std::list<ModelObject*>::iterator it = this->model->objects.begin();
		it != this->model->objects.end(); it++)
	{
		ModelObject* obj = *it;

		this->shader->onDraw(obj);

		glBindVertexArray(obj->arrayBuffer);
		glDrawElements(GL_TRIANGLES, obj->verticesCount, GL_UNSIGNED_INT, 0); //Rysowanie obiektu z bufora wierzchołków
		glBindVertexArray(0);
	}
}
