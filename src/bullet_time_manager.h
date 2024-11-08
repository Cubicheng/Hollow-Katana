#pragma once

#include "util.h"

class BulletTimeManager{
public:
	enum class Status {
		Entering,
		Exiting
	};

	static BulletTimeManager* GetSingleton();

	void post_progress();
	void set_status(Status status);

	float on_update(float delta);

	void on_render_bullet_time_hp();

	const float get_hp() const{
		return hp;
	}

private:
	BulletTimeManager() = default;
	~BulletTimeManager() = default;

	static BulletTimeManager* instance;
	float progress = 0.0f;//from 0 to 1
	Status status = Status::Exiting;

	float hp = 1;
	const float SPEED_DECREASE = 1.0f;
	const float SPEED_INCREASE = 0.2f;

	ut::Rect rect = { 1100,10,170,30 };

	const float SPEED_PROGRESS = 2.0f;
	const float DST_DELTA_FACTOR = 0.35f;
	const float DST_COLOR_FACTOR = 0.35f;

	float lerp(float start, float end, float t) {
		return start + (end - start) * t;
	}
};