#include "player_fall_state.h"
#include "../../util.h"
#include "../../characters/character_manager.h"

void PlayerFallState::on_enter() {
	Player* player = (Player*)CharacterManager::GetInstance()->GetPlayer();
	player->set_animation("fall");
}

void PlayerFallState::on_update(float delta) {
	Player* player = (Player*)CharacterManager::GetInstance()->GetPlayer();
	if (player->get_hp() <= 0)
		player->switch_state("dead");
	else if (player->is_on_floor()) {
		player->switch_state("idle");
		player->on_land();
		//ut::play_audio(_T("player_land"), false);
	}
	else if (player->can_attack()) {
		player->switch_state("attack");
	}
}


