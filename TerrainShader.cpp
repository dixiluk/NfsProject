#include "TerrainShader.h"
#include "StructureShader.h"
#include "Structure.h"
#include "Camera.h"
#include "Terrain.h"

TerrainShader::TerrainShader() : Shader("TerrainShader.vs", "TerrainShader.ps")
{
	this->mvpLink = glGetUniformLocation(this->program, "MVP");
	this->modelMatrixLink = glGetUniformLocation(this->program, "ModelMatrix");
	this->textureMapLink = glGetUniformLocation(this->program, "TextureMap");
	for (int i = 0; i < 4; i++){
		char *str = (char*) malloc(10);
		itoa(i, str, 10);
		this->textureLink[i] = glGetUniformLocation(this->program, (std::string("Texture[") + std::string(str) + "]").c_str());
		free(str);
	}
}

TerrainShader::~TerrainShader()
{
}

void TerrainShader::onPrepare(void* ptr)
{
	glUseProgram(program);

	Terrain* object = (Terrain*) ptr;

	glm::mat4 ModelMatrix;
	ModelMatrix = glm::translate(glm::mat4(1.0f), object->position);
	ModelMatrix = glm::rotate(ModelMatrix, (float) (-1.57079633f), glm::vec3(1, 0, 0)); //Macierz modelu

	object->iModelMat = ModelMatrix;

	glm::mat4 ModelViewProjMatrix =
		Camera::ActiveCamera->projectionMatrix *
		Camera::ActiveCamera->viewMatrix *
		ModelMatrix; // MVP

	// Przesy³anie macierza MVP do programu shadera
	glUniformMatrix4fv(this->mvpLink, 1, GL_FALSE, glm::value_ptr(ModelViewProjMatrix));
	// Przesy³anie macierza modelu do programu shadera
	glUniformMatrix3fv(this->modelMatrixLink, 1, GL_FALSE, glm::value_ptr(ModelMatrix));
	glEnable(GL_TEXTURE);
	glEnable(GL_TEXTURE0);
	glEnable(GL_TEXTURE1);
	glEnable(GL_TEXTURE2);

	// Przesy³anie mapy tekstur do programu shadera
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, object->textureMap->id);
	glUniform1i(this->textureMapLink, 0);

	for (int i = 1; i <= 4; i++){
		// Przesy³anie tekstury do programu shadera
		glActiveTexture(GL_TEXTURE0+i);
		glBindTexture(GL_TEXTURE_2D, object->texture[i-1]->id);
		glUniform1i(this->textureLink[i-1], i);
	}
}

void TerrainShader::onDraw(void* ptr){}