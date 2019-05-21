#include "Mananger.h"

Mananger* Mananger::_Mananger;


bool exit_b = false;

//Game update variables
int const tickUpdate = 100;
int const displayUpdate = 30;
int UPS = 0, FPS; //UpdatePerSecond,FramePerSecond
time_t gameStartTime;
time_t turnTime, limitTime = 6000;


//可以把一些指標宣告在這，用來接declareObj new出來的東西
Canvas* focus;
ExampleCanvas* EC;



Mananger::Mananger()
{
}

//在這裡宣告元件 (單純為了架構整齊)
void declareObj() {
	EC = new ExampleCanvas(Position(0,0)); //有東西接
	EC->externVariable = &UPS;	//可以利用pointer把外面的變數丟到Class裡面
	new ExampleCanvas(Position(5,5)); //沒東西接(這裡要小心MemoryLeak)
}

void Mananger::gameStart()
{
	declareObj();
	initialize();
	loop();
}
//我的部分，基本不用看
void Mananger::initialize() {
	system("color 00");//setConsoleColor as Black

	CONSOLE_CURSOR_INFO info;//hide the cursor
	info.bVisible = false;
	info.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

	focus = EC;
	gameStartTime = clock();


	
	if(!_Mananger->updateLayer.empty())
	for (auto it = Mananger::_Mananger->updateLayer.begin(); it != Mananger::_Mananger->updateLayer.end(); it++) {
		(*it)->start();
	}
	

}



//我的部分，基本不用看
void Mananger::loop() {
	int tickCount = 0, displayCount = 0; // Control update time
	int udratecnt = 0, dpratecnt = 0;//update rate
	clock_t t = clock();
	clock_t tickPerSecond = clock();
	while (!exit_b) {
		tickCount += clock() - t;
		displayCount += clock() - t;
		t = clock();
		
		if (tickCount > CLOCKS_PER_SEC / tickUpdate) {
			//tickupdate
			Update();
			udratecnt++;
			tickCount = 0;
		}
		if (displayCount > CLOCKS_PER_SEC / displayUpdate) {
			//displayupdate
			Display();
			dpratecnt++;
			displayCount = 0;
		}

		//use to counting update rate
		if (clock() - tickPerSecond >= 1000) {
			UPS = udratecnt;
			FPS = dpratecnt;
			udratecnt = 0;
			dpratecnt = 0;
			tickPerSecond = clock();
		}

	}

}

void Mananger::Update() {
	KeyBoard::keyBoard.keyUpdate();

	if (KeyBoard::keyBoard.anyKeyPress) {
		if (KeyBoard::keyBoard.IsKeyDown(VK_TAB)) {
			new ExampleCanvas(Position(rand() % 15, rand() % 15));//這樣可以動態產生物件
		}
		if (KeyBoard::keyBoard.IsKeyDown(VK_RETURN)) {
			if(focus)
			focus->keyEvent(VK_RETURN); //個人希望keyEvent只有被focus到才會動作，單純為了架構好看
		}
			
	}

	//我的部分，基本不用看
	for (auto it = Mananger::_Mananger->updateLayer.begin(); it != Mananger::_Mananger->updateLayer.end();) {
		auto now = it++;//提前讓it變成下一個要執行的，以免刪除後it無法++
		size_t layerSize = Mananger::_Mananger->updateLayer.size();
		(*now)->loop();
		if (_Mananger->updateLayer.empty())break;
	}
}


//我的部分，基本不用看
void Mananger::Display() {
	if (!_Mananger->displayLayer.empty())
	for (auto it = Mananger::_Mananger->displayLayer.begin(); it != Mananger::_Mananger->displayLayer.end(); it++) {
		(*it)->draw();
	}
	Display::_display.DrawBuffer();
}

Mananger::~Mananger()
{
	
}
