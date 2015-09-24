#include "StructureShader.h"
#include "Environment.h"
#include "Engine.h"
#include "Camera.h"
#include "Structure.h"


StructureShader::StructureShader() : Shader("StructureShader.vs", "StructureShader.ps")
{
	this->textureLink = glGetUniformLocation(this->program, "DiffuseMap");
	this->mvpLink = glGetUniformLocation(this->program, "MVP");
}


StructureShader::~StructureShader()
{
}

void StructureShader::onPrepare(void* ptr){

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE);
	glEnable(GL_TEXTURE0);

	glUseProgram(program);

	Structure* object = (Structure*) ptr;

	glm::mat4 ModelMatrix;

	ModelMatrix = glm::translate(glm::mat4(1.0f), object->position);
	ModelMatrix = glm::rotate(ModelMatrix, -1.57079633f, glm::vec3(1, 0, 0));

	glm::mat4 ModelViewProjMatrix = Camera::ActiveCamera->projectionMatrix *
		Camera::ActiveCamera->viewMatrix * ModelMatrix;

	glUniformMatrix4fv(this->mvpLink, 1, GL_FALSE, glm::value_ptr(ModelViewProjMatrix));
	
}

void StructureShader::onDraw(void* ptr){
	ModelObject* obj = (ModelObject*) ptr;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, obj->diffuseMap->id);
	glUniform1i(this->textureLink, 0);
}