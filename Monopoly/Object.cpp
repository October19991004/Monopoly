#include "Object.h"
#include"Mananger.h"


Object::Object()
{
	Mananger::_Mananger->updateLayer.push_back(this);
}


Object::~Object()
{
	Mananger::_Mananger->updateLayer.remove(this);
}
