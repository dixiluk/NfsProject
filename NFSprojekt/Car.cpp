#include "Car.h"
#include "Engine.h"
#include "Structure.h"
#include "Camera.h"
#include "kulka.h"

#include "StructureShader.h"

#define addSpeedPerFrame 0.25
#define minusSpeedPerFrame 1
#define rotationPowerFrame 0.25
#define carLength 3
#define carWidth 0.8

std::list<Car*> Car::Cars;

Car* Car::ControledCar=0;
Car::Car(glm::vec3 position, Model* model, Shader* shader) : DynamicObject(position, shader)
{
	this->colisionPoint.push_back(glm::vec3(carWidth/2.0, -carLength/2.0, 3.0));
	this->colisionPoint.push_back(glm::vec3(0, -carLength/2.0, 3.0));
	this->colisionPoint.push_back(glm::vec3(-carWidth/2.0, -carLength/2.0, 3.0));
	this->colisionPoint.push_back(glm::vec3(carWidth/2.0, carLength/2, 3.0));
	this->colisionPoint.push_back(glm::vec3(0, carLength/2.0, 3.0));
	this->colisionPoint.push_back(glm::vec3(-carWidth/2.0, carLength/2.0, 3.0));
	this->model = model;
	Cars.push_back(this);
	this->speed = 0;
	this->rpm = 0;
	this->gear = 1;
	this->gearup = false;
	this->geardown = false;
	this->maxGear = 6;
	this->rotationAxis = glm::vec3( 1, 0, 0);
	this->speedAt6kRps[0] = -30;
	this->speedAt6kRps[1] = 45;
	this->speedAt6kRps[2] = 80;
	this->speedAt6kRps[3] = 120;
	this->speedAt6kRps[4] = 150;
	this->speedAt6kRps[5] = 180;
	this->speedAt6kRps[6] = 220;
	ControledCar = this;
	this->directionPoint = glm::vec3( 0,-1,0 );
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
		if (this->gearup==false)
		{
			this->gearup = true;

			if(this->speed==0 || this->gear>0)
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
			
			if (this->gear == 1 && this->speed==0) {
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
	if (this->speed > 30) {
		if (site)
			this->rotationAxis.z += (float)(0.006 * (-log(this->speed - 20) + 7));
		else
			this->rotationAxis.z -= (float)(0.006 * (-log(this->speed - 20) + 7));

	}
	else
	{
		if (site) 
		{
			this->rotationAxis.z += (float)(0.006 * log(this->speed + 1)*1.4);
		}
		else
		{
			this->rotationAxis.z -= (float)(0.006 * log(this->speed + 1)*1.4);

		}
	}
}




void Car::compute()
{
	if (ControledCar==this){
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
		this->Colision();
		this->move();


	}
}


void Car::move(){
	glm::vec4 vec = this->iModelMat * glm::vec4(this->directionPoint,1);
	glm::vec3 t = glm::vec3(vec);
	//Engine::Instance->activeScene->kulki.push_back(new kulka(t, new StructureShader()));


	for each (glm::vec3 var in this->colisionPoint)
	{
		glm::vec4 vec = this->iModelMat * glm::vec4(var, 1);
		glm::vec3 t = glm::vec3(vec);
		//Engine::Instance->activeScene->kulki.push_back(new kulka(t, new StructureShader()));
	}




	this->position += (t-this->position)*(float)(this->speed/100);
	Camera::ActiveCamera->position = this->position;

}

void Car::Colision(){
	for each (Structure* item in Structure::Structures)
	{
		if (item->isColision){

			for each (ModelObject* item2 in item->model->objects){
				{
					glm::vec3* tmp1 = new glm::vec3(0, 0, 0);
					glm::vec3* tmp2 = new glm::vec3(0, 0, 0);


					if (this->PointToMesh(this->position, glm::vec3(this->position.x, this->position.y, this->position.z - 0.5), item2->v, item2->verticesCount * 3, item->iModelMat, tmp1, tmp2))
					{
						this->speed = 0;
						printf("found colision");
					}
				}
			}
		}
	}
}

bool Car::rayIntersectsTriangle(glm::vec3 p, glm::vec3 d, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, float& lenOnLine)
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

bool Car::PointToMesh(glm::vec3 P1, glm::vec3 P2, float* mesh, int meshSize, glm::mat4 ModelMatrix,
	glm::vec3* intersectionPoint, glm::vec3* surfaceVector)
{
	glm::vec3 dir;
	glm::vec3 p1, p2, p3;
	StructureShader *tmp = new StructureShader();
	float len;

	//Engine::Instance->activeScene->kulki.push_back(new kulka(glm::vec3(0, 1, 2), tmp));
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

