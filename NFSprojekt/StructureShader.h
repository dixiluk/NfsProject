#pragma once
#include "Shader.h"
class StructureShader :
	public Shader
{
private:
	GLuint pointLightCountLink, pointLightMatrixArrayLink;
	GLuint normalMatrixLink;
	GLuint textureLink;
	GLuint switchLink;
	GLuint mvpLink;

	int switchVal;
public:
	void onPrepare(void* ptr);
	void onDraw(void* ptr);
	StructureShader();
	~StructureShader();
};

