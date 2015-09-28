#pragma once
#include "GraphicalObject.h"
class Text :
	public GraphicalObject
{
public:
	Text(glm::vec3 position, Shader* shader, std::string name, std::string value);
	~Text();

	void compute();
	void draw();
	static Text* getTextByName(std::string name);
	void changeValue(std::string newValue);
private:
	std::string name;
	std::string value;
	static std::list<Text*> AllTexts;

};

