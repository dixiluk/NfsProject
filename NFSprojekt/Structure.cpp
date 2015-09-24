#include "Structure.h"

std::list<Structure*> Structure::Structures;


Structure::Structure(glm::vec3 position, Model* model, Shader* shader) : StaticObject()
{
	this->position = position;
	this->model = model;
	this->shader = shader;
	Structures.push_back(this);
}

Structure::~Structure()
{
}

void Structure::draw(Shader *shad)
{
	if (shad == 0)
		shad = this->shader;
	shad->onPrepare(this);

	for (std::list<ModelObject*>::iterator it = this->model->objects.begin();
		it != this->model->objects.end(); it++){

		ModelObject* obj = *it;
		shad->onDraw(obj);
		glBindVertexArray(obj->arrayBuffer);
		glDrawElements(GL_TRIANGLES, obj->verticesCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	}
}
