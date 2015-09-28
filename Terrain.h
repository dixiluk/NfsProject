#pragma once
#include "StaticObject.h"

class Terrain :
	public StaticObject
{
	friend class TerrainShader;
private:
	Texture* textureMap;
	Texture* texture[4];
public:
	static Shader* TerrainShaderInstance;
	Terrain(glm::vec3 position, Model* model, char* textureMap, char* texture1, char* texture2, char* texture3, char* texture4);
	glm::mat4 iModelMat;
	void draw();
	~Terrain();
};

