#include "Canvas.h"
#include "Mananger.h"
void Canvas::show()
{
	canSee = true;
}
void Canvas::hide()
{
	canSee = false;
}
//drawText to DisplayBuffer
void Canvas::draw()
{
	if (!canSee)return;
	
	for (int h = 0; h < this->h; h++) {
		for (int w = 0; w < this->w; w++) {
			if (this->text.length() > (h * this->w + w)) {
				Display::_display.outputBuffer[Display::_display.index(pos.x + w, pos.y + h)].Attributes = ForeColor | (BackColor << 4);
				Display::_display.outputBuffer[Display::_display.index(pos.x + w, pos.y + h)].Char.UnicodeChar = this->text[h*this->w + w];
			}
		}
	}
	
}
void Canvas::drawCursor()
{
	Display::_display.outputBuffer[Display::_display.index(pos.x +cursorPos.x , pos.y + cursorPos.y)] .Attributes = ForeColor << 4 | (BackColor << 1);
}

void Canvas::clean()
{
	for (int h = 0; h < this->h; h++) {
		for (int w = 0; w < this->w; w++) {
			if (this->text.length() > (h * this->w + w)) {
				CHAR_INFO buf;
				buf.Attributes = 0x0000;//ForeColor | (BackColor << 4);
				buf.Char.UnicodeChar = L'ªÅ';
				Display::_display.outputBuffer[Display::_display.index(pos.x + w, pos.y + h)] = buf;
			}
		}

	}
}

Canvas::Canvas():Object()
{
	Mananger::_Mananger->displayLayer.push_back(this);
}




Canvas::~Canvas()
{
	Mananger::_Mananger->displayLayer.remove(this);
}



