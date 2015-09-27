#include "Car.h"
#include "Engine.h"
#include "Structure.h"
#include "Camera.h"
#include "kulka.h"

#include "StructureShader.h"

#define addSpeedPerFrame 0.25
#define minusSpeedPerFrame 1
#define rotationPowerFrame 0.25
#define carLength 5.1
#define carWidth 2.1

std::list<Car*> Car::Cars;

Car* Car::ControledCar = 0;
Car::Car(glm::vec3 position, Model* model, Shader* shader) : DynamicObject(position, shader)
{
	this->colisionPoint.push_back(glm::vec3(carWidth / 2.0, -carLength / 2.0, 0.3));
	this->colisionPoint.push_back(glm::vec3(0, -carLength / 2.0-0.1, 0.3));
	this->colisionPoint.push_back(glm::vec3(-carWidth / 2.0, -carLength / 2.0, 0.3));
	this->colisionPoint.push_back(glm::vec3(carWidth / 2.0, carLength / 2.0+0.2, 0.3));
	this->colisionPoint.push_back(glm::vec3(0, carLength / 2.0+0.3, 0.3));
	this->colisionPoint.push_back(glm::vec3(-carWidth / 2.0, carLength / 2.0+0.2, 0.3));
	this->model = model;
	Cars.push_back(this);
	this->speed = 0;
	this->rpm = 0;
	this->gear = 1;
	this->gearup = false;
	this->geardown = false;
	this->maxGear = 6;
	this->rotationAxis = glm::vec3(1, 0, 0);
	this->speedAt6kRps[0] = -30;
	this->speedAt6kRps[1] = 45;
	this->speedAt6kRps[2] = 80;
	this->speedAt6kRps[3] = 120;
	this->speedAt6kRps[4] = 150;
	this->speedAt6kRps[5] = 180;
	this->speedAt6kRps[6] = 220;
	ControledCar = this;
	this->directionPoint = glm::vec3(0, -1, 0);
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
	if (this->rpm <= 0) this->rpm = 0;

}



void Car::gearbox(){
	if (Engine::Instance->keyboard[Engine::Instance->gearboxDownKey]){
		if (this->gearup == false)
		{
			this->gearup = true;

			if (this->speed == 0 || this->gear>0)
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

			if (this->gear == 1 && this->speed == 0) {
				this->gear--;
				this->calculaterpm();
			}

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


void Car::minusSpeed()
{
	double tmpSpeed = minusSpeedPerFrame;
	if (this->speed > 0)
	{
		this->speed -= tmpSpeed;
		if (this->speed < 0) this->speed = 0;
	}

	if (this->speed < 0)
	{
		this->speed += tmpSpeed;
		if (this->speed > 0) this->speed = 0;
	}

	this->calculaterpm();

}

void Car::addSpeed()
{
	double tmpSpeed = addSpeedPerFrame - 0.03*this->gear;
	if (this->gear == 0)
	{
		if (this->rpm < 4000) {

			this->speed -= (tmpSpeed*((8 + 3 * this->rpm / 1000) / 20));
		}
		if (this->rpm >= 4000) {

			this->speed -= (tmpSpeed*(1 - (this->rpm - 4000) / 2800));
		}
	}
	else
	{
		if (this->rpm < 4000) {

			this->speed += (tmpSpeed*((8 + 3 * this->rpm / 1000) / 20));
		}
		if (this->rpm >= 4000) {

			this->speed += (tmpSpeed*(1 - (this->rpm - 4000) / 2800));
		}
	}
	this->calculaterpm();

}


void Car::turn(bool site){
	if (this->speed <= 0){
		if (site)
		{
			this->rotationAxis.z += (float) (0.006 * log(-this->speed + 1)*1.4);
		}
		else
		{
			this->rotationAxis.z -= (float) (0.006 * log(-this->speed + 1)*1.4);

		}
	}
	else
	{
		if (this->speed > 30) {
			if (site)
				this->rotationAxis.z += (float) (0.006 * (-log(this->speed - 20) + 7));
			else
				this->rotationAxis.z -= (float) (0.006 * (-log(this->speed - 20) + 7));

		}
		else
		{
			if (site)
			{
				this->rotationAxis.z += (float) (0.006 * log(this->speed + 1)*1.4);
			}
			else
			{
				this->rotationAxis.z -= (float) (0.006 * log(this->speed + 1)*1.4);

			}
		}
	}
}




void Car::compute()
{
	if (ControledCar == this){
		this->gearbox();

		printf("Gear: %i  speed: %f  rpm: %f\n", this->gear, this->speed, this->rpm);

		if (Engine::Instance->keyboard[101])
		{
			this->addSpeed();
		}
		if (Engine::Instance->keyboard[103])
		{
			this->minusSpeed();
		}
		if (Engine::Instance->keyboard[100])
		{
			this->turn(false);
		}
		if (Engine::Instance->keyboard[102])
		{
			this->turn(true);
		}
		this->move();


	}
}


void Car::move(){



	for each (glm::vec3 var in this->colisionPoint)
	{
		glm::vec4 vec = this->iModelMat * glm::vec4(var, 1);
		glm::vec3 t = glm::vec3(vec);


		
		glm::vec4 vec2 = this->iModelMat * glm::vec4(this->directionPoint - this->position +t , 1);

		glm::vec3 t2 = (glm::vec3(vec2) - t)*(float) (this->speed / 100);

		glm::vec3* tmp1 = new glm::vec3(0, 0, 0);
		glm::vec3* tmp2 = new glm::vec3(0,0,0);

		/*if (Structure::Colision(tmp1, tmp2, t, t+t2))
			printf("Kolizja \n");*/

		//Engine::Instance->activeScene->kulki.push_back(new kulka(t+t2, new StructureShader()));
	}

	glm::vec4 vec = this->iModelMat * glm::vec4(this->directionPoint, 1);
	glm::vec3 t = (glm::vec3(vec) - this->position)*(float) (this->speed / 100);

	Engine::Instance->activeScene->kulki.push_back(new kulka(this->position+t, new StructureShader()));
	Engine::Instance->activeScene->kulki.push_back(new kulka(this->position+this->directionPoint, new StructureShader()));

	/*if (Structure::Colision(tmp1, tmp2, this->position, this->position+t))
		printf("Kolizja \n");*/

	this->position += t;
	Camera::ActiveCamera->position = this->position;

}



