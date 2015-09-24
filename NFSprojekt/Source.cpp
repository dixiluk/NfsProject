#include "Environment.h"
#include "Engine.h"
#include "Structure.h"
#include "Car.h"
#include "Environment.h"
#include "Camera.h"
#include "ModelObject.h"
#include "StructureShader.h"

int main(int argc, char * argv[])
{
	Engine::Instance = new Engine(Engine::Resolution(1440, 900));

	Engine::Init(argc, argv);

	Scene* scene = new Scene();

	scene->addGraphicalObject(new Car(glm::vec3(0, 0, 0), new Model("Audi-TT.fbx"), new StructureShader()));

	Engine::Instance->activeScene = (Scene*)scene;

	Camera *camera = new Camera(glm::vec3(2,5,2));
	camera->setActive();
	camera->setDirectionToPosition(glm::vec3(0, 0, 0));
	glutMainLoop();

	return 0;
}