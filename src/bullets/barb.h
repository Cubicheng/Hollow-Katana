#pragma once

#include "../animations/animation.h"
#include "../collision/collision_box.h"

class Barb {
public:
	Barb();
	~Barb();

	void on_update(float delta);
	void on_render();

	void set_position(const Vector2& position) {
		this->base_position = position;
		this->current_position = position;
	}

	bool check_valid()const {
		return is_valid;
	}

private:
	enum class Stage {
		Idle,
		Aim,
		Dash,
		Break
	};

	const float SPEED_DASH = 1500.0f;

	Vector2 velocity;
	Vector2 base_position;
	Vector2 current_position;
	bool is_valid = true;

	Timer timer_idle;
	Timer timer_aim;

	int diff_period = 0;
	float total_delta_time = 0;

	Animation animation_loose;
	Animation animation_break;
	Animation* current_animation = nullptr;

	Stage stage = Stage::Idle;
	CollisionBox* collision_box = nullptr;

	void on_break();
};