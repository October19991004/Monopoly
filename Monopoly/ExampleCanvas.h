#pragma once
#include "Canvas.h"
#include "KeyBoard.h"
#include <sstream>
class ExampleCanvas : public Canvas
{
public:
	int* externVariable = NULL;//�i�H�Ϋ��Ч�~�����ܼƧ˶i��
	void start() {
		//�|�bMananger��Initialize����w�g�ŧi�X�Ӫ�Object��start���]�L�@��
		//�p�G�n�ʺA���ͥX�ӥi�H��Constructor call �άO�����bConstructor��ӳ]�w���]�w�n

		this->text =
			L"abcde"
			L"�@�G�T�|��"
			L"��������K";

		w = 5;
		h = 3;
		ForeColor = Red; BackColor = White;
	};

	void loop() {
		//�C�@��Update���|�]�@���A�p�G�n��keyBoard�n�O�oinclude
		if (KeyBoard::keyBoard.IsKeyDown(VK_RETURN)) {
			flag = !flag;
		}
		if (KeyBoard::keyBoard.IsKeyUp(VK_DELETE)) {
			//�o�˥i�H��ۤv�R��(�ʺA�ͦ��B�R��)
			delete this;
		}
		if (KeyBoard::keyBoard.IsKeyPress(VK_ESCAPE)) {
			if (canSee) hide();
			else show();
		}
	};

	void draw() {
		//�i�H�ۤv����draw���禡�A�S���g���ܴN�O�ӵ�Canvas.cpp�̭�����(�N�O���e���˧�Ҧ��F��Ӫ��e�L�X��)
		//Display::_display.outputBuffer[] ���u���@���A��Display::_display.index(x, y)��2D index���1D�W
		//Attribute���榡�N�O (�I���� << 4 ) | (�r�C��) �ϥ��N�O�@��16bit�����
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

	//Constructor �@�w�n�O�o�[�W�~��Canvas��Constructor���M�|�S�k�ʧ@
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

