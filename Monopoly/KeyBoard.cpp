#include "KeyBoard.h"

KeyBoard KeyBoard::keyBoard = KeyBoard();

void KeyBoard::keyUpdate() {
	anyKeyPress = false;
	for (int i = 0; i < 256; i++) {
		if (GetAsyncKeyState(i)) {
			anyKeyPress = true;

			if (!keyPress[i]) {
				keyDown[i] = 1;
				keyPressTime[i] = 0;
			}
			else {
				keyDown[i] = 0;
			}
			keyUp[i] = 0;
			keyPress[i] = 1;
			keyPressTime[i]++;
		}
		else {
			if (keyPress[i]) {
				keyUp[i] = 1;

			}
			else {
				keyUp[i] = 0;
			}
			keyDown[i] = 0;
			keyPress[i] = 0;
		}
	}


}

KeyBoard::KeyBoard()
{
}


KeyBoard::~KeyBoard()
{
}

bool KeyBoard::IsKeyDown(short keyCode)
{
	if (keyCode > 255 || keyCode < 1) {
		return 0;
	}
	return keyDown[keyCode];
}

bool KeyBoard::IsKeyPress(short keyCode)
{
	if (keyCode > 255 || keyCode < 1) {
		return 0;
	}
	return keyPress[keyCode];
}

bool KeyBoard::IsKeyUp(short keyCode)
{
	if (keyCode > 255 || keyCode < 1) {
		return 0;
	}
	return keyUp[keyCode];
}

unsigned short KeyBoard::getKeyPressTime(short keyCode)
{
	if (keyCode > 255 || keyCode < 1) {
		return 0;
	}
	return keyPressTime[keyCode];
}

bool * const KeyBoard::getKeyPressList()
{
	return keyPress;
}

bool * const KeyBoard::getKeyDownList()
{
	return keyDown;
}

bool * const KeyBoard::getKeyUpList()
{
	return keyUp;
}

unsigned short * const KeyBoard::getKeyPressTimeList()
{
	return keyPressTime;
}
