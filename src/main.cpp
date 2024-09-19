#include <iostream>
#include <graphics.h>
#include <thread>
#include "util.h"
#include "frame_timer.h"
#include "resources_manager.h"

HWND hwnd;
ExMessage msg;
bool is_quit = false;
FrameTimer frameTimer;

void init() {
	hwnd = initgraph(1280, 720, EX_SHOWCONSOLE);
	SetWindowText(hwnd, _T("Hollow Katana"));
}

void LoadResources() {
	try {
		ResourcesManager::GetInstance()->load();
	}
	catch (const LPCTSTR id) {
		TCHAR err_msg[512];
		_stprintf_s(err_msg, _T("Can not load resources: %s"), id);
		MessageBox(hwnd, err_msg, _T("Failed to load resources"), MB_OK|MB_ICONERROR);
		__debugbreak();
	}
}

static void draw_background() {
	static IMAGE* img_background = ResourcesManager::GetInstance()->getImage("background");
	static ut::Rect rect_dst = {
		(getwidth() - img_background->getwidth()) / 2,
		(getheight() - img_background->getheight()) / 2,
		img_background->getwidth(),
		img_background->getheight()
	};
	ut::putimage_ex(img_background, &rect_dst);
}

int main() {

	init();

	LoadResources();

	BeginBatchDraw();

	while (!is_quit) {
		while (peekmessage(&msg)) {


		}

		ut::putimage_alpha(0, 0, ResourcesManager::GetInstance()->getImage("background"));

		frameTimer.update();

		setbkcolor(RGB(0, 0, 0));
		cleardevice();

		draw_background();

		FlushBatchDraw();

		frameTimer.frame_sleep();
	}

	EndBatchDraw();


	return 0;
}