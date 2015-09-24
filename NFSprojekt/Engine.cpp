#include "Engine.h"
#include "Camera.h"
#include "DynamicObject.h"


Engine* Engine::Instance = nullptr;


Engine::Engine(Resolution resolution)
{
	this->resolution = resolution;
}


Engine::~Engine()
{
}

void Engine::Init(int argc, char * argv[])						//inicjacja parametrow OpenGl i tworzenie okna
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(Instance->resolution.Width, Instance->resolution.Height);

	glutCreateWindow(WINDOW_TITLE);
	//glutFullScreen();
	glutKeyboardFunc(Engine::KeyboardFunc);
	glutKeyboardUpFunc(Engine::KeyboardUpFunc);
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
int tmp=0;
void Engine::DisplayFunc()		//glowna petla
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	Engine::UpdatePass();

	Engine::RenderPass();
	tmp++;
	//printf("%d\n",tmp);

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void Engine::ReshapeFunc(int width, int height)	//funkcja zmiany rozmiaru okna
{
	return;
	Instance->resolution.Height = height;
	Instance->resolution.Width = width;
	glViewport(0, 0, width, height);
	Camera::ActiveCamera->setAspectRatio((GLdouble) width / height);
}

void Engine::KeyboardFunc(unsigned char key, int x, int y)
{

}

void Engine::KeyboardUpFunc(unsigned char key, int x, int y)
{

}

void Engine::PassiveMotionFunc(int x, int y){
	Camera::CameraMotion(x, y);
}

void Engine::UpdatePass()	//wykonywanie wszystkich obliczen
{

}


void Engine::RenderPass(){	//funkcja wykonania rysowania wszystich elementow
	glClearColor(0.2, 0.2, 0.2, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (GraphicalObject* obj : Engine::Instance->activeScene->graphicalObjects){
		obj->draw();
	}
}