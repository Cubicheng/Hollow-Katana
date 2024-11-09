#pragma once
#include "character.h"
#include "../bullets/barb.h"
#include "../bullets/sword.h"

class Enemy:public Character
{
public:
	Enemy();
	~Enemy();

	void load_animations();
	void load_move_animation(const std::string& name, float interval, bool is_loop, Animation::AnchorMode ancherMode = Animation::AnchorMode::BottomCentered);
	void load_one_animation(Animation& animation, float interval, bool is_loop, Animation::AnchorMode anchorMode, const std::string& name);

	void on_update(float delta) override;
	void on_render() override;

	void on_hurt()override;

	void set_facing_left(bool flag) {
		is_facing_left = flag;
	}

	bool get_facing_left() const{
		return is_facing_left;
	}

	void set_dashing_in_air(bool flag){
		is_dashing_in_air = flag;
	}

	bool get_dashing_in_air() const{
		return is_dashing_in_air;
	}

	void set_dashing_on_floor(bool flag){
		is_dashing_in_floor = flag;
	}

	bool get_dashing_on_floor() const{
		return is_dashing_in_floor;
	}

	void set_throw_silk(bool flag){
		is_throwing_silk = flag;
		collision_box_silk->set_enabled(flag);
	}

	bool get_throw_silk() const{
		return is_throwing_silk;
	}

	void throw_barbs();
	void throw_sword();

	void on_dash();
	void on_throw_silk();

	void on_render_hp();

private:

	const float full_hp = 10;

	bool is_throwing_silk = false;
	bool is_dashing_in_air = false;
	bool is_dashing_in_floor = false;

	Animation silk_animation;
	Animation* current_dash_animation = nullptr;

	ut::Rect hp_ui = {0,0,100,5};

	std::vector<Barb*> barb_list;
	std::vector<Sword*> sword_list;
	CollisionBox* collision_box_silk = nullptr;
};