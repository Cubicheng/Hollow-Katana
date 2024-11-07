#include "barb.h"
#include "../collision/collision_manager.h"
#include "../animations/resources_manager.h"
#include "../characters/character_manager.h"

Barb::Barb(){
	diff_period = ut::range_random(0, 6);

	animation_loose.set_interval(0.15f);
	animation_loose.set_loop(true);
	animation_loose.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_loose.add_frame(ResourcesManager::GetInstance()->getAtlas("barb_loose"));

	animation_break.set_interval(0.1f);
	animation_break.set_loop(false);
	animation_break.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_break.add_frame(ResourcesManager::GetInstance()->getAtlas("barb_break"));
	animation_break.set_on_finished([&]() {is_valid = false; });

	collision_box = CollisionManager::getInstance()->create_collision_box();
	collision_box->set_layer_src(CollisionLayer::EnemyLayer);
	collision_box->set_layer_dst(CollisionLayer::PlayerLayer);
	collision_box->set_size({ 20,20 });
	collision_box->set_on_collision([&]() {on_break(); });

	timer_idle.set_wait_time(ut::range_random(3, 10));
	timer_idle.set_one_shot(true);
	timer_idle.set_on_timeout([&]() {
		if (stage == Stage::Idle) {
			stage = Stage::Aim;
			base_position = current_position;
		}
		});

	timer_aim.set_wait_time(0.75f);
	timer_aim.set_one_shot(true);
	timer_aim.set_on_timeout([&]() {
		if (stage == Stage::Aim) {
			stage = Stage::Dash;
			const Vector2& pos_player = CharacterManager::GetInstance()->GetPlayer()->get_position();
			velocity = (pos_player - current_position).normalize() * SPEED_DASH;
		}
		});
}

Barb::~Barb(){
	CollisionManager::getInstance()->destroy_collision_box(collision_box);
}

void Barb::on_update(float delta){
	if (stage == Stage::Idle) {
		timer_idle.on_update(delta);
	}
	if (stage == Stage::Aim) {
		timer_aim.on_update(delta);
	}
	total_delta_time += delta;
	switch (stage) {
	case Stage::Idle:
		current_position.y = base_position.y + sin(total_delta_time / 0.5f + diff_period) * 30;
		break;
	case Stage::Aim:
		current_position.x = base_position.x + ut::range_random(-10, 10);
		break;
	case Stage::Dash:
		current_position += velocity * delta;
		if (current_position.y >= CharacterManager::GetInstance()->GetPlayer()->get_floor_y()) {
			on_break();
		}
		if (current_position.y <= 0) {
			is_valid = false;
		}
		break;
	}
	collision_box->set_position(current_position);

	current_animation = (stage == Stage::Break ? &animation_break : &animation_loose);
	current_animation->set_position(current_position);
	current_animation->on_update(delta);
}

void Barb::on_render(){
	current_animation->on_render();
}

void Barb::on_break(){
	if (stage == Stage::Break)
		return;
	stage = Stage::Break;
	collision_box->set_enabled(false);
	//ut::play_audio(_T("barb_break"), false);
}
