#include "enemy.h"
#include "../collision/collision_manager.h"
#include "../animations/resources_manager.h"
#include "../state_machine/enemy_state_nodes/enemy_state_nodes.h"

Enemy::Enemy(){
	is_facing_left = true;
	position = { 1050,200 };
	logic_height = 150;

	hit_box->set_size({ 50,80 });
	hurt_box->set_size({ 100,180 });

	hit_box->set_layer_src(CollisionLayer::None);
	hit_box->set_layer_dst(CollisionLayer::PlayerLayer);

	hurt_box->set_layer_src(CollisionLayer::EnemyLayer);
	hurt_box->set_layer_dst(CollisionLayer::None);

	hurt_box->set_on_collision([&] {decrease_hp(); });

	collision_box_silk = CollisionManager::getInstance()->create_collision_box();
	collision_box_silk->set_size({ 225,225 });
	collision_box_silk->set_layer_src(CollisionLayer::None);
	collision_box_silk->set_layer_dst(CollisionLayer::PlayerLayer);
	collision_box_silk->set_enabled(false);

	load_animations();
}

Enemy::~Enemy(){
	CollisionManager::getInstance()->destroy_collision_box(collision_box_silk);
}

void Enemy::load_animations(){
	load_move_animation("aim", 0.05f, false);
	load_move_animation("dash_in_air", 0.05f, true);
	load_move_animation("dash_on_floor", 0.05f, true);
	load_move_animation("fall", 0.1f, true);
	load_move_animation("idle", 0.1f, true);
	load_move_animation("jump", 0.1f, false);
	load_move_animation("run", 0.05f, true);
	load_move_animation("squat", 0.05f, false);
	load_move_animation("throw_barb", 0.1f, false);
	load_move_animation("throw_silk", 0.1f, true);
	load_move_animation("throw_sword", 0.05f, false);

	load_one_animation(silk_animation, 0.1f, false, Animation::AnchorMode::BottomCentered, "silk");
	
	load_move_animation("vfx_dash_in_air", 0.1f, false, Animation::AnchorMode::Centered);
	load_move_animation("vfx_dash_on_floor", 0.1f, false);

	state_machine.register_state("aim", new EnemyAimState());
	state_machine.register_state("dash_in_air", new EnemyDashInAirState());
	state_machine.register_state("dash_on_floor", new EnemyDashOnFloorState());
	state_machine.register_state("dead", new EnemyDeadState());
	state_machine.register_state("fall", new EnemyFallState());
	state_machine.register_state("idle", new EnemyIdleState());
	state_machine.register_state("jump", new EnemyJumpState());
	state_machine.register_state("run", new EnemyRunState());
	state_machine.register_state("squat", new EnemySquatState());
	state_machine.register_state("throw_barb", new EnemyThrowBarbState());
	state_machine.register_state("throw_silk", new EnemyThrowSilkState());
	state_machine.register_state("throw_sword", new EnemyThrowSwordState());

	state_machine.set_entry("idle");
}

void Enemy::load_move_animation(const std::string& name, float interval, bool is_loop,Animation::AnchorMode ancherMode) {
	AnimationGroup& animation_group = animation_pool[name];
	load_one_animation(animation_group.Left, interval, is_loop, ancherMode, "enemy_" + name + "_left");
	load_one_animation(animation_group.Right, interval, is_loop, ancherMode, "enemy_" + name + "_right");
}

void Enemy::load_one_animation(Animation& animation, float interval, bool is_loop, Animation::AnchorMode anchorMode, const std::string& name) {
	animation.set_interval(interval);
	animation.set_loop(is_loop);
	animation.set_anchor_mode(anchorMode);
	animation.add_frame(ResourcesManager::GetInstance()->getAtlas(name));
}

void Enemy::on_update(float delta){
	if (velocity.x >= 0.0001f) {
		is_facing_left = (velocity.x < 0);
	}
	Character::on_update(delta);

	hit_box->set_position(get_logic_center());

	if (is_throwing_silk) {
		collision_box_silk->set_position(get_logic_center());
		silk_animation.set_position(get_logic_center());
		silk_animation.on_update(delta);
	}

	if (is_dashing_in_air || is_dashing_in_floor) {
		current_dash_animation->set_position(is_dashing_in_air ? get_logic_center() : position);
		current_dash_animation->on_update(delta);
	}

	for (Barb* barb : barb_list) {
		barb->on_update(delta);
	}

	for (Sword* sword : sword_list) {
		sword->on_update(delta);
	}

	barb_list.erase(std::remove_if(barb_list.begin(), barb_list.end(),
		[](Barb* barb) {
			bool can_remove = !barb->check_valid();
			if (can_remove) delete barb;
			return can_remove;
		}), barb_list.end());

	sword_list.erase(std::remove_if(sword_list.begin(), sword_list.end(),
		[](Sword* sword) {
			bool can_remove = !sword->check_valid();
			if (can_remove) delete sword;
			return can_remove;
		}), sword_list.end());
}

void Enemy::on_render(){
	for (Barb* barb : barb_list) {
		barb->on_render();
	}
	for (Sword* sword : sword_list) {
		 sword->on_render();
	}
	
	Character::on_render();

	if (is_throwing_silk) 
		silk_animation.on_render();
	
	if (is_dashing_in_air || is_dashing_in_floor) 
		current_dash_animation->on_render();
}

void Enemy::on_hurt(){
	switch (ut::range_random(1, 3)) {
	case 1:
		//ut::play_audio(_T("enemy_hurt_1"), false);
		break;
	case 2:
		//ut::play_audio(_T("enemy_hurt_2"), false);
		break;
	case 3:
		//ut::play_audio(_T("enemy_hurt_3"), false);
		break;
	}
}

void Enemy::throw_barbs(){
	int num_new_barb = ut::range_random(1, 3);
	if (barb_list.size() >= 10) num_new_barb = 1;
	int width_grid = getwidth() / num_new_barb;

	for (int i = 0; i < num_new_barb; i++) {
		Barb* new_barb = new Barb();
		float x = ut::range_random(width_grid * i, width_grid * (i + 1));
		float y = ut::range_random(250, 500);
		new_barb->set_position({ x,y });
		barb_list.push_back(new_barb);
	}
}

void Enemy::throw_sword(){
	Sword* new_sword = new Sword(get_logic_center(), is_facing_left);
	sword_list.push_back(new_sword);
}

void Enemy::on_dash(){
	if (is_dashing_in_air) 
		current_dash_animation = velocity.x>0 ? &animation_pool["vfx_dash_in_air"].Right : &animation_pool["vfx_dash_in_air"].Left;
	else 
		current_dash_animation = velocity.x>0 ? &animation_pool["vfx_dash_on_floor"].Right : &animation_pool["vfx_dash_on_floor"].Left;
	
	current_dash_animation->reset();
}

void Enemy::on_throw_silk(){
	silk_animation.reset();
}

