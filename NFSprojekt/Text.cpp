#include "Text.h"


Text::Text(glm::vec3 position, Shader* shader, std::string name, std::string value) : GraphicalObject(position, shader)
{
	this->name = name;
	this->value = value;
	allTexts.push_back(this);
}


Text::~Text()
{
}

void Text::compute()
{
}

void Text::draw()
{
	glWindowPos2i(position.x, position.y);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)value.c_str());
}

Text* Text::getTextByName(std::string name)
{
	for (std::list<Text*>::iterator it = this->allTexts.begin();
		it != this->allTexts.end(); it++){
		if ((*it)->name == name)
			return *it;
	}
	return NULL;
}