#include <iostream>
#include <graphics.h>
#include <thread>
#include "util.h"
#include "frame_timer.h"
#include "animations/resources_manager.h"
#include "collision/collision_manager.h"
#include "characters/character_manager.h"
#include "bullet_time_manager.h"

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

void draw_remain_hp() {
	static IMAGE* img_ui_heart = ResourcesManager::GetInstance()->getImage("ui_heart");
	ut::Rect rect_dst = { 0,10,img_ui_heart->getwidth(),img_ui_heart->getheight() };
	Player* player = (Player*)CharacterManager::GetInstance()->GetPlayer();
	for (int i = 0; i < player->get_hp(); i++) {
		rect_dst.x = 10 + i * 40;
		ut::putimage_ex(img_ui_heart, &rect_dst);
	}
}

int main() {

	init();

	LoadResources();

	ut::play_audio(_T("bgm"), true);

	frameTimer.init();

	BeginBatchDraw();

	while (!is_quit) {
		frameTimer.on_frame_start();

		while (peekmessage(&msg)) {
			CharacterManager::GetInstance()->on_input(msg);
		}

		frameTimer.on_frame_tick();
		float scaled_delta = BulletTimeManager::GetSingleton()->on_update(frameTimer.get_delta().count());
		CharacterManager::GetInstance()->on_update(scaled_delta);
		CollisionManager::getInstance()->process_collisions();

		setbkcolor(RGB(0, 0, 0));
		cleardevice();

		draw_background();
		CharacterManager::GetInstance()->on_render();
		CollisionManager::getInstance()->on_debug_render();
		draw_remain_hp();

		FlushBatchDraw();

		frameTimer.frame_sleep();
	}

	EndBatchDraw();

	return 0;
}