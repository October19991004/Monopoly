#include "Display.h"

Display Display::_display;


void Display::DrawBuffer()
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;

	SetConsoleCursorInfo(output, &info);
	unsigned long dummy;

	COORD drawCursorPos;
	for (short x = 0; x < BufferSize.X; x++) {
		for (short y = 0; y < BufferSize.Y; y++) {
			if (outputBuffer[index(x, y)].Char.UnicodeChar <= 128 ) {
				FillConsoleOutputCharacterW(output, outputBuffer[index(x, y)].Char.UnicodeChar, 1, COORD{ x * 2,y }, &dummy);
				
			}
			else if ((outputBuffer[index(x, y)].Char.UnicodeChar <= 0x257F && outputBuffer[index(x, y)].Char.UnicodeChar >= 0x2500)) {
				//SetConsoleCursorPosition(output, COORD{x*2,y});
				//std::wcout << outputBuffer[index(x, y)].Char.UnicodeChar;
				FillConsoleOutputCharacterW(output, outputBuffer[index(x, y)].Char.UnicodeChar, 1, COORD{ x * 2,y }, &dummy);
			}
			else {
				FillConsoleOutputCharacterW(output, outputBuffer[index(x, y)].Char.UnicodeChar, 2, COORD{ x * 2,y }, &dummy);
			}
			FillConsoleOutputAttribute(output, outputBuffer[index(x, y)].Attributes, 2, COORD{ x * 2, y }, &dummy);
		}
	}
	drawCursorPos.X = 0; drawCursorPos.Y = 0;
	SetConsoleCursorPosition(output, drawCursorPos);


	for (int x = 0; x < BufferSize.X * BufferSize.Y; x++) {
		
		CHAR_INFO buf; buf.Char.UnicodeChar = L'¡@'; buf.Attributes = 0x0000;
		outputBuffer[x] = buf;
	}
}

void Display::printText(std::wstring text, int x, int y, int w, int h, WORD attr)
{
	int tmpy = y;
	for (int i = 0; i < text.length(); i++) {
		if (i % w == 0 && i != 0) {
			y++;
			if (y > tmpy + h)return;
		}
		CHAR_INFO buf; buf.Char.UnicodeChar = text[i]; buf.Attributes = attr;
		outputBuffer[index(x + (i % w), y)] = buf;
	}

}

inline int Display::index(int x, int y)
{
	return x + y * BufferSize.X;
}

Display::Display()
{
	outputBuffer = new CHAR_INFO[BufferSize.X * BufferSize.Y];

	for (int i = 0; i < BufferSize.X * BufferSize.Y; i++) {
		outputBuffer[i].Attributes = 0x0000;
		outputBuffer[i].Char.UnicodeChar = L'¡@';
	}
	
	std::wcout.imbue(std::locale(""));
	setlocale(LC_ALL,"");
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}


Display::~Display()
{
	delete[] outputBuffer;
}
