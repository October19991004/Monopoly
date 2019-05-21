
#include <cstdlib>
#include<iostream>
#include"Mananger.h"
using namespace std;
int main() {
	//Mananger mananger = Mananger();
	Mananger::_Mananger = new Mananger();
	Mananger::_Mananger->gameStart();
	system("pause");
	return 0;
}