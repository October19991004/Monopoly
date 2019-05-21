#pragma once
#include "Canvas.h"
#include "KeyBoard.h"
#include <sstream>
class ExampleCanvas : public Canvas
{
public:
	int* externVariable = NULL;//可以用指標把外面的變數弄進來
	void start() {
		//會在Mananger的Initialize中把已經宣告出來的Object的start都跑過一次
		//如果要動態產生出來可以用Constructor call 或是直接在Constructor把該設定的設定好

		this->text =
			L"abcde"
			L"一二三四五"
			L"●←∮╬Θ";

		w = 5;
		h = 3;
		ForeColor = Red; BackColor = White;
	};

	void loop() {
		//每一次Update都會跑一次，如果要有keyBoard要記得include
		if (KeyBoard::keyBoard.IsKeyDown(VK_RETURN)) {
			flag = !flag;
		}
		if (KeyBoard::keyBoard.IsKeyUp(VK_DELETE)) {
			//這樣可以把自己刪掉(動態生成、刪除)
			delete this;
		}
		if (KeyBoard::keyBoard.IsKeyPress(VK_ESCAPE)) {
			if (canSee) hide();
			else show();
		}
	};

	void draw() {
		//可以自己重載draw的函式，沒有寫的話就是照著Canvas.cpp裡面的做(就是之前那樣把所有東西照長寬印出來)
		//Display::_display.outputBuffer[] 它只有一維，用Display::_display.index(x, y)把2D index轉到1D上
		//Attribute的格式就是 (背景色 << 4 ) | (字顏色) 反正就是一個16bit的資料
		std::wstringstream ss;
		if(externVariable)
		ss << *externVariable;
		if (!canSee)return;

		for (int h = 0; h < this->h; h++) {
			for (int w = 0; w < this->w; w++) {
				if (this->text.length() >(h * this->w + w)) {
					if(flag)
						Display::_display.outputBuffer[Display::_display.index(pos.x + w, pos.y + h)].Attributes = ForeColor | (BackColor << 4);
					else
						Display::_display.outputBuffer[Display::_display.index(pos.x + w, pos.y + h)].Attributes = (ForeColor<< 4) | (BackColor);
					if (ss.str().length() > (h * this->w + w) && externVariable) {
						Display::_display.outputBuffer[Display::_display.index(pos.x + w, pos.y + h)].Char.UnicodeChar = ss.str()[h*this->w + w];
					}
					else {
						Display::_display.outputBuffer[Display::_display.index(pos.x + w, pos.y + h)].Char.UnicodeChar = this->text[h*this->w + w];
					}
					
				}
			}
		}
	}

	//Constructor 一定要記得加上繼承Canvas的Constructor不然會沒法動作
	ExampleCanvas() :Canvas(){
		start(); 
	};
	ExampleCanvas(Position pos_in) :Canvas() {
		pos = Position(pos_in);
		start();
	};
	~ExampleCanvas() {};

private:
	bool flag = false;
};

