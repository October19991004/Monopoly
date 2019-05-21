#pragma once
#include"BasicClass.h"
#include "Display.h"
#include "Object.h"
#include<iostream>
#include<Windows.h>
#include<string>
class Canvas : public Object
{
public:
	//canvas's position in console
	Position pos = Position(0,0);

	//cursor's position in canvas
	Position cursorPos = Position(0,0);

	//canva's size(draw function is depend on it)
	size_t w = 1, h = 1;

	//(if (canSee) draw)
	bool canSee = true;
	void show();
	void hide();


	//output text content
	virtual void draw();
	virtual void drawCursor();
	void clean();
	//diffient canvas using diffient key event
	virtual int keyEvent(int keyValue) { return 0; };

	Color ForeColor = Color::White;
	Color BackColor = Color::Black;

	std::wstring text = L"";
	
	


	Canvas();
	~Canvas();
};

