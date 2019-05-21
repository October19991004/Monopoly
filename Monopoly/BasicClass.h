#pragma once
struct Position {
	int x;
	int y;

	Position(int in_x, int in_y) {
		this->x = in_x;
		this->y = in_y;
	}
	Position() :x(0), y(0) {}

	bool operator==(Position pos) {
		if (this->x == pos.x && this->y == pos.y)return true;
		return false;
	}


};
enum Color
{
	Black=0,
	DarkBlue=1,	
	DarkGreen = 2,
	DarkCyan=3,
	DarkMagenta=5,	
	DarkRed=4,	
	DarkYellow=6,	
	Gray=7,	
	DarkGray = 8,
	Blue = 9,
	Green=10,
	Cyan = 11,
	Red = 12,
	Magenta=13,	
	Yellow = 14,
	White=15	
	
};
