#include "player.h"
#include "../animations/resources_manager.h"
#include "../util.h"
#include "../state_machine/player_state_nodes/player_state_nodes.h"

#include <cmath>

Player::Player() {
	is_facing_left = false;
	position = { 250,200 };
	logic_height = 120;

	hit_box->set_size({ 150,150 });
	hurt_box->set_size({ 40,80 });

	hit_box->set_layer_dst(CollisionLayer::EnemyLayer);
	hit_box->set_layer_src(CollisionLayer::None);
	//hit box is specially for hit, so the layer src is none

	hurt_box->set_layer_dst(CollisionLayer::None);
	hurt_box->set_layer_src(CollisionLayer::PlayerLayer);
	//hurt box is speciallyfor hurt, so the layer dst is none

	hit_box->set_enabled(false);
	hurt_box->set_on_collision(
		[&]() {
			decrease_hp();
		}
	);

	timer_roll_cd.set_wait_time(CD_ROLL);
	timer_roll_cd.set_one_shot(true);
	timer_roll_cd.set_on_timeout(
		[&]() {
			is_roll_cd_comp = true;
		}
	);

	timer_attack_cd.set_wait_time(CD_ATTACK);
	timer_attack_cd.set_one_shot(true);
	timer_attack_cd.set_on_timeout(
		[&]() {
			is_attack_cd_comp = true;
		}
	);

	load_animations();

	state_machine.register_state("attack", new PlayerAttackState());
	state_machine.register_state("dead", new PlayerDeadState());
	state_machine.register_state("fall", new PlayerFallState());
	state_machine.register_state("jump", new PlayerJumpState());
	state_machine.register_state("idle", new PlayerIdleState());
	state_machine.register_state("roll", new PlayerRollState());
	state_machine.register_state("run", new PlayerRunState());

	state_machine.set_entry("idle");
}

void Player::on_input(const ExMessage& msg){
	if (hp <= 0)
		return;
	switch (msg.message) {
		case WM_KEYDOWN:
			switch (msg.vkcode) {
			case 0x41:
				is_left_key_down = true;
				break;
			case 0x44:
				is_right_key_down = true;
				break;
			case VK_SPACE:
			case 0x57:
			case VK_UP:
				is_jump_key_down = true;
				break;
			case 0x53:
			case VK_DOWN:
				is_roll_key_down = true;
				break;
			}
			break;
		case WM_KEYUP:
			switch (msg.vkcode) {
			case 0x41:
				is_left_key_down = false;
				break;
			case 0x44:
				is_right_key_down = false;
				break;
			case VK_SPACE:
			case 0x57:
			case VK_UP:
				is_jump_key_down = false;
				break;
			case 0x53:
			case VK_DOWN:
				is_roll_key_down = false;
				break;
			}
			break;
		case WM_LBUTTONDOWN:
			is_attack_key_down = true;
			update_attack_dir(msg.x, msg.y);
			break;
		case WM_LBUTTONUP:
			is_attack_key_down = false;
			break;

		case WM_RBUTTONDOWN:
			//todo
			break;

		case WM_RBUTTONUP:
			//todo
			break;
	}
}

void Player::on_update(float delta){
	if (hp > 0 && !is_rolling)
		velocity.x = get_move_dir() * SPEED_RUN;
	if(get_move_dir()!=0)
		is_facing_left = get_move_dir() < 0;
	
	timer_roll_cd.on_update(delta);
	timer_attack_cd.on_update(delta);

	animation_jump_vfx.on_update(delta);
	animation_land_vfx.on_update(delta);

	if (is_attacking) {
		current_slash_animation->set_position(get_logic_center());
		current_slash_animation->on_update(delta);
	}

	Character::on_update(delta);
}

void Player::on_render(){
	if(is_jump_vfx_visible)
		animation_jump_vfx.on_render();
	if(is_land_vfx_visible)
		animation_land_vfx.on_render();

	Character::on_render();

	if(is_attacking)
		current_slash_animation->on_render();
}

void Player::on_hurt(){
	//ut::play_audio(_T("player_hurt"), false);
}

void Player::on_jump(){
	velocity.y -= SPEED_JUMP;
	is_jump_vfx_visible = true;
	animation_jump_vfx.set_position(position);
	animation_jump_vfx.reset();
}

void Player::on_land(){
	is_land_vfx_visible = true;
	animation_land_vfx.set_position(position);
	animation_land_vfx.reset();
}

void Player::on_roll(){
	timer_roll_cd.restart();
	is_roll_cd_comp = false;
	velocity.x = is_facing_left ? -SPEED_ROLL : SPEED_ROLL;
}

void Player::on_attack(){
	timer_attack_cd.restart();
	is_attack_cd_comp = false;
	switch (attack_dir) {
	case Player::AttackDir::Up:
		current_slash_animation = &animation_slash_up;
		break;
	case Player::AttackDir::Down:
		current_slash_animation = &animation_slash_down;
		break;
	case Player::AttackDir::Left:
		current_slash_animation = &animation_slash_left;
		is_facing_left = true;
		break;
	case Player::AttackDir::Right:
		current_slash_animation = &animation_slash_right;
		is_facing_left = false;
		break;
	}
	current_slash_animation->set_position(get_logic_center());
	current_slash_animation->reset();
}

void Player::load_animations() {
	load_move_animation("attack", 0.05f, false, 5);
	load_move_animation("dead", 0.1f, false, 6);
	load_move_animation("fall", 0.15f, false, 5);
	load_move_animation("idle", 0.15f, true, 5);
	load_move_animation("jump", 0.15f, false, 5);
	load_move_animation("roll", 0.05f, false, 7);
	load_move_animation("run", 0.075f, true, 10);

	load_one_animation(animation_slash_up, 0.07f, false, Animation::AnchorMode::Centered, "player_vfx_attack_up", 5);
	load_one_animation(animation_slash_down, 0.07f, false, Animation::AnchorMode::Centered, "player_vfx_attack_down", 5);
	load_one_animation(animation_slash_left, 0.07f, false, Animation::AnchorMode::Centered, "player_vfx_attack_left", 5);
	load_one_animation(animation_slash_right, 0.07f, false, Animation::AnchorMode::Centered, "player_vfx_attack_right", 5);

	load_one_animation(animation_jump_vfx, 0.05f, false, Animation::AnchorMode::BottomCentered, "player_vfx_jump", 5);
	animation_jump_vfx.set_on_finished([&]() {
		is_jump_vfx_visible = false;
	});

	load_one_animation(animation_land_vfx, 0.1f, false, Animation::AnchorMode::BottomCentered, "player_vfx_land", 2);
	animation_land_vfx.set_on_finished([&]() {
		is_land_vfx_visible = false;
	});
}

void Player::load_move_animation(const std::string& name, float interval, bool is_loop, int num_h) {
	AnimationGroup& animation_group = animation_pool[name];

	load_one_animation(animation_group.Left, interval, is_loop, Animation::AnchorMode::BottomCentered, "player_" + name + "_left", num_h);
	load_one_animation(animation_group.Right, interval, is_loop, Animation::AnchorMode::BottomCentered, "player_" + name + "_right", num_h);
}

void Player::load_one_animation(Animation& animation, float interval, bool is_loop, Animation::AnchorMode anchorMode, const std::string& name, int num_h){
	animation.set_interval(interval);
	animation.set_loop(is_loop);
	animation.set_anchor_mode(anchorMode);
	animation.add_frame(ResourcesManager::GetInstance()->getImage(name), num_h);
}

void Player::update_attack_dir(int x, int y){
	static const float PI = 3.14159265358979323846f;
	float angle = std::atan2(-(y - (position.y - logic_height / 2)), x - position.x);
	if (angle >= -PI / 4 && angle < PI / 4)
		attack_dir = AttackDir::Right;
	else if (angle >= PI / 4 && angle <= 3 * PI / 4)
		attack_dir = AttackDir::Up;
	else if (angle < -PI / 4 && angle > -3 * PI / 4)
		attack_dir = AttackDir::Down;
	else attack_dir = AttackDir::Left;
}
