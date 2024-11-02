#pragma once

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

private:
	BulletTimeManager() = default;
	~BulletTimeManager() = default;

	static BulletTimeManager* instance;
	float progress = 0.0f;//from 0 to 1
	Status status = Status::Exiting;

	const float SPEED_PROGRESS = 2.0f;
	const float DST_DELTA_FACTOR = 0.35f;
	const float DST_COLOR_FACTOR = 0.35f;

	float lerp(float start, float end, float t) {
		return start + (end - start) * t;
	}
};