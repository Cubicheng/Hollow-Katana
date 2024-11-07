#include "player_jump_state.h"
#include "../../characters/character_manager.h"
#include "../../util.h"

void PlayerJumpState::on_enter() {
	Player* player = (Player*)CharacterManager::GetInstance()->GetPlayer();

	player->set_animation("jump");

	player->on_jump();

	ut::play_audio(_T("player_jump"), false);
}

void PlayerJumpState::on_update(float delta) {
	Player* player = (Player*)CharacterManager::GetInstance()->GetPlayer();
	if (player->get_hp() <= 0)
		player->switch_state("dead");
	else if (player->get_velocity().y > 0)
		player->switch_state("fall");
	else if (player->can_attack())
		player->switch_state("attack");
}
