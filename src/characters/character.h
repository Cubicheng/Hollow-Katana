#pragma once

#include "../vector2.h"
#include "../animations/animation.h"
#include "../collision/collision_box.h"
#include "../state_machine/state_machine.h"

#include <string>
#include <graphics.h>
#include <unordered_map>

class Character
{
public:
	Character();
	~Character();

	void decrease_hp();

	int get_hp() const {
		return hp;
	}

	void set_position(const Vector2& pos) {
		position = pos;
	}

	const Vector2& get_position() const {
		return position;
	}

	void set_velocity(const Vector2& vel) {
		velocity = vel;
	}

	Vector2 get_velocity() const {
		return velocity;
	}

	Vector2 get_logic_center()const {
		return Vector2(position.x, position.y - logic_height / 2);
	}

	void set_enable_gravity(bool enable) {
		enable_gravity = enable;
	}

	CollisionBox* get_hit_box() const {
		return hit_box;
	}

	CollisionBox* get_hurt_box() const {
		return hurt_box;
	}

	bool is_on_floor() const {
		return position.y >= FLOOR_Y;
	}

	void make_invunlerable() {
		is_invunlerable = true;
		timer_invunlerable_status.restart();
	}

	virtual void on_input(const ExMessage& msg) {}
	virtual void on_update(float delta);
	virtual void on_render();

	virtual void on_hurt() {}

	void switch_state(const std::string& id);
	void set_animation(const std::string& id);

protected:
	struct AnimationGroup {
		Animation Left;
		Animation Right;
	};

	const float FLOOR_Y = 620;
	const float GRAVITY = 980 * 2;

	int hp = 10;
	Vector2 position;//bottom position
	Vector2 velocity;
	float logic_height = 0;
	bool is_facing_left = true;
	StateMachine state_machine;
	bool enable_gravity = true;
	bool is_invunlerable = false;
	Timer timer_invunlerable_blink;
	Timer timer_invunlerable_status;
	bool is_blink_invisible = false;
	CollisionBox* hit_box = nullptr;
	CollisionBox* hurt_box = nullptr;
	AnimationGroup* current_animation = nullptr;
	std::unordered_map<std::string, AnimationGroup> animation_pool;
};