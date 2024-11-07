
#include "player_roll_state.h"
#include "../../characters/character_manager.h"

PlayerRollState::PlayerRollState() {
	timer.set_wait_time(0.35f);
	timer.set_one_shot(true);
	timer.set_on_timeout(
		[&]() {
			Player* player = (Player*)CharacterManager::GetInstance()->GetPlayer();
			player->set_rolling(false);
		}
	);
}

void PlayerRollState::on_enter() {
	Player* player = (Player*)CharacterManager::GetInstance()->GetPlayer();
	player->set_animation("roll");

	player->get_hurt_box()->set_enabled(false);
	player->set_rolling(true);
	player->on_roll();
	timer.restart();

	ut::play_audio(_T("player_roll"), false);
}

void PlayerRollState::on_update(float delta) {
	timer.on_update(delta);
	Player* player = (Player*)CharacterManager::GetInstance()->GetPlayer();

	if (!player->get_rolling()) {
		if (player->get_move_dir() != 0)
			player->switch_state("run");
		else if (player->can_jump())
			player->switch_state("jump");
		else
			player->switch_state("idle");
	}
}

void PlayerRollState::on_exit() {
	Player* player = (Player*)CharacterManager::GetInstance()->GetPlayer();
	player->get_hurt_box()->set_enabled(true);
}


