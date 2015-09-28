#include "CarShader.h"
#include "Car.h"
#include "Camera.h"


CarShader::CarShader()
	: Shader("StructureShader.vs", "StructureShader.ps")
{
	// Tworzenie po³¹czenia do zmiennych w programie shadera
	this->mvpLink = glGetUniformLocation(this->program, "MVP");
	this->modelMatrixLink = glGetUniformLocation(this->program, "ModelMatrix");
	this->textureLink = glGetUniformLocation(this->program, "DiffuseMap");


}


CarShader::~CarShader()
{
}


void CarShader::onPrepare(void* ptr)
{
	glUseProgram(program);

	Car* object = (Car*)ptr;

	glm::mat4 ModelMatrix;
	ModelMatrix = glm::translate(glm::mat4(1.0f), object->position);
	ModelMatrix = glm::rotate(ModelMatrix, (float)(-1.57079633f*object->rotationAxis.x), glm::vec3(1, 0, 0)); //Macierz modelu
	ModelMatrix = glm::rotate(ModelMatrix, (float)(-1.57079633f*object->rotationAxis.y), glm::vec3(0, 1, 0)); //Macierz modelu
	ModelMatrix = glm::rotate(ModelMatrix, (float)(-1.57079633f*object->rotationAxis.z), glm::vec3(0, 0, 1)); //Macierz modelu

	object->iModelMat = ModelMatrix;

	glm::mat4 ModelViewProjMatrix =
		Camera::ActiveCamera->projectionMatrix *
		Camera::ActiveCamera->viewMatrix *
		ModelMatrix; // MVP

					 // Przesy³anie macierza MVP do programu shadera
	glUniformMatrix4fv(this->mvpLink, 1, GL_FALSE, glm::value_ptr(ModelViewProjMatrix));
	// Przesy³anie macierza modelu do programu shadera
	glUniformMatrix3fv(this->modelMatrixLink, 1, GL_FALSE, glm::value_ptr(ModelMatrix));
}

void CarShader::onDraw(void* ptr) {
	ModelObject* obj = (ModelObject*)ptr;

	glEnable(GL_TEXTURE);
	// Przesy³anie tekstury do programu shadera
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, obj->diffuseMap->id);
	glUniform1i(textureLink, 0);
}