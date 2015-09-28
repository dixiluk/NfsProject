#include "Environment.h"
#include "Engine.h"
#include "Structure.h"
#include "Car.h"
#include "Environment.h"
#include "Camera.h"
#include "ModelObject.h"
#include "StructureShader.h"
#include "CarShader.h"
#include "kulka.h"
#include "Terrain.h"
#include "Text.h"
#include "CheckPoint.h"

int main(int argc, char * argv[])
{
	Engine::Instance = new Engine(Engine::Resolution(1440, 900));

	Engine::Init(argc, argv);

	Level* scene = new Level();
	kulka::kulkam = new Model("kulka.fbx");
	Engine::Instance->activeLevel = (Level*) scene;
	Camera *camera = new Camera(glm::vec3(210, -4.5, 175));

	scene->addGraphicalObject(new Car(glm::vec3(0, 0, 0), new Model("premier.fbx"), new CarShader()));

	scene->addGraphicalObject(new Terrain(glm::vec3(0, 0, 0), new Model("RacingGameLevel.fbx"),"LevelTextures/Channel.png", "LevelTextures/grass.png", "LevelTextures/grass2.png", "LevelTextures/rock.png", "LevelTextures/rock.png"));
	scene->addGraphicalObject(new Structure(glm::vec3(0, 0, 0), new Model("RacingGameLevelCollision.fbx"), new StructureShader(), true));


	camera->setActive();
	glutMainLoop();

	return 0;
}