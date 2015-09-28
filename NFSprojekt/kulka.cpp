#include "kulka.h"
#include "StructureShader.h"
#include "Engine.h"

Model* kulka::kulkam = 0;
int kulka::limit = 5;
StructureShader *tmp = 0;
kulka::kulka(glm::vec3 position, Shader* shader) : DynamicObject(position, shader)
{
	this->model = this->kulkam;
	
}


kulka::~kulka()
{
}
void kulka::compute(){}

void kulka::draw()
{
	this->shader->onPrepare(this);

	for (std::list<ModelObject*>::iterator it = this->model->objects.begin();
		it != this->model->objects.end(); it++){		
		ModelObject* obj = *it;
		this->shader->onDraw(obj);
		glBindVertexArray(obj->arrayBuffer);
		glDrawElements(GL_TRIANGLES, obj->verticesCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}



void kulka::tworz(glm::vec3 poz){
	if (kulka::limit > 0){
		kulka::limit--;
		if(tmp==NULL) tmp = new StructureShader();
		//Engine::Instance->activeLevel->kulki.push_back(new kulka(poz, tmp));
	}

}