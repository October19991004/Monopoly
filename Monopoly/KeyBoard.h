#pragma once
#include <Windows.h>
class KeyBoard
{
public:
	static KeyBoard keyBoard;

	KeyBoard();
	~KeyBoard();
	bool anyKeyPress;
	bool IsKeyDown(short);
	bool IsKeyPress(short);
	bool IsKeyUp(short);
	unsigned short getKeyPressTime(short);
	bool* const getKeyPressList();
	bool* const getKeyDownList();
	bool* const getKeyUpList();
	unsigned short* const getKeyPressTimeList();
	void keyUpdate();
private:
	bool keyDown[256];
	bool keyUp[256];
	bool keyPress[256];
	unsigned short keyPressTime[256];
};

