#pragma once
#include "Object.h"
#include "Canvas.h"
#include "ExampleCanvas.h"
#include "BasicClass.h"
#include "KeyBoard.h"
#include "Display.h"
#include <Windows.h>
#include <list>
#include <chrono>
#include <fstream>
#include <sstream>
#include <direct.h>

class Mananger
{
public:
	static Mananger* _Mananger;
	Mananger();
	~Mananger();
	std::list<Object*> updateLayer;
	std::list<Canvas*> displayLayer;
	
	void gameStart();

private:
	void initialize();
	void loop();
	void Update();
	void Display();
};

