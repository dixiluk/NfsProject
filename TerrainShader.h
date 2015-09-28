#pragma once
#include "Shader.h"
#include "Texture.h"
class TerrainShader :
	public Shader
{
public:
	TerrainShader();
	~TerrainShader();
	
	GLuint modelMatrixLink;
	GLuint textureLink[4];
	GLuint textureMapLink;
	GLuint mvpLink;

	void onDraw(void* ptr);
	void onPrepare(void* ptr);
};

