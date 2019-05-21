#pragma once
#include<Windows.h>
#include<iostream>
#include<string>
class Display
{
public:
	static Display _display;
	CHAR_INFO* outputBuffer;
	void DrawBuffer();
	COORD BufferSize = {40,25};
	void printText(std::wstring text, int x = 0, int y = 0, int w = 100, int h = 100, WORD attr = 0x00F0);
	inline int index(int x, int y);

	Display();
	~Display();
};

