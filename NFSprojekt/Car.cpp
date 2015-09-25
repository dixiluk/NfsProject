#include "Car.h"
#include "Engine.h"

#define addSpeedPerFrame 0.25
#define rotationPowerFrame 0.25

std::list<Car*> Car::Cars;

Car::Car(glm::vec3 position, Model* model, Shader* shader) : DynamicObject(position, shader)
{
	this->model = model;
	Cars.push_back(this);
	this->control = true;
	this->speed = 0;
	this->rpm = 0;
	this->gear = 1;
	this->gearup = false;
	this->geardown = false;
	this->maxGear = 6;
	this->rotationAxis = glm::vec3{ 0.5, 0, 0 };
	this->speedAt6kRps[0] = -30;
	this->speedAt6kRps[1] = 45;
	this->speedAt6kRps[2] = 80;
	this->speedAt6kRps[3] = 120;
	this->speedAt6kRps[4] = 150;
	this->speedAt6kRps[5] = 180;
	this->speedAt6kRps[6] = 220;
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


void Car::calculateSpeed()
{

		this->speed = (double)this->speedAt6kRps[this->gear] / 6000 * this->rpm;
}
void Car::calculaterpm()
{

		this->rpm = this->speed * 6000 / (double)this->speedAt6kRps[this->gear];
		if (this->rpm > 7000)
		{
			this->rpm = 7000;
			this->calculateSpeed();
		}

}



void Car::gearbox(){
	if (Engine::Instance->keyboard[Engine::Instance->gearboxDownKey]){
		if (!this->gearup)
		{
			this->gearup = true;
			if (this->gear < this->maxGear){
				this->gear++;
				this->calculaterpm();
			}
		}
	}

	if (!Engine::Instance->keyboard[Engine::Instance->gearboxDownKey])
	{
		this->gearup = false;
	}

	if (Engine::Instance->keyboard[Engine::Instance->gearboxUpKey])
	{
		if (!this->geardown)
		{
			this->geardown = true;
			if (this->gear > 1){
				this->gear--;
				this->calculaterpm();
			}

		}
	}

	if (!Engine::Instance->keyboard[Engine::Instance->gearboxUpKey])
	{
		
		this->geardown = false;
		
	}
}


void Car::addSpeed()
{
	double tmpSpeed = addSpeedPerFrame-0.03*this->gear;
		if (this->rpm < 4000){

			this->speed += (tmpSpeed*((8 + 3 * this->rpm / 1000) / 20));
		}
		if (this->rpm >= 4000){

			this->speed += (tmpSpeed*(1-(this->rpm-4000)/2800));
		}

	this->calculaterpm();

}


void Car::turn(bool site){
	//this->rotationAxis();

}




void Car::compute()
{
	if (control){
		this->gearbox();

		printf("Gear: %i  speed: %f  rpm: %f\n", this->gear, this->speed, this->rpm);





		if (Engine::Instance->keyboard[101])
		{
			this->addSpeed();

		}
		if (Engine::Instance->keyboard[103])
		{
			this->addSpeed();

		}
		if (Engine::Instance->keyboard[100])
		{
			this->rotationAxis = glm::vec3{ 0.5, 0, 0 };

		}
		if (Engine::Instance->keyboard[102])
		{
			this->rotationAxis = glm::vec3{ 1, 0, 0 };
		}

	}
}