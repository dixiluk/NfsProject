#include "Engine.h"
#include "Camera.h"
#include "DynamicObject.h"
#include "Car.h"



Engine* Engine::Instance = nullptr;


Engine::Engine(Resolution resolution)
{
	this->resolution = resolution;
	this->pause = false;
}


Engine::~Engine()
{
}

void Engine::Init(int argc, char * argv[])						//inicjacja parametrow OpenGl i tworzenie okna
{

	for (int i = 0; i < 255; i++){
		Instance->keyboard[i]=false;
	}
	Instance->gearboxUpKey = 49;
	Instance->gearboxDownKey = 50;
	Instance->moveCameraKey = 109;



	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(Instance->resolution.Width, Instance->resolution.Height);

	glutCreateWindow(WINDOW_TITLE);
	//glutFullScreen();
	glutKeyboardFunc(Engine::KeyboardFunc);
	glutKeyboardUpFunc(Engine::KeyboardUpFunc);
	glutSpecialFunc(Engine::SpecialFunc);
	glutSpecialUpFunc(Engine::SpecialUpFunc);
	glutDisplayFunc(Engine::DisplayFunc);
	glutPassiveMotionFunc(Engine::PassiveMotionFunc);
	glutReshapeFunc(Engine::ReshapeFunc);
	glutIdleFunc(Engine::DisplayFunc);
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	int major = 0, minor = 0;
	const char * version = (char *)glGetString(GL_VERSION);
	if (sscanf(version, "%d.%d", &major, &minor) != 2)
	{
		printf("Bledny format wersji OpenGL\n");

	}
}

void Engine::DisplayFunc()		//glowna petla
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	Engine::UpdatePass();

	Engine::RenderPass();

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void Engine::ReshapeFunc(int width, int height)	//funkcja zmiany rozmiaru okna
{
	Instance->resolution.Height = height;
	Instance->resolution.Width = width;
	glViewport(0, 0, width, height);
	Camera::ActiveCamera->setAspectRatio((GLdouble) width / height);
}

void Engine::KeyboardFunc(unsigned char key, int x, int y)
{
	Engine::Instance->keyboard[key] = true;
	if (key == 'p'){
		if (Engine::Instance->pause)
		{
			Engine::Instance->pause = false;
			Car::ControledCar->startTime +=  clock() - Engine::Instance->pausetime;

		}
		else
		{
			Engine::Instance->pause = true;
			Engine::Instance->pausetime = clock();
		}
	}

}

void Engine::KeyboardUpFunc(unsigned char key, int x, int y)
{
	Engine::Instance->keyboard[key] = false;

}

void Engine::SpecialFunc(int key, int x, int y)
{
	Engine::Instance->keyboard[key] = true;

}

void Engine::SpecialUpFunc(int key, int x, int y)
{
	Engine::Instance->keyboard[key] = false;

}


void Engine::PassiveMotionFunc(int x, int y){
	Camera::CameraMotion(x, y);
}

void Engine::UpdatePass()	//wykonywanie wszystkich obliczen
{
	Camera::ActiveCamera->setupCamera();

	for (GraphicalObject* obj : Engine::Instance->activeLevel->graphicalObjects){
		obj->compute();
	}
}


void Engine::RenderPass(){	//funkcja wykonania rysowania wszystich elementow
	glClearColor(0.2, 0.2, 0.2, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (GraphicalObject* obj : Engine::Instance->activeLevel->graphicalObjects){
		obj->draw();
	}

}