#pragma once
#include "Environment.h"
#include "Level.h"


class Engine
{
public:
	struct Resolution{
	public:
		Resolution(){}
		Resolution(int Width, int Height){
			this->Width = Width;
			this->Height = Height;
		}
		int Width, Height;

	} resolution;

	std::list<Level*> scenes;
	Level* activeLevel;

	PFNGLWINDOWPOS2IPROC glWindowPos2i;

	static Engine* Instance;

	bool keyboard[255];
	bool pause;
	short gearboxUpKey;
	short gearboxDownKey;
	short moveCameraKey;

	Engine(Resolution resolution);
	~Engine();
	static void Init(int argc, char * argv[]);
	static void DisplayFunc();
	static void ReshapeFunc(int width, int height);
	static void KeyboardFunc(unsigned char key, int x, int y);
	static void KeyboardUpFunc(unsigned char key, int x, int y);
	static void SpecialFunc(int key, int x, int y);
	static void SpecialUpFunc(int key, int x, int y);
	static void PassiveMotionFunc(int x, int y);
	static void UpdatePass();
	static void RenderPass();
	
	
};