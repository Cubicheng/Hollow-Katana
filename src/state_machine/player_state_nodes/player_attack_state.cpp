#include "player_attack_state.h"
#include "../../characters/character_manager.h"
#include "../../util.h"

PlayerAttackState::PlayerAttackState() {
	timer.set_wait_time(0.3f);
	timer.set_one_shot(true);
	timer.set_on_timeout(
		[&]() {
			Player* player = (Player*)CharacterManager::GetInstance()->GetPlayer();
			player->set_attacking(false);
		}
	);
}

void PlayerAttackState::on_enter() {
	Player* player = (Player*)CharacterManager::GetInstance()->GetPlayer();

	player->set_animation("attack");
	player->get_hit_box()->set_enabled(true);
	player->set_attacking(true);
	update_hit_box_position();
	player->on_attack();
	timer.restart();

	switch (ut::range_random(1, 3)) {
	case 1:
		ut::play_audio(_T("player_attack_1"), false);
		break;
	case 2:
		ut::play_audio(_T("player_attack_2"), false);
		break;
	case 3:
		ut::play_audio(_T("player_attack_3"), false);
		break;
	}
}

void PlayerAttackState::on_update(float delta) {
	timer.on_update(delta);
	update_hit_box_position();

	Player* player = (Player*)CharacterManager::GetInstance()->GetPlayer();

	if (player->get_hp() <= 0)
		player->switch_state("dead");
	else if (!player->get_attacking()) {
		if (player->get_velocity().y > 0)
			player->switch_state("fall");
		else if (player->get_move_dir() == 0)
			player->switch_state("idle");
		else if (player->is_on_floor() && player->get_move_dir() != 0)
			player->switch_state("run");
	}
}

void PlayerAttackState::on_exit() {
	Player* player = (Player*)CharacterManager::GetInstance()->GetPlayer();
	player->get_hit_box()->set_enabled(false);
	player->set_attacking(false);
}

void PlayerAttackState::update_hit_box_position(){
	Player* player = (Player*)CharacterManager::GetInstance()->GetPlayer();

	Vector2 pos_hit_box;
	Vector2 pos_center = player->get_logic_center();
	CollisionBox* hit_box = player->get_hit_box();
	const Vector2& size_hit_box = hit_box->get_size();

	switch (player->get_attack_dir()) {
	case Player::AttackDir::Up:
		pos_hit_box = { pos_center.x,pos_center.y - size_hit_box.y / 2 };
		break;
	case Player::AttackDir::Down:
		pos_hit_box = { pos_center.x,pos_center.y + size_hit_box.y / 2 };
		break;
	case Player::AttackDir::Left:
		pos_hit_box = { pos_center.x - size_hit_box.x / 2,pos_center.y };
		break;
	case Player::AttackDir::Right:
		pos_hit_box = { pos_center.x + size_hit_box.x / 2,pos_center.y };
		break;
	}
	
	hit_box->set_position(pos_hit_box);
}
