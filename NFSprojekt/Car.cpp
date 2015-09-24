#include "Car.h"
#include "Engine.h"

std::list<Car*> Car::Cars;

Car::Car(glm::vec3 position, Model* model, Shader* shader) : DynamicObject(position, shader)
{
	this->model = model;
	Cars.push_back(this);
}


Car::~Car()
{
}


void Car::draw()
{
	this->shader->onPrepare(this);

	for (std::list<ModelObject*>::iterator it = this->model->objects.begin();
		it != this->model->objects.end(); it++){

		ModelObject* obj = *it;
		this->shader->onDraw(obj);
		glBindVertexArray(obj->arrayBuffer);
		glDrawElements(GL_TRIANGLES, obj->verticesCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
void Car::compute()
{
	if (Engine::Instance->keyboard[101]){
		this->position.z += 0.01;

	}
	if (Engine::Instance->keyboard[103]){
		this->position.z -= 0.01;

	}
	if (Engine::Instance->keyboard[100]){
		this->position.x += 0.01;

	}
	if (Engine::Instance->keyboard[102]){
		this->position.x -= 0.01;

	}
}