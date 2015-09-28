#pragma once
#include "Shader.h"
class StructureShader :
	public Shader
{
private:
	GLuint modelMatrixLink;
	GLuint textureLink;
	GLuint mvpLink;
public:
	void onPrepare(void* ptr);
	void onDraw(void* ptr);
	StructureShader();
	~StructureShader();
};
