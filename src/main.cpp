#include <iostream>
#include <graphics.h>
#include <thread>
#include "util.h"
#include "frame_timer.h"
#include "animations/resources_manager.h"
#include "collision/collision_manager.h"
#include "characters/character_manager.h"

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

	frameTimer.init();

	BeginBatchDraw();

	while (!is_quit) {
		frameTimer.on_frame_start();

		while (peekmessage(&msg)) {
			CharacterManager::GetInstance()->on_input(msg);
		}

		frameTimer.on_frame_tick();
		CharacterManager::GetInstance()->on_update(frameTimer.get_delta().count());
		CollisionManager::getInstance()->process_collisions();

		setbkcolor(RGB(0, 0, 0));
		cleardevice();

		draw_background();
		CharacterManager::GetInstance()->on_render();
		CollisionManager::getInstance()->on_debug_render();

		FlushBatchDraw();

		frameTimer.frame_sleep();
	}

	EndBatchDraw();

	return 0;
}