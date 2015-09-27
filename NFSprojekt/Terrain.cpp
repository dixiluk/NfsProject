#include "Terrain.h"
#include "TerrainShader.h"

Shader* Terrain::TerrainShaderInstance = 0;

Terrain::Terrain(glm::vec3 position, Model* model, char* textureMap, char* texture1, char* texture2, char* texture3, char* texture4) : StaticObject(position, shader)
{
	if (TerrainShaderInstance == 0)
		TerrainShaderInstance = new TerrainShader();
	this->shader = TerrainShaderInstance;
	this->model = model;

	this->textureMap = new Texture((std::string(TEXTURES_SUBDIR) + std::string(textureMap)).c_str());

	this->texture[0] = new Texture((std::string(TEXTURES_SUBDIR) + std::string(texture1)).c_str());
	this->texture[1] = new Texture((std::string(TEXTURES_SUBDIR) + std::string(texture2)).c_str());
	this->texture[2] = new Texture((std::string(TEXTURES_SUBDIR) + std::string(texture3)).c_str());
	this->texture[3] = new Texture((std::string(TEXTURES_SUBDIR) + std::string(texture4)).c_str());
}


Terrain::~Terrain()
{
}

void Terrain::draw(){
	this->shader->onPrepare(this);

	for (std::list<ModelObject*>::iterator it = this->model->objects.begin();
		it != this->model->objects.end(); it++)
	{
		ModelObject* obj = *it;

		this->shader->onDraw(obj);

		glBindVertexArray(obj->arrayBuffer);
		glDrawElements(GL_TRIANGLES, obj->verticesCount, GL_UNSIGNED_INT, 0); //Rysowanie obiektu z bufora wierzcho³ków
		glBindVertexArray(0);
	}

}
