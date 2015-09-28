#include "Car.h"
#include "Engine.h"
#include "Structure.h"
#include "Camera.h"
#include "kulka.h"
#include "Text.h"
#include "CheckPoint.h"

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
	this->colisionPoint[0]=(glm::vec3(carWidth / 2.0, -carLength / 2.0, 0.3));
	this->colisionPoint[1]=(glm::vec3(0, -carLength / 2.0-0.1, 0.3));
	this->colisionPoint[2] =(glm::vec3(-carWidth / 2.0, -carLength / 2.0, 0.3));
	this->colisionPoint[3] = (glm::vec3(carWidth / 2.0, carLength / 2.0 + 0.2, 0.3));
	this->colisionPoint[4] = (glm::vec3(0, carLength / 2.0 + 0.3, 0.3));
	this->colisionPoint[5] = (glm::vec3(-carWidth / 2.0, carLength / 2.0 + 0.2, 0.3));
	this->model = model;
	Cars.push_back(this);
	this->maxGear = 6;
	this->speedAt6kRps[0] = -30;
	this->speedAt6kRps[1] = 45;
	this->speedAt6kRps[2] = 80;
	this->speedAt6kRps[3] = 120;
	this->speedAt6kRps[4] = 150;
	this->speedAt6kRps[5] = 180;
	this->speedAt6kRps[6] = 220;
	this->bestTime = 0;
	ControledCar = this;
	this->directionPoint = glm::vec3(0, -1, 0);
	this->restart();
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


bool Car::turn(bool site){
	double tmp = this->rotationAxis.z;
	if (this->speed <= 0){
		if (site)
		{
			tmp += (float) (0.006 * log(-this->speed + 1)*1.4);
		}
		else
		{
			tmp -= (float) (0.006 * log(-this->speed + 1)*1.4);

		}
	}
	else
	{
		if (this->speed > 30) {
			if (site)
				tmp += (float) (0.006 * (-log(this->speed - 20) + 7));
			else
				tmp -= (float) (0.006 * (-log(this->speed - 20) + 7));

		}
		else
		{
			if (site)
			{
				tmp += (float) (0.006 * log(this->speed + 1)*1.4);
			}
			else
			{
				tmp -= (float) (0.006 * log(this->speed + 1)*1.4);

			}
		}
	}
	
	glm::mat4 ModelMatrix;
	ModelMatrix = glm::translate(glm::mat4(1.0f), (this->position));
	ModelMatrix = glm::rotate(ModelMatrix, (float) (-1.57079633f*this->rotationAxis.x), glm::vec3(1, 0, 0)); //Macierz modelu
	ModelMatrix = glm::rotate(ModelMatrix, (float) (-1.57079633f*this->rotationAxis.y), glm::vec3(0, 1, 0)); //Macierz modelu
	ModelMatrix = glm::rotate(ModelMatrix, (float) (-1.57079633f*tmp), glm::vec3(0, 0, 1)); //Macierz modelu
	
	for each (glm::vec3 var in this->colisionPoint)
	{
		glm::vec4 vec = this->iModelMat * glm::vec4(var, 1);
		glm::vec3 t = glm::vec3(vec);

		glm::vec4 vec2 = ModelMatrix * glm::vec4(var, 1);
		glm::vec3 t2 = glm::vec3(vec2);

		glm::vec3* tmp1 = new glm::vec3(0, 0, 0);
		glm::vec3* tmp2 = new glm::vec3(0, 0, 0);

		if (Structure::Colision(tmp1, tmp2, t, t2))
		{
			printf("Kolizja \n");
			return false;
		}
	}

	this->rotationAxis.z = tmp;
	this->iModelMat = ModelMatrix;
	return true;
}




void Car::compute()
{
	if (ControledCar == this){
		this->gearbox();
		this->move();

		if (Engine::Instance->keyboard[100])
		{
			this->turn(false);
		}
		if (Engine::Instance->keyboard[102])
		{
			this->turn(true);
		}
		if (Engine::Instance->keyboard[101])
		{
			this->addSpeed();
		}
		if (Engine::Instance->keyboard[103])
		{
			this->minusSpeed();
		}
		if (Engine::Instance->keyboard['r'])
		{
			this->restart();
		}

		this->displayTexts();



		this->checkCheckPoint();


	}
}

void Car::displayTexts(){
	if (Text::getTextByName("speed") == NULL)
		Engine::Instance->activeLevel->addGraphicalObject(new Text(glm::vec3(10, 10, 0), 0, "speed", "wartosc"));
	char* buf = (char*) malloc(10);
	itoa(this->speed, buf, 10);
	Text::getTextByName("speed")->changeValue("Speed: " + std::string(buf));
	free(buf);


	if (Text::getTextByName("rpm") == NULL)
		Engine::Instance->activeLevel->addGraphicalObject(new Text(glm::vec3(10, 30, 0), 0, "rpm", "wartosc"));
	char* buf2 = (char*) malloc(10);
	itoa(this->rpm, buf2, 10);
	Text::getTextByName("rpm")->changeValue("RPM: " + std::string(buf2));
	free(buf2);
	
	if (Text::getTextByName("gear") == NULL)
		Engine::Instance->activeLevel->addGraphicalObject(new Text(glm::vec3(10, 50, 0), 0, "gear", "wartosc"));
	char* buf3 = (char*) malloc(10);
	itoa((int)(this->gear), buf3, 10);
	Text::getTextByName("gear")->changeValue("Gear: " + std::string(buf3));
	free(buf3);
	
	if (Text::getTextByName("bestTime") == NULL)
		Engine::Instance->activeLevel->addGraphicalObject(new Text(glm::vec3(Engine::Instance->resolution.Width-150, 30, 0), 0, "bestTime", "wartosc"));
	char* buf4 = (char*) malloc(10);
	itoa((int) (this->bestTime), buf4, 10);
	Text::getTextByName("bestTime")->changeValue("BestTime: " + std::string(buf4)+"s");
	free(buf4);
	
	if (Text::getTextByName("Time") == NULL)
		Engine::Instance->activeLevel->addGraphicalObject(new Text(glm::vec3(Engine::Instance->resolution.Width - 150, 10, 0), 0, "Time", "wartosc"));
	char* buf5 = (char*) malloc(10);
	itoa(((int) (clock() - this->startTime)/1000), buf5, 10);
	Text::getTextByName("Time")->changeValue("Time: " + std::string(buf5)+"s");
	free(buf5);
}

void Car::move(){


	glm::vec4 vec = this->iModelMat * glm::vec4(this->directionPoint, 1);
	glm::vec3 t = (glm::vec3(vec) - this->position)*(float) (this->speed / 100);

	glm::mat4 ModelMatrix;
	ModelMatrix = glm::translate(glm::mat4(1.0f), (this->position+t));
	ModelMatrix = glm::rotate(ModelMatrix, (float) (-1.57079633f*this->rotationAxis.x), glm::vec3(1, 0, 0)); //Macierz modelu
	ModelMatrix = glm::rotate(ModelMatrix, (float) (-1.57079633f*this->rotationAxis.y), glm::vec3(0, 1, 0)); //Macierz modelu
	ModelMatrix = glm::rotate(ModelMatrix, (float) (-1.57079633f*this->rotationAxis.z), glm::vec3(0, 0, 1)); //Macierz modelu


	for each (glm::vec3 var in this->colisionPoint)
	{
		glm::vec4 vec = this->iModelMat * glm::vec4(var, 1);
		glm::vec3 t = glm::vec3(vec);

		glm::vec4 vec2 = ModelMatrix * glm::vec4(var, 1);
		glm::vec3 t2 = glm::vec3(vec2);

		glm::vec3* tmp1 = new glm::vec3(0, 0, 0);
		glm::vec3* tmp2 = new glm::vec3(0,0,0);

		if (Structure::Colision(tmp1, tmp2, t, t2))
		{

			if (this->gear > 0){
				if (this->colisionPoint[0] == var){ // kolizja lewy przode
					if (this->turn(true))
					{
						this->speed = 0.995 * this->speed;
						this->move();
						return;
					}
					else
					{
						this->speed = 0;
						return;
					}
				}
				if (this->colisionPoint[1] == var){// kolizja srodek przode
					this->speed = -1 / 5 * this->speed;
					this->move();
					return;

				}
				if (this->colisionPoint[2] == var){// kolizja prawy przode
					if (this->turn(false))
					{
						this->speed = 0.995 * this->speed;
						this->move();
						return;
					}
					else
					{
						this->speed = 0;
						return;
					}
				}
			}

			if (this->gear == 0){
				if (this->colisionPoint[3] == var){// kolizja lewy tyl
					if (this->turn(false))
					{
						this->speed = 0.995 * this->speed;
						this->move();
						return;
					}
					else
					{
						this->speed = 0;
						return;
					}
				}
				if (this->colisionPoint[4] == var){// kolizja srodek tyl
					this->speed = -1 / 3 * this->speed;
					this->move();
					return;
				}
				if (this->colisionPoint[5] == var){// kolizja prawy tyl
					if (this->turn(true))
					{
						this->speed = 0.995 * this->speed;
						this->move();
						return;
					}
					else
					{
						this->speed = 0;
						return;
					}
				}
			}
		}
	}
	

	this->position += t;
	this->iModelMat = ModelMatrix;
	Camera::ActiveCamera->position = this->position;

}


void Car::restart(){

	this->checkPointStatus[0] = false;
	this->checkPointStatus[1] = false;
	this->checkPointStatus[2] = false;
	this->checkPointStatus[3] = false;

	this->rotationAxis = glm::vec3(1, 0, 2);
	this->position = glm::vec3(210, -4.5, 175);
	this->speed = 0;
	this->rpm = 0;
	this->gear = 1;
	this->gearup = false;
	this->geardown = false;
	this->startTime = clock();

}


void Car::checkCheckPoint()
{
	for (int i = 0; i < 4; i++)
	{
		if (!this->checkPointStatus[i]){

			Engine::Instance->activeLevel->kulki.push_back(new kulka(Engine::Instance->activeLevel->checkPoints[i].position,new StructureShader()));
			if (Engine::Instance->activeLevel->checkPoints[i].check(this->position))
			{
				this->checkPointStatus[i] = true;
				if (i == 3){

					if (this->bestTime==0)this->bestTime = this->startTime - clock();
					if (this->bestTime>this->startTime - clock())this->bestTime = this->startTime - clock();
					this->restart();
				}
			}
			else return;
		}

	}
}