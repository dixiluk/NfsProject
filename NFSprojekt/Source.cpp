#include "Environment.h"
#include "Engine.h"
#include "Structure.h"
#include "Car.h"
#include "Environment.h"
#include "Camera.h"
#include "ModelObject.h"
#include "kulka.h"
#include "StructureShader.h"

int main(int argc, char * argv[])
{
	Engine::Instance = new Engine(Engine::Resolution(1440, 900));

	Engine::Init(argc, argv);

	Scene* scene = new Scene();
	kulka::kulkam = new Model("kulka.fbx");

	//scene->addGraphicalObject(new Car(glm::vec3(0, 0, 0), new Model("premier.fbx"), new StructureShader()));
	scene->addGraphicalObject(new Structure(glm::vec3(0, 0, 0), new Model("RacingGameLevel.fbx"), new StructureShader(), false));
	scene->addGraphicalObject(new Structure(glm::vec3(0, 0, 0), new Model("RacingGameLevelCollision.fbx"), new StructureShader(), true));
	scene->addGraphicalObject(new Car(glm::vec3(10, -1, -7), new Model("premier.fbx"), new StructureShader()));
	Engine::Instance->activeScene = (Scene*) scene;
	Camera *camera = new Camera(glm::vec3(5,3,-6));
	camera->setActive();
	camera->setDirectionToPosition(glm::vec3(10, -1.5, -6));
	glutMainLoop();

	return 0;
}