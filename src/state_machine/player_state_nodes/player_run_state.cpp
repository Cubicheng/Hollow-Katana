#include "player_run_state.h"
#include "../../characters/character_manager.h"
#include "../../util.h"

void PlayerRunState::on_enter() {
	Player* player = (Player*)CharacterManager::GetInstance()->GetPlayer();
	player->set_animation("run");
	//ut::play_audio(_T("player_run"), true);
}

void PlayerRunState::on_update(float delta) {
	Player* player = (Player*)CharacterManager::GetInstance()->GetPlayer();
	if (player->get_hp() <= 0)
		player->switch_state("dead");
	else if (player->get_move_dir() == 0)
		player->switch_state("idle");
	else if (player->can_jump())
		player->switch_state("jump");
	else if (player->can_attack())
		player->switch_state("attack");
	else if (player->can_roll())
		player->switch_state("roll");
}

void PlayerRunState::on_exit(){
	//ut::stop_audio(_T("player_run"));
}