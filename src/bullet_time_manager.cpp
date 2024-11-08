#include "bullet_time_manager.h"
#include "graphics.h"

BulletTimeManager* BulletTimeManager::instance = nullptr;

BulletTimeManager* BulletTimeManager::GetSingleton() {
	if (!instance)
		instance = new BulletTimeManager();
	return instance;
}

void BulletTimeManager::post_progress() {
	DWORD* buffer = GetImageBuffer();
	int w = getwidth();
	int h = getheight();
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int idx = y * w + x;
			DWORD color = buffer[idx];
			BYTE r = (BYTE)(GetRValue(color) * lerp(1.0f, DST_COLOR_FACTOR, progress));
			BYTE g = (BYTE)(GetGValue(color) * lerp(1.0f, DST_COLOR_FACTOR, progress));
			BYTE b = (BYTE)(GetBValue(color) * lerp(1.0f, DST_COLOR_FACTOR, progress));
			buffer[idx] = RGB(r, g, b);
		}
	}
}

void BulletTimeManager::set_status(Status status) {
	this->status = status;
}

float BulletTimeManager::on_update(float delta) {
	float delta_progress = SPEED_PROGRESS * delta;
	progress += delta_progress * (status == Status::Entering ? 1 : -1);
	
	if (progress < 0) progress = 0;
	if (progress > 1) progress = 1;

	if (status == Status::Entering) {
		hp -= SPEED_DECREASE * delta;
	}
	else {
		hp += SPEED_INCREASE * delta;
	}

	if (hp < 0) {
		hp = 0;
		set_status(Status::Exiting);
	}
	if (hp > 1) hp = 1;


	return delta * lerp(1.0f, DST_DELTA_FACTOR, progress);
}

void BulletTimeManager::on_render_bullet_time_hp(){
	setfillcolor(RGB(63, 104, 125));
	solidrectangle(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);
	setfillcolor(RGB(126,208,249));
	solidrectangle(rect.x, rect.y, rect.x + hp*rect.w, rect.y + rect.h);
}


