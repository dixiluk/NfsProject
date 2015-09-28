#include "StructureShader.h"
#include "Structure.h"
#include "Camera.h"

StructureShader::StructureShader()
	: Shader("StructureShader.vs", "StructureShader.ps")
{
	// Tworzenie połączenia do zmiennych w programie shadera
	this->mvpLink = glGetUniformLocation(this->program, "MVP"); 
	this->modelMatrixLink = glGetUniformLocation(this->program, "ModelMatrix");
	this->textureLink = glGetUniformLocation(this->program, "DiffuseMap");


}


StructureShader::~StructureShader()
{
}

void StructureShader::onPrepare(void* ptr)
{
	glUseProgram(program);

	Structure* object = (Structure*)ptr;
	
	glm::mat4 ModelMatrix;
	ModelMatrix = glm::translate(glm::mat4(1.0f), object->position);
	ModelMatrix = glm::rotate(ModelMatrix, (float) (-1.57079633f)*object->rotationAxis.x, glm::vec3(1, 0, 0)); //Macierz modelu
	ModelMatrix = glm::rotate(ModelMatrix, (float) (-1.57079633f)*object->rotationAxis.y, glm::vec3(0, 1, 0)); //Macierz modelu
	ModelMatrix = glm::rotate(ModelMatrix, (float) (-1.57079633f)*object->rotationAxis.z, glm::vec3(0, 0, 1)); //Macierz modelu
	
	object->iModelMat = ModelMatrix;

	glm::mat4 ModelViewProjMatrix = 
		Camera::ActiveCamera->projectionMatrix *
		Camera::ActiveCamera->viewMatrix *
		ModelMatrix; // MVP
	
	// Przesyłanie macierza MVP do programu shadera
	glUniformMatrix4fv(this->mvpLink, 1, GL_FALSE, glm::value_ptr(ModelViewProjMatrix)); 
	// Przesyłanie macierza modelu do programu shadera
	glUniformMatrix3fv(this->modelMatrixLink, 1, GL_FALSE, glm::value_ptr(ModelMatrix));
}

void StructureShader::onDraw(void* ptr){
	ModelObject* obj = (ModelObject*)ptr;

	glEnable(GL_TEXTURE);
	// Przesyłanie tekstury do programu shadera
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, obj->diffuseMap->id);
	glUniform1i(textureLink, 0);
}